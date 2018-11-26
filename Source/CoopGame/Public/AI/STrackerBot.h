// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Core/Public/Math/Vector.h"

//#include "AI/Navigation/NavigationSystem.h"
//#include "AI/Navigation/NavigationPath.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "SHealthComponent.h"
#include "SCharacter.h"
#include <Sound/SoundCue.h>
#include "STrackerBot.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class COOPGAME_API ASTrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	FVector GetNextPathPoint();

	UFUNCTION()
	void HandleTakeDamage(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnCheckNearbyBots();

	void SelfDestruct();

	void DamageSelf();

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;
	
	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, Category="TrackerBot")
	float MovimentForce;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	bool bUSeVelocityChage;
	
	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float RequiredDistanceToTarget;
		
	UMaterialInstanceDynamic* MatInst;
	
	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	UParticleSystem* ExplosionEffect;

	bool bExploded;

	bool bStartedSelfDestruction = false;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float SelfDamageInterval;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float ExplosionDamage;

	FTimerHandle TimerHandle_SelfDamage;
	
	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	USoundCue* SelfDestructSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	USoundCue* ExplodeSound;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	int PowerLevel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
