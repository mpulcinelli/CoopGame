// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoopGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API UCoopGameInstance : public UGameInstance
{
	GENERATED_BODY()




public:
	UCoopGameInstance();

	virtual void Init() override;
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

};
