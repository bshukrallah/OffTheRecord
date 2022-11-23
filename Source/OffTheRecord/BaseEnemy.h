// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatusEnums.h"
#include "AttackTriggerComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAttackTriggerComponent* LeftAttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAttackTriggerComponent* RightAttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAttackTriggerComponent* ChargeAttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAttackTriggerComponent* JumpAttackBox;

	//Character Hit Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		EHitState HitState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* FallingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* IdleMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ECombatState CombatState;

	class ABaseEnemyAIController* AIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bCharge;

	int32 PowerLevel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void Idle(FName MontageSection);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void KnockBack(FVector ForceDirection, int32 PowerLvl);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void BackGetUp();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void FrontGetUp();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void KnockForward(FVector ForceDirection, int32 PowerLvl);

	UFUNCTION(BlueprintCallable, Category = "Actions")
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
		void Attack(FName MontageSection, float AnimSpeed);

	UFUNCTION(BlueprintCallable)
		void Charge();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetPowerLevel(int32 Power) { PowerLevel = Power; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetPowerLevel() { return PowerLevel; }

	void DisableHitBoxes();
	void EnableHitBoxes();

	void DisableAttackBoxes();

	FORCEINLINE void EnableRightAttackBox() { RightAttackBox->EnableCollision(); }
	FORCEINLINE void EnableLeftAttackBox() { LeftAttackBox->EnableCollision(); }
	FORCEINLINE void EnableJumpAttackBox();

	void DisableChargeAttackBox();
	void EnableChargeAttackBox();

};
