// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameModeBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Actors/GameStates/PlayableGameStateBase.h"
#include "ItTakesOne/Framework/MainGameInstance.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"
#include "ItTakesOne/Interfaces/SavableActorInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

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

AActor* APlayableGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* PlayerStart = nullptr;

	if (const auto CurGameState = GetGameState<APlayableGameStateBase>())
	{
		PlayerStart = CurGameState->GetActiveSpawnPoint();

		if (PlayerStart)
		{
			UE_LOG(LogTemp, Display, TEXT("%s: use game state active spawn point"), *GetActorNameOrLabel());
		}
	}

	if (!PlayerStart)
	{
		if (const auto WorldSettings = Cast<AMainWorldSettings>(GetWorldSettings()))
		{
			PlayerStart = WorldSettings->GetDefaultSpawnPoint();

			if (PlayerStart)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: use world settings default spawn point"), *GetActorNameOrLabel());
			}
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
	UE_LOG(LogTemp, Display, TEXT("%s: loading map data"), *GetActorNameOrLabel());

	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	auto ContentData = GameInstance->GetContentData();
	auto& WorldData = ContentData->TestWorld;

	if (WorldData.bInitialized)
	{
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			auto Actor = *It;
			auto SavableActor = Cast<ISavableActorInterface>(Actor);
			if (SavableActor)
			{
				for (auto& ActorData : WorldData.Actors)
				{
					if (ActorData.ActorName == Actor->GetFName())
					{
						FMemoryReader MemReader(ActorData.ByteData);
						FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
						Ar.ArIsSaveGame = true;
						Actor->Serialize(Ar);
						SavableActor->OnActorLoaded();
					}
				}
			}
		}
	}
}

void APlayableGameModeBase::WriteSaveGame()
{
	UE_LOG(LogTemp, Display, TEXT("%s: saving map data"), *GetActorNameOrLabel());
	auto WorldData = GetPlayableWorldSaveData();
	if (!WorldData) { return; }

	WorldData->Actors.Empty();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		auto Actor = *It;
		auto SavableActor = Cast<ISavableActorInterface>(Actor);
		if (IsValid(Actor) && SavableActor)
		{
			FActorSaveData ActorData;
			ActorData.ActorName = Actor->GetFName();

			FMemoryWriter MemWriter(ActorData.ByteData);
			FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
			Ar.ArIsSaveGame = true;
			Actor->Serialize(Ar);

			WorldData->Actors.Add(ActorData);
		}
	}

	WorldData->bInitialized = true;

	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	auto ContentData = GameInstance->GetContentData();
	UGameplayStatics::SaveGameToSlot(ContentData, GameInstance->GetContentSlotName(), 0);
}

FPlayableWorldSaveData* APlayableGameModeBase::GetPlayableWorldSaveData()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	return &ContentData->TestWorld;
}

void APlayableGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	LoadSaveGame();
}
