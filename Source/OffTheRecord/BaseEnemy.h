// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatusEnums.h"
#include "BaseEnemy.generated.h"

UCLASS()
class OFFTHERECORD_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UHitColliderComponent* FrontHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UHitColliderComponent* BackHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UHitColliderComponent* TopHitBox;

	//Character Hit Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		EHitState HitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* FallingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ECombatState CombatState;

	class ABaseEnemyAIController* AIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bCharge;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void KnockBack(FVector ForceDirection, int32 PowerLvl);

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void BackGetUp();

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void FrontGetUp();

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void KnockForward(FVector ForceDirection, int32 PowerLvl);

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void KnockDown();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE EHitState GetHitState() const { return HitState; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE ECombatState GetCombatState() const { return CombatState; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCombatState(ECombatState CState) { CombatState = CState; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetHitState(EHitState 
			eHitState) { HitState = eHitState; }

	UFUNCTION(BlueprintCallable)
		void ResetState();

	UFUNCTION(BlueprintCallable)
		void ResetAI();

	UFUNCTION(BlueprintCallable)
		void SetFallState(EHitState eHitState);

	UFUNCTION(BlueprintCallable)
		void Attack(FName MontageSection, bool isJumpAttack);

	UFUNCTION(BlueprintCallable)
		void Charge();

	void DisableHitBoxes();
	void EnableHitBoxes();

};
