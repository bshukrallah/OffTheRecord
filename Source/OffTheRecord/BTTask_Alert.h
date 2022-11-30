// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Alert.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBTTask_Alert : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Alert();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
