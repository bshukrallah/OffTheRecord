// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)



#include "BaseCharacterAnimInstance.h"
#include "BaseCharacter.h"


UBaseCharacterAnimInstance::UBaseCharacterAnimInstance() :
	Speed(0.f), bComboFinal(false), CharacterState(ECharacterState::ECS_UNARMED)
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
		//CharacterState = BaseCharacter->GetCharacterStatus();
		//BaseCharacter->GetComboState() == EComboState::ECS_COMBO2 ? bComboFinal = true : bComboFinal = false;
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

void UBaseCharacterAnimInstance::ComboHit()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->ComboHit();
	}
}

void UBaseCharacterAnimInstance::ComboMiss()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->ComboMiss();
	}
}

