// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayerState.h"




void ASPlayerState::AddScore(float ScoreDelta)
{
	//UE_LOG(LogTemp, Warning, TEXT("Somou"));
	UE_LOG(LogTemp, Warning, TEXT("MyCharacter's score is %f"), Score);
	UE_LOG(LogTemp, Warning, TEXT("The delta to sum is %f"), ScoreDelta);
	Score = Score + ScoreDelta;
}

void ASPlayerState::SubScore(float ScoreDelta)
{
	Score = Score - ScoreDelta;
}


void ASPlayerState::AddCredits(float CreditsDelta)
{
	PLayerCredits = PLayerCredits + CreditsDelta;
}

void ASPlayerState::SubCredits(float CreditsDelta)
{
	PLayerCredits = PLayerCredits - CreditsDelta;
}

