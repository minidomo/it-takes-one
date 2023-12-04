// Fill out your copyright notice in the Description page of Project Settings.

#include "RingWave.h"

#include "Components/BoxComponent.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"
#include "ItTakesOne/Actors/PlayerStates/SkyPlayerState.h"
#include "Kismet/GameplayStatics.h"

class ASkyPlayerState;

ARingWave::ARingWave()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Speed = 500.f;
	PlayerDamage = 10.f;
	MaxTimeAlive = 10.f;
}

void ARingWave::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARingWave::OnBeginOverlap);
	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &ARingWave::CallDestroy, MaxTimeAlive);

	if (const auto Boss = Cast<AWindBossCharacter>(
		UGameplayStatics::GetActorOfClass(this, AWindBossCharacter::StaticClass())))
	{
		Boss->OnDestroyed.AddDynamic(this, &ARingWave::OnBossDestroyed);
	}
	else
	{
		Destroy();
	}
}

void ARingWave::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	if (const auto Controller = OtherActor->GetInstigatorController())
	{
		if (const auto PlayerState = Controller->GetPlayerState<ASkyPlayerState>())
		{
			PlayerState->ApplyDamage(PlayerDamage);
		}
	}
}

void ARingWave::CallDestroy()
{
	Destroy();
}

void ARingWave::OnBossDestroyed(AActor* DestroyedActor)
{
	Destroy();
}

void ARingWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Distance = Direction * Speed * DeltaTime;
	const FVector NewPosition = GetActorLocation() + Distance;
	SetActorLocation(NewPosition, true);
}

void ARingWave::SetDirection(const FVector& NewDirection)
{
	Direction = NewDirection;
}

void ARingWave::SetSpeed(float NewSpeed)
{
	Speed = NewSpeed;
}

void ARingWave::SetPlayerDamage(float NewPlayerDamage)
{
	PlayerDamage = NewPlayerDamage;
}
