// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_AttackDecision.h"
#include "AIController.h"
#include "BaseEnemyAIController.h"
#include "BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_AttackDecision::UBTTask_AttackDecision()
{
}

EBTNodeResult::Type UBTTask_AttackDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int32 AttackChoice = FMath::RandRange(1, 6);
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
	UCharacterMovementComponent* EnemyMovement = Cast<UCharacterMovementComponent>(BaseEnemy->GetMovementComponent());
	if (EnemyMovement)
	{
		EnemyMovement->MaxWalkSpeed = 800.0f;
		EnemyMovement->MaxAcceleration = 300.0f;
		EnemyMovement->GroundFriction = 1.0f;
	}

	if (AIController) {
		switch (AttackChoice)
		{
		case 1: 
		case 2:
		case 3: 
		case 4:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP1);
			break;

		case 5:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP2);
			break;

		case 6:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP3);

		}
	}
	return EBTNodeResult::Type();
}
