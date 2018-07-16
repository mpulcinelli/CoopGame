// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <TimerManager.h>

#include "SGameState.h"
#include "SPlayerState.h"
#include <GameFramework/Controller.h>
#include "SGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor);

enum class EWaveState: uint8;

/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	int32 NrBotsToSpawn;
	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category="GameMode")
	float TimeBetweenWaves;

	FTimerHandle TimerHandle_BotSpawnner;
	FTimerHandle TimerHandle_NextWaveStart;

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnNewBot();
	
	void SpawnBotTimerElapsed();

	void StartWave();

	void EndWave();

	void PrepareForNextWave();
	
	void CheckWaveStatte();

	void CheckAnyPlayerAlive();

	void GameOver();

	void SetWaveState(EWaveState NewWaveState);

	void RestartDeadPlayers();

	bool HasPlayersToPlay();

public:

	ASGameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category="GameMode")
	FOnActorKilled OnActorKilled;
};
