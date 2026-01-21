// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FLYWEIGHT_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Visual")
	USoundBase* AttackSound;

	// 이 함수를 오버라이드 해야 에셋 매니저가 인식함
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		// 에셋의 파일 이름을 ID로 사용 (예: WeaponData:BP_Sword)
		// "WeaponData"는 태그(Type) 역할을 함
		return FPrimaryAssetId("WeaponData", GetFName());
	}
};
