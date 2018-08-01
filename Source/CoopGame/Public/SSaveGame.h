// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API USSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	USSaveGame();

		
	UPROPERTY(EditAnywhere)
	float PlayerScore;
	
	UPROPERTY(EditAnywhere)
	float PLayerCredits;
};
