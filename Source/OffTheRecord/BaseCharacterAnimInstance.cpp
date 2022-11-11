// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)



#include "BaseCharacterAnimInstance.h"
#include "BaseCharacter.h"


UBaseCharacterAnimInstance::UBaseCharacterAnimInstance() :
	Speed(0.f)
{
}

void UBaseCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		FVector MovementSpeed(BaseCharacter->GetVelocity());
		MovementSpeed.Z = 0; //zero out z axis
		Speed = MovementSpeed.Size();
		CharacterState = BaseCharacter->GetCharacterStatus();
	}
}

void UBaseCharacterAnimInstance::FinishAttack()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->FinishAttack();
	}
}

