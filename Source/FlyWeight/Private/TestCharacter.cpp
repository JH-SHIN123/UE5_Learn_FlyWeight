// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

#include "Engine/AssetManager.h"
#include "../WeaponDataAsset.h"
#include "../Public/Weapon.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	mCurrentWeapon = Cast<AWeapon>(GetWorld()->SpawnActor(AWeapon::StaticClass()));
	mCurrentWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestCharacter::EquipWeapon(FPrimaryAssetId WeaponID)
{
	if (false == WeaponID.IsValid())
		return;

	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> AssetsToLoad;
	TArray<FName> AddBundle;
	AssetsToLoad.Add(WeaponID);

	AssetManager.LoadPrimaryAssets(AssetsToLoad, AddBundle,
		FStreamableDelegate::CreateUObject(this, &ATestCharacter::OnWeaponLoaded, WeaponID));
}

void ATestCharacter::OnWeaponLoaded(FPrimaryAssetId LoadedID)
{
	UAssetManager& AssetManager = UAssetManager::Get();

	UWeaponDataAsset* WeaponData = Cast<UWeaponDataAsset>(
		AssetManager.GetPrimaryAssetObject(LoadedID));

	if (WeaponData)
	{
		// 주의: WeaponData 내부의 Mesh가 TSoftObjectPtr라면 그것도 로드해야 함.
		// 보통은 DataAsset 자체를 로드하면 내부의 하드 레퍼런스는 같이 로드됨.

		if (mCurrentWeapon)
		{
			// 여기서 WeaponData->WeaponMesh가 로드되어있다고 가정
			// (만약 TSoftObjectPtr라면 .LoadSynchronous() 또는 체인 로딩 필요)			
			mCurrentWeapon->SetMesh(WeaponData->WeaponMesh.LoadSynchronous());
		}
	}
}

