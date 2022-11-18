// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "StatusEnums.h"
#include "HitColliderComponent.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UHitColliderComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UHitColliderComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool bCollisionEnabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseWeapon* EquippedWeaponOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseCharacter* BaseCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseCharacter* BaseCharacterOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseEnemy* BaseEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		class ABaseEnemy* BaseEnemyOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component Owner", meta = (AllowPrivateAccess = "true"))
		FString ComponentOwner;

	//Hit Collider Type
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		EBoxTypes HitBoxType;

public:
	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void DisableCollision();

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void EnableCollision();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE FString GetColliderOwner() { return ComponentOwner; }

	UFUNCTION(BlueprintCallable)
		void SetType(EBoxTypes NewHitBoxTypes);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE EBoxTypes GetType() { return HitBoxType; }
};
