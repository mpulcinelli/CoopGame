// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameMode.h"
#include "SHealthComponent.h"
#include <Engine/Engine.h>




ASGameMode::ASGameMode()
{
	TimeBetweenWaves = 2.0f;
	GameStateClass = ASGameState::StaticClass();
	PlayerStateClass = APlayerState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval= 1.0f;
}

void ASGameMode::StartWave()
{
	WaveCount++;

	NrBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawnner, this, &ASGameMode::SpawnBotTimerElapsed, 1.0f, true, 0.0f);

	SetWaveState(EWaveState::WaveInProgress);
}

void ASGameMode::SpawnBotTimerElapsed()
{
	SpawnNewBot();
	NrBotsToSpawn--;

	if (NrBotsToSpawn<=0.0f)
	{
		EndWave();
	}

}


void ASGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawnner);
	//PrepareForNextWave();
	SetWaveState(EWaveState::WaitingToComplete);
}

void ASGameMode::PrepareForNextWave()
{

	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameMode::StartWave, TimeBetweenWaves, false);
	SetWaveState(EWaveState::WaitingToStart);
	RestartDeadPlayers();
}

void ASGameMode::CheckWaveStatte()
{

	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (NrBotsToSpawn > 0 || bIsPreparingForWave)
	{
		return;
	}

	bool bIsAnyBotAlive = false;

	for (FConstPawnIterator It= GetWorld()->GetPawnIterator(); It;++It)
	{
		APawn* TestPawn = It->Get();

		if (TestPawn == nullptr || TestPawn->IsPlayerControlled()) 
		{
			continue;
		}

		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth()>0.0f)
		{
			bIsAnyBotAlive = true;
			break;
		}
	}

	if (!bIsAnyBotAlive)
	{
		SetWaveState(EWaveState::WaveComplete);
		PrepareForNextWave();
	}
	
}

void ASGameMode::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()));
			if(ensure(HealthComp) && HealthComp->GetHealth() > 0.0f)
			{
				return;
			}
		}
	}

	GameOver();

}

void ASGameMode::GameOver()
{
	EndWave();

	SetWaveState(EWaveState::GameOver);
	// @TODO>

}

void ASGameMode::SetWaveState(EWaveState NewWaveState)
{
	ASGameState* GS = GetGameState<ASGameState>();
	if (ensureAlways(GS))
	{
		GS->SetWaveState (NewWaveState);
	}
}

void ASGameMode::RestartDeadPlayers()
{

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() ==nullptr)
		{
			RestartPlayer(PC);
		}
	}


}

bool ASGameMode::HasPlayersToPlay()
{
	int32 CountPlayer = 0;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() != nullptr)
		{
			CountPlayer++;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, FString::FormatAsNumber(CountPlayer));

	if (CountPlayer>1)
	{
		return true;
	}

	return false;
}

void ASGameMode::StartPlay()
{
	Super::StartPlay();
	
	if (HasPlayersToPlay()) 
	{
		PrepareForNextWave();
	}
	

}

void ASGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasPlayersToPlay())
	{
		CheckWaveStatte();
		CheckAnyPlayerAlive();
	}
}
