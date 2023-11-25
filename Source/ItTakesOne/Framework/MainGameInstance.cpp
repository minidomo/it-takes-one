// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{
}

void UMainGameInstance::Init()
{
	Super::Init();
	/*
	 * load save file
	 */
	UE_LOG(LogTemp, Display, TEXT("%s: init"), *GetName());
}

void UMainGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Display, TEXT("%s: shutdown"), *GetName());
}
