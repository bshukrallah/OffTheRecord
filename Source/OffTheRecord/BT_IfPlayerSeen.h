// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BT_IfPlayerSeen.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBT_IfPlayerSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBT_IfPlayerSeen();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
