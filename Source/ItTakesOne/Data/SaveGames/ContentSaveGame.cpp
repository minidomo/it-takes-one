// Fill out your copyright notice in the Description page of Project Settings.

#include "ContentSaveGame.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "ItTakesOne/Data/SaveGameArchive.h"

UContentSaveGame::UContentSaveGame()
{
}

bool UContentSaveGame::LoadActor(AActor* Actor, FActorSaveData& Data)
{
	if (!Actor)
	{
		return false;
	}

	Actor->SetActorLocationAndRotation(Data.Transform.GetLocation(), Data.Transform.GetRotation());
	Actor->SetActorScale3D(Data.Transform.GetScale3D());

	FMemoryReader MemReader(Data.ByteData);
	FSaveGameArchive Ar(MemReader);
	Actor->Serialize(Ar);
	return true;
}

bool UContentSaveGame::SaveActor(AActor* Actor, FActorSaveData& Data)
{
	if (!Actor)
	{
		return false;
	}

	Data.Name = Actor->GetFName();
	Data.Class = Actor->GetClass();
	Data.Transform = Actor->GetTransform();
	Data.bDeferLoad = Actor->IsA(APlayerState::StaticClass());

	FMemoryWriter MemWriter(Data.ByteData);
	FSaveGameArchive Ar(MemWriter);
	Actor->Serialize(Ar);
	return true;
}

FActorSaveData* UContentSaveGame::FindData(TArray<FActorSaveData>& ActorData, const AActor* Actor)
{
	for (auto& Data : ActorData)
	{
		if (Data.Name == Actor->GetFName())
		{
			return &Data;
		}

		// check for classes that only have one instance
		if (Data.Class == Actor->GetClass())
		{
			if (Actor->IsA(AGameStateBase::StaticClass()) || Actor->IsA(APlayerState::StaticClass()))
			{
				return &Data;
			}
		}
	}

	return nullptr;
}
