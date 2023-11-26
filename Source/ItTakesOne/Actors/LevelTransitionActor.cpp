// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ItTakesOne/ItTakesOneCharacter.h"

// Sets default values
ALevelTransitionActor::ALevelTransitionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	RootComponent = BoxCollisionComponent;

	BoxCollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualComponent"));
	VisualComponent->SetupAttachment(RootComponent);

	// Bind the overlap event
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelTransitionActor::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ALevelTransitionActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALevelTransitionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransitionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		// Assuming your player class is called AYourPlayerClass, replace it with your actual player class
		if (OtherActor->IsA(AItTakesOneCharacter::StaticClass()))
		{
			// Switch level on collision with player
			UGameplayStatics::OpenLevel(this, LevelToLoad);
		}
	}
}
