// Fill out your copyright notice in the Description page of Project Settings.

#include "ContentSaveGame.h"

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

	Data.bLoaded = true;
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
