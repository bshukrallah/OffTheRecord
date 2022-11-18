// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
	}
}

// Called every frame
void ABaseEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* Enemy = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(PlayerPawn)) {
		GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		Enemy->MaxWalkSpeed = 550;
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("Player"));
		Enemy->MaxWalkSpeed = 300;
	}
}

bool ABaseEnemyAIController::IsDead() const
{
	return false;
}
