// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_EnemyIdle.h"
#include "BaseEnemy.h"
#include "BaseEnemyAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_EnemyIdle::UBTTask_EnemyIdle()
{
}

EBTNodeResult::Type UBTTask_EnemyIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int32 IdleChoice = FMath::RandRange(1, 3);

	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
	if (AIController->GetAIState() != EAIState::EAS_IDLE) {
		if (AIController) AIController->SetEnemyAIState(EAIState::EAS_IDLE);
		//OwnerComp.GetBlackboardComponent()->ClearValue("Player");
		if (BaseEnemy) {
			switch (IdleChoice)
			{
			case 1:
				BaseEnemy->Idle("Dance1");
				break;

			case 2:
				BaseEnemy->Idle("Dance2");
				break;

			case 3:
				BaseEnemy->Idle("Dance3");
			}
		}
	}
	return EBTNodeResult::Type();
}
