// Fill out your copyright notice in the Description page of Project Settings.

#include "SkyLandGameMode.h"

#include "NavigationSystem.h"
#include "GameFramework/PlayerState.h"
#include "ItTakesOne/Actors/LevelTransitionActor.h"
#include "ItTakesOne/Actors/Boss/CoreCrystal.h"
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
	if (const auto GameInstance = GetGameInstance<UMainGameInstance>())
	{
		const auto ContentData = GameInstance->GetContentData();
		return &ContentData->SkyLand;
	}
	return nullptr;
}

void ASkyLandGameMode::BeginPlay()
{
	Super::BeginPlay();

	BossCharacter = Cast<
		AWindBossCharacter>(UGameplayStatics::GetActorOfClass(this, AWindBossCharacter::StaticClass()));

	if (BossCharacter)
	{
		BossCharacter->OnDestroyed.AddDynamic(this, &ASkyLandGameMode::OnBossDestroyed);
	}

	OnCoreCrystalDestroyedDelegate.AddDynamic(this, &ASkyLandGameMode::OnCoreCrystalDestroyed);

	SpawnCoreCrystal();
}

void ASkyLandGameMode::OnPlayerDied(ACharacter* Character, AController* Controller)
{
}

void ASkyLandGameMode::OnBossDestroyed(AActor* DestroyedActor)
{
	if (const auto SaveData = GetPlayableWorldSaveData())
	{
		SaveData->bPlaythroughComplete = true;
	}

	// spawn transition actor
	FVector Location = BossCharacter->GetActorLocation();

	// offset Z upwards so adjusting puts the actor on top of the terrain
	Location.Z += 10;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const auto Actor = GetWorld()->SpawnActor<ALevelTransitionActor>(LevelTransitionActorClass, Location,
	                                                                 FRotator::ZeroRotator,
	                                                                 Params);
	Actor->LevelToLoad = "MainMenu";

	// save after two seconds to allow for other processes to take place
	GetWorldTimerManager().SetTimer(SaveAfterBossDeathTimerHandle, this, &ASkyLandGameMode::WriteSaveGame, 2.f);
}

void ASkyLandGameMode::OnCoreCrystalDestroyed()
{
	SpawnCoreCrystal();
}

void ASkyLandGameMode::SpawnCoreCrystal()
{
	if (!IsValid(BossCharacter)) { return; }

	FVector Location;

	if (BossCharacter)
	{
		if (const auto NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem()))
		{
			FNavLocation Result;
			NavSystem->GetRandomReachablePointInRadius(BossCharacter->GetActorLocation(), 3000.f, Result);
			Location = Result.Location;
		}
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<ACoreCrystal>(CoreCrystalClass, Location, FRotator::ZeroRotator, Params);
}
