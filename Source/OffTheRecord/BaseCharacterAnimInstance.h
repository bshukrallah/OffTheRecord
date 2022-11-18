// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once


#include "CoreMinimal.h"
#include "StatusEnums.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UBaseCharacterAnimInstance(); //constructor

protected:
	//Function that will run consistently controlling animation params
	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void FinishAttack();

	UFUNCTION(BlueprintCallable)
		void ComboHit();

	UFUNCTION(BlueprintCallable)
		void ComboMiss();

	UFUNCTION(BlueprintCallable)
		void PowerUpWeapon();

	UFUNCTION(BlueprintCallable)
		void ConfigureWeaponSound();

private:
	//Pointer to base character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		class ABaseCharacter* BaseCharacter;

	//Variable for character velocity speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerState, meta = (AllowPrivateAccess = "true"))
		ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerState, meta = (AllowPrivateAccess = "true"))
		EComboState ComboState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerState, meta = (AllowPrivateAccess = "true"))
		bool bComboFinal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerMovement, meta = (AllowPrivateAccess = "true"))
		bool bInAir;

public:

	//Used in the animation blueprint to play full body animation for final combo hit
	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetComboFinal(bool final) { bComboFinal = final; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool GetComboFinal() { return bComboFinal; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCharacterState(ECharacterState state) { CharacterState = state; }

	UFUNCTION(BlueprintCallable)
		void EnableJumpTriggerBox();

	UFUNCTION(BlueprintCallable)
		void DisableJumpTriggerBox();

	UFUNCTION(BlueprintCallable)
		void EnableWeaponCollision();

	UFUNCTION(BlueprintCallable)
		void DisableWeaponCollision();

};
