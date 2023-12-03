// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameModeBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Actors/GameStates/PlayableGameStateBase.h"
#include "ItTakesOne/Actors/PlayerStates/PlayablePlayerStateBase.h"
#include "ItTakesOne/Framework/MainGameInstance.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "Kismet/GameplayStatics.h"

APlayableGameModeBase::APlayableGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BP_BasePlayerController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AGameStateBase> GameStateBPClass(
		TEXT("/Game/Blueprints/Core/GameStates/BP_PlayableGameStateBase"));
	if (GameStateBPClass.Class)
	{
		GameStateClass = GameStateBPClass.Class;
	}

	PlayerStateClass = APlayablePlayerStateBase::StaticClass();
}

void APlayableGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("%s: begin play"), *GetActorNameOrLabel());
	OnPlayerDiedDelegate.AddDynamic(this, &APlayableGameModeBase::OnPlayerDied);
}

void APlayableGameModeBase::OnPlayerDied(ACharacter* Character, AController* Controller)
{
	UE_LOG(LogTemp, Display, TEXT("%s: player died"), *GetActorNameOrLabel());
	Controller->StartSpot.Reset();
	RestartPlayer(Controller);
}

void APlayableGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	LoadPlayerState(NewPlayer->GetPlayerState<APlayerState>());
}

AActor* APlayableGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* PlayerStart = nullptr;

	if (const auto CurGameState = GetGameState<APlayableGameStateBase>())
	{
		PlayerStart = CurGameState->GetActiveSpawnPoint();

		// if (PlayerStart)
		// {
		// 	UE_LOG(LogTemp, Display, TEXT("%s: use game state active spawn point"), *GetActorNameOrLabel());
		// }
	}

	if (!PlayerStart)
	{
		if (const auto WorldSettings = Cast<AMainWorldSettings>(GetWorldSettings()))
		{
			PlayerStart = WorldSettings->GetDefaultSpawnPoint();

			// if (PlayerStart)
			// {
			// 	UE_LOG(LogTemp, Warning, TEXT("%s: use world settings default spawn point"), *GetActorNameOrLabel());
			// }
		}
	}

	if (!PlayerStart)
	{
		PlayerStart = Super::ChoosePlayerStart_Implementation(Player);

		UE_LOG(LogTemp, Error,
		       TEXT(
			       "%s: could not find a spawn point in game state or world settings, using default player start implementation"
		       ), *GetActorNameOrLabel());
	}

	return PlayerStart;
}

void APlayableGameModeBase::LoadSaveGame()
{
	const auto WorldData = GetPlayableWorldSaveData();

	if (!WorldData)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: attempted to load world data but storage data is null"),
		       *GetActorNameOrLabel());
		return;
	}

	if (!WorldData->bInitialized)
	{
		UE_LOG(LogTemp, Display, TEXT("%s: world data was not marked as initialized, skipping loading"),
		       *GetActorNameOrLabel());
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("%s: loading map data"), *GetActorNameOrLabel());

	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	const auto World = GetWorld();
	TSet<FName> LoadedActors;

	// give data to actors that already exist in the level
	for (FActorIterator It(World); It; ++It)
	{
		const auto Actor = *It;
		const auto SavableActor = Cast<ISavableActorInterface>(Actor);
		if (IsValid(Actor) && SavableActor)
		{
			FActorSaveData* Data = WorldData->Actors.FindByPredicate([&](const FActorSaveData& Element)
			{
				return Element.Name == Actor->GetFName();
			});

			if (Data)
			{
				if (!Data->bDeferLoad && ContentData->LoadActor(Actor, *Data))
				{
					SavableActor->OnActorLoaded();
					LoadedActors.Add(Data->Name);
				}
			}
			else
			{
				// having no data means this actor was destroyed at runtime, so destroy it
				Actor->Destroy();
			}

			UE_LOG(LogTemp, Display, TEXT("%s: %s | %d"), *GetActorNameOrLabel(), *Actor->GetActorNameOrLabel(),
			       !!Data);
		}
	}


	// spawn actors that were created at runtime 
	for (auto& Data : WorldData->Actors)
	{
		if (Data.bDeferLoad) { continue; }

		if (!LoadedActors.Contains(Data.Name))
		{
			FActorSpawnParameters Params;
			Params.Name = Data.Name;

			AActor* Actor = World->SpawnActor(Data.Class, &Data.Transform, Params);
			if (ContentData->LoadActor(Actor, Data))
			{
				const auto SavableActor = Cast<ISavableActorInterface>(Actor);
				SavableActor->OnActorLoaded();
				LoadedActors.Add(Data.Name);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: actor failed to load: %s"), *GetActorNameOrLabel(),
				       *Data.Name.ToString());
			}

			UE_LOG(LogTemp, Display, TEXT("%s: spawn %s | %d"), *GetActorNameOrLabel(), *Data.Name.ToString(), !!Actor);
		}
	}
}

void APlayableGameModeBase::WriteSaveGame()
{
	const auto WorldData = GetPlayableWorldSaveData();

	if (!WorldData)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: attempted to save world data but storage data was not set"),
		       *GetActorNameOrLabel());
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("%s: saving map data"), *GetActorNameOrLabel());

	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();

	WorldData->Actors.Empty();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		const auto Actor = *It;
		const auto SavableActor = Cast<ISavableActorInterface>(Actor);
		if (IsValid(Actor) && SavableActor)
		{
			FActorSaveData Data;
			if (ContentData->SaveActor(Actor, Data))
			{
				WorldData->Actors.Add(Data);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: actor failed to save: %s"), *GetActorNameOrLabel(),
				       *Actor->GetActorNameOrLabel());
			}
		}
	}

	WorldData->bInitialized = true;
	UGameplayStatics::SaveGameToSlot(ContentData, GameInstance->GetContentSlotName(), 0);
}

FPlayableWorldSaveData* APlayableGameModeBase::GetPlayableWorldSaveData()
{
	if (const auto GameInstance = GetGameInstance<UMainGameInstance>())
	{
		const auto ContentData = GameInstance->GetContentData();
		return &ContentData->TestWorld;
	}
	return nullptr;
}

void APlayableGameModeBase::LoadPlayerState(APlayerState* PlayerState)
{
	const auto CurPlayerState = Cast<APlayablePlayerStateBase>(PlayerState);

	if (!CurPlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: attempted to load data into player state but received unexpected type"),
		       *GetActorNameOrLabel());
		return;
	}

	const auto WorldData = GetPlayableWorldSaveData();

	if (!WorldData || !WorldData->bInitialized) { return; }

	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();

	FActorSaveData* Data = WorldData->Actors.FindByPredicate([&](const FActorSaveData& Element)
	{
		return Element.Name == CurPlayerState->GetFName();
	});

	if (Data && ContentData->LoadActor(CurPlayerState, *Data))
	{
		CurPlayerState->OnActorLoaded();
	}
}

void APlayableGameModeBase::InitGameState()
{
	Super::InitGameState();
	LoadSaveGame();
}
