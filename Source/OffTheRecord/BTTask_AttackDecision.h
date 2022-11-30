// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackDecision.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBTTask_AttackDecision : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AttackDecision();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
