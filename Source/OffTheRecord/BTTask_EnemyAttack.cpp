// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_EnemyAttack.h"
#include "BaseEnemyAIController.h"
#include "BaseEnemy.h"

UBTTask_EnemyAttack::UBTTask_EnemyAttack()
{
}

EBTNodeResult::Type UBTTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (BaseEnemy) {
		ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
		if (AIController) {
			EAIState AIState = AIController->GetAIState();
			switch (AIState)
			{
			case EAIState::EAS_ATTACKP1:
				BaseEnemy->Attack("Punch1", false);
				break;

			case EAIState::EAS_ATTACKP2:
				BaseEnemy->Attack("JumpAttack", true);
				break;

			case EAIState::EAS_ATTACKP3:
				return EBTNodeResult::Type();
			}
		}
	}
	return EBTNodeResult::Type();
}
