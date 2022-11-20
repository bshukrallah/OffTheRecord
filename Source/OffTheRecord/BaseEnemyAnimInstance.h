// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBaseEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseEnemyAnimInstance();

protected:
	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

private:
	//Pointer to base character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		class ABaseEnemy* BaseEnemy;

	//Variable for character velocity speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool KnockedBackwards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool KnockedForwards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool KnockedDown;

	UFUNCTION(BlueprintCallable, Category = "Collision Settings")
		void EnableCollision();

	UFUNCTION(BlueprintCallable, Category = "AI Settings")
		void EnableAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bCharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bJumpAttack;

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE void isCharging(bool charge) { bCharge = charge; }
	
	UFUNCTION(BlueprintCallable)
		FORCEINLINE void isJumpAttack(bool JumpAttack) { bJumpAttack = JumpAttack; }

};
