// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BT_IfPlayerSeen.h"
//#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "BaseEnemyAIController.h"
#include "BaseEnemy.h"

UBT_IfPlayerSeen::UBT_IfPlayerSeen()
{
	NodeName = "Activate if Player is seen";
}

void UBT_IfPlayerSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	APawn* PlayerPawn = (UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	float distance = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(PlayerPawn);
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn) && distance < 1200.0f) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		//ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
		//ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(BaseEnemy->GetController());
		//AIController->SetEnemyAIState(EAIState::EAS_IDLE);
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	}

}
