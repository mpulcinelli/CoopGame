// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category="Player Score")
	void AddScore(float ScoreDelta);
	
	UFUNCTION(BlueprintCallable, Category = "Player Score")
	void SubScore(float ScoreDelta);

	UFUNCTION(BlueprintCallable, Category = "Player Credits")
	void AddCredits(float CreditsDelta);

	UFUNCTION(BlueprintCallable, Category = "Player Credits")
	void SubCredits(float CreditsDelta);
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Credits")
	float  PLayerCredits;
};
