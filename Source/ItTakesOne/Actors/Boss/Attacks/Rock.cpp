// Fill out your copyright notice in the Description page of Project Settings.

#include "Rock.h"

#include "ItTakesOne/Actors/Boss/CoreCrystal.h"
#include "ItTakesOne/Actors/Characters/WindBossCharacter.h"
#include "ItTakesOne/Actors/PlayerStates/SkyPlayerState.h"
#include "Kismet/GameplayStatics.h"

ARock::ARock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName("OverlapOnlyPawn");

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Speed = 4000.f;
	PlayerDamage = 10.f;
	BossDamage = 30.f;
}

void ARock::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARock::OnBeginOverlap);
	Mesh->OnComponentHit.AddDynamic(this, &ARock::OnHit);
}

void ARock::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Controller = OtherActor->GetInstigatorController())
	{
		if (const auto PlayerState = Controller->GetPlayerState<ASkyPlayerState>())
		{
			PlayerState->ApplyDamage(PlayerDamage);
			Destroy();
		}
	}
}

void ARock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                  FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ACoreCrystal::StaticClass()))
	{
		if (const auto Boss = Cast<AWindBossCharacter>(
			UGameplayStatics::GetActorOfClass(this, AWindBossCharacter::StaticClass())))
		{
			Boss->ApplyDamage(BossDamage);
		}
		OtherActor->Destroy();
	}

	Destroy();
}

void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Distance = Direction * Speed * DeltaTime;
	const FVector NewPosition = GetActorLocation() + Distance;
	SetActorLocation(NewPosition, true);
}

void ARock::SetDirection(const FVector& NewDirection)
{
	Direction = NewDirection;
}

void ARock::SetSpeed(float NewSpeed)
{
	Speed = NewSpeed;
}

void ARock::SetPlayerDamage(float NewPlayerDamage)
{
	PlayerDamage = NewPlayerDamage;
}

void ARock::SetBossDamage(float NewBossDamage)
{
	BossDamage = NewBossDamage;
}
