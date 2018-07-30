// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayerState.h"




void ASPlayerState::AddScore(float ScoreDelta)
{
	Score = Score + ScoreDelta;
}

void ASPlayerState::SubScore(float ScoreDelta)
{
	Score = Score - ScoreDelta;
}


void ASPlayerState::AddCredits(int32 CreditsDelta)
{
	PLayerCredits = PLayerCredits + CreditsDelta;
}

void ASPlayerState::SubCredits(int32 CreditsDelta)
{
	PLayerCredits = PLayerCredits - CreditsDelta;
}

