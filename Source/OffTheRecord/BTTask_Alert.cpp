// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_Alert.h"
#include "BaseEnemy.h"
#include "BaseEnemyAIController.h"

UBTTask_Alert::UBTTask_Alert()
{
}

EBTNodeResult::Type UBTTask_Alert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
	if (AIController) AIController->SetEnemyAIState(EAIState::EAS_READY);
	return EBTNodeResult::Type();
}
