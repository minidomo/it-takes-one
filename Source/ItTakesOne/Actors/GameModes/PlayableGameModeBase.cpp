// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableGameModeBase.h"

#include "GameFramework/PlayerStart.h"
#include "ItTakesOne/Actors/GameStates/PlayableGameStateBase.h"
#include "ItTakesOne/Framework/MainWorldSettings.h"

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
