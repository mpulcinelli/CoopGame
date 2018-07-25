// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "SPowerupActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

protected:


	/*Time between Ticks*/
	UPROPERTY(EditDefaultsOnly, Category="Powerups")
	float PowerupInterval;

	/* Total times we apply the powerup effect */
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	int32 TotalNrOfTicks;

	FTimerHandle TimerHandle_PowerupTick;

	int32 TicksProcessed;

	UFUNCTION()
	void OnTickPowerup();

	UPROPERTY(ReplicatedUsing = OnRep_PowerupActive)
	bool bIsPowerupActive;
	
	UFUNCTION()
	void OnRep_PowerupActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerupStateChanged(bool bNewIsActive);
public:	

	void ActivatePowerup(AActor* ActivateFor);

	UFUNCTION(BlueprintImplementableEvent, Category="Powerups")
	void OnActivated(AActor* ActivateFor);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerupTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnExpired();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Reward")
		float RewardValue;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Reward")
		float PlayerRewardPercentage;
};
