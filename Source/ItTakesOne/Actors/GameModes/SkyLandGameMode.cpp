// Fill out your copyright notice in the Description page of Project Settings.

#include "SkyLandGameMode.h"

#include "GameFramework/PlayerState.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"
#include "ItTakesOne/Actors/PlayerStates/SkyPlayerState.h"
#include "ItTakesOne/Framework/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASkyLandGameMode::ASkyLandGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BPSkyController"));
	if (PlayerControllerBPClass.Class)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateBPClass(
		TEXT("/Game/Blueprints/Core/PlayerStates/BP_SkyPlayerState"));
	if (PlayerStateBPClass.Class)
	{
		PlayerStateClass = PlayerStateBPClass.Class;
	}
}

FPlayableWorldSaveData* ASkyLandGameMode::GetPlayableWorldSaveData()
{
	const auto GameInstance = GetGameInstance<UMainGameInstance>();
	const auto ContentData = GameInstance->GetContentData();
	return &ContentData->SkyLand;
}

void ASkyLandGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerState = Cast<ASkyPlayerState>(UGameplayStatics::GetActorOfClass(this, ASkyPlayerState::StaticClass()));
	BossCharacter = Cast<
		AWindBossCharacter>(UGameplayStatics::GetActorOfClass(this, AWindBossCharacter::StaticClass()));

	if (PlayerState)
	{
		PlayerState->OnHealthUpdateDelegate.AddDynamic(this, &ASkyLandGameMode::OnPlayerHealthUpdate);
	}

	if (BossCharacter)
	{
		BossCharacter->OnHealthUpdateDelegate.AddDynamic(this, &ASkyLandGameMode::OnBossHealthUpdate);
	}
}

void ASkyLandGameMode::OnPlayerHealthUpdate(float OldHealth, float NewHealth)
{
	UE_LOG(LogTemp, Display, TEXT("%s: player hp %f -> %f"), *GetActorNameOrLabel(), OldHealth, NewHealth);
}

void ASkyLandGameMode::OnBossHealthUpdate(float OldHealth, float NewHealth)
{
	UE_LOG(LogTemp, Display, TEXT("%s: boss hp %f -> %f"), *GetActorNameOrLabel(), OldHealth, NewHealth);
}
