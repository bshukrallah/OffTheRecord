// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatusEnums.h"
#include "BaseEnemy.h"

UBaseEnemyAnimInstance::UBaseEnemyAnimInstance() : Speed(0.f), KnockedBackwards(false), KnockedForwards(false), KnockedDown(false)
{
}

void UBaseEnemyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (BaseEnemy == nullptr)
	{
		BaseEnemy = Cast<ABaseEnemy>(TryGetPawnOwner());
	}
	if (BaseEnemy)
	{
		FVector MovementSpeed(BaseEnemy->GetVelocity());
		MovementSpeed.Z = 0;
		Speed = MovementSpeed.Size();
	}
}
