// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"


//Weapon status for weapons
UENUM(BlueprintType)
enum class EWeaponStatus : uint8
{
	//Weapon on ground - able to be picked up
	EWS_WEAPONPICKUP UMETA(DisplayName = "Weapon Drop"),
	EWS_WEAPONFALLING UMETA(DisplayName = "Weapon Falling"),
	//Equipped version of weapon
	EWS_WEAPONEQUIPPED UMETA(DisplayName = "Weapon Equipped"),

	EWS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class OFFTHERECORD_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void StopFalling();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

	//Weapon Enum Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		EWeaponStatus WeaponStatus;

	//Enables Item tracing when overlapped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* PickUpTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAttackTriggerComponent* AttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* WeaponSwingAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, meta = (AllowPrivateAccess = "true"))
		class USoundCue* WeaponSwingCue;

	float FallingWeaponTime;

	bool bOrientWeapon;
	int32 PowerUpLevel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DropWeapon(); //Adds impulse to weapon when dropped
	void SpawnWeapon(); //Adds impulse to weapon when spawned

	void PlayWeaponSwingSound(int8 type); //Adds impulse to weapon when spawned

	FORCEINLINE UBoxComponent* GetPickUpTrigger() const { return PickUpTrigger; }
	FORCEINLINE EWeaponStatus GetWeaponStatus() const { return WeaponStatus; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	UFUNCTION(BlueprintCallable, Category = Items, meta = (AllowPrivateAccess = "true"))
		void SetWeaponStatus(EWeaponStatus Status);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetPowerLevel() { return PowerUpLevel; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetPowerLevel(int32 PowerLevel) { PowerUpLevel = PowerLevel; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UAttackTriggerComponent* GetAttackBox() { return AttackBox; }

};
