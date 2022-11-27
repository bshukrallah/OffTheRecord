// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_EnemyAttack.h"
#include "BaseEnemyAIController.h"
#include "BaseEnemy.h"

UBTTask_EnemyAttack::UBTTask_EnemyAttack()
{
}

EBTNodeResult::Type UBTTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int32 AttackChoice = FMath::RandRange(1, 2);
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (BaseEnemy) {
		ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
		if (AIController) {
			EAIState AIState = AIController->GetAIState();
			switch (AIState)
			{
			case EAIState::EAS_ATTACKP1:
				BaseEnemy->SetPowerLevel(150);
				AttackChoice == 1 ? BaseEnemy->Attack("Punch1", 1.0f) : BaseEnemy->Attack("Punch2", 1.0f);
				break;

			case EAIState::EAS_ATTACKP2:
				BaseEnemy->SetPowerLevel(300);
				BaseEnemy->Attack("JumpAttack", 1.4f);
				break;

			case EAIState::EAS_ATTACKP3:
				BaseEnemy->SetPowerLevel(500);
				BaseEnemy->Charge();
			}
		}
	}
	return EBTNodeResult::Type();
}
