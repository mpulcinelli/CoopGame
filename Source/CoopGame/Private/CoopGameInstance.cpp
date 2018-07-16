// Fill out your copyright notice in the Description page of Project Settings.

#include "CoopGameInstance.h"
#include "GameFramework/PlayerController.h"


UCoopGameInstance::UCoopGameInstance()
{

}

void UCoopGameInstance::Init()
{

}

void UCoopGameInstance::Host()
{
	UWorld* W = GetWorld();
	if(W)
	{
		W->ServerTravel("/Game/Maps/Blockout_P?listen");
	}
}

void UCoopGameInstance::Join(const FString& Address)
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC)
	{
		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
