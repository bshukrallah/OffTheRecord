// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_Surprise.h"
#include "BaseEnemy.h"
#include "BaseEnemyAIController.h"
#include "AIController.h"

UBTTask_Surprise::UBTTask_Surprise()
{
}

EBTNodeResult::Type UBTTask_Surprise::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (BaseEnemy) {
		BaseEnemy->Idle("Surprise");
	}

	return EBTNodeResult::Type();
}
