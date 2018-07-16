// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "DrawDebugHelpers.h"
#include <GameFramework/DamageType.h>
#include <Particles/ParticleSystem.h>
#include <Particles/ParticleSystemComponent.h>
#include "CoopGame.h"
#include <PhysicalMaterials/PhysicalMaterial.h>
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;

USTRUCT()
struct FHitScanTrace
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;
	UPROPERTY()
	FVector_NetQuantize TraceTo;
};

UCLASS()
class COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();




	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	void StopFire();


protected:

	virtual void BeginPlay() override;

	virtual void Fire();

	void CheckOwnerNoExistsToDestroyMyself();

	void PlayImpactEffect(EPhysicalSurface SurfaceType, FVector ImpactPoint);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* MeshComp;


	void PlayFireEffect(FVector TracerEndPoint);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float BaseDamage;

	FTimerHandle TimerHandle_TimeBetweemShots;

	float LastFireTime;
	
	/* RPM - Bullets Per Minutes Fired */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	/* Bullets Spread in Degrees */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin=0.0f))
	float BulletSpread;

	float TimeBetweenShots;

	UPROPERTY(ReplicatedUsing=OnRep_HitScanTrace)
	FHitScanTrace HitScanTrace;

	UFUNCTION()
	void OnRep_HitScanTrace();

};
