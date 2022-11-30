// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BT_Service_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class OFFTHERECORD_API UBT_Service_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBT_Service_PlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
