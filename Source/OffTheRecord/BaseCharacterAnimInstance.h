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

private:
	//Pointer to base character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class ABaseCharacter* BaseCharacter;

	//Variable for character velocity speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		ECharacterState CharacterState;

public:

};
