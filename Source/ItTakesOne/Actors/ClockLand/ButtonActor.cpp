// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

// Sets default values
AButtonActor::AButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AButtonActor::OnOverlapBegin);

	// Initialize static mesh
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(RootComponent); // Attaching the mesh to the root component

	bIsActivated = false;
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AItTakesOneCharacter* Character = Cast<AItTakesOneCharacter>(OtherActor);
	if (Character)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("button pressed"));
		}

		if (!bIsActivated)
		{
			bIsActivated = true;

			GetWorldTimerManager().SetTimer(TimerHandle, this, &AButtonActor::DeactivateButton, 1.0f, false);
		}
	}
}

void AButtonActor::DeactivateButton()
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("button deactivate"));
	}

	bIsActivated = false;
}

