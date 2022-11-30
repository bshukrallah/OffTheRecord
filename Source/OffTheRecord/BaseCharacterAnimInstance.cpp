// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)



#include "BaseCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.h"


UBaseCharacterAnimInstance::UBaseCharacterAnimInstance() :
	Speed(0.f), bComboFinal(false), CharacterState(ECharacterState::ECS_UNARMED), bInAir(false)
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
		BaseCharacter->GetMovementComponent()->IsFalling() == true ? bInAir = true : bInAir = false;

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

void UBaseCharacterAnimInstance::PowerUpWeapon()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->PowerUpWeapon();
	}
}

void UBaseCharacterAnimInstance::ConfigureWeaponSound()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->PlayWeaponSwingSound();
	}
}

void UBaseCharacterAnimInstance::EnableJumpTriggerBox()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->EnableAttackBox();
	}
}

void UBaseCharacterAnimInstance::DisableJumpTriggerBox()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->DisableAttackBox();
	}
}

void UBaseCharacterAnimInstance::EnableWeaponCollision()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->EnableWeaponCollision();
	}
}

void UBaseCharacterAnimInstance::DisableWeaponCollision()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->DisableWeaponCollision();
	}
}

void UBaseCharacterAnimInstance::Recover()
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		BaseCharacter->Recover();
	}
}

