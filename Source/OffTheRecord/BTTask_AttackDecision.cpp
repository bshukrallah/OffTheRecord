// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BTTask_AttackDecision.h"
#include "AIController.h"
#include "BaseEnemyAIController.h"

UBTTask_AttackDecision::UBTTask_AttackDecision()
{
}

EBTNodeResult::Type UBTTask_AttackDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Deciding..."));
	int32 AttackChoice = FMath::RandRange(1, 6);
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (AIController) {
		switch (AttackChoice)
		{
		case 1: 
		case 2:
		case 3: 
		case 4:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP1);
			UE_LOG(LogTemp, Warning, TEXT("A1"));
			break;

		case 5:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP2);
			UE_LOG(LogTemp, Warning, TEXT("A2"));
			break;

		case 6:
			AIController->SetEnemyAIState(EAIState::EAS_ATTACKP3);
			UE_LOG(LogTemp, Warning, TEXT("A3"));

		}
	}
	return EBTNodeResult::Type();
}
