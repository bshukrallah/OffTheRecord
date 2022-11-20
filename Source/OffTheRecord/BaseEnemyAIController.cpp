// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatusEnums.h"
#include "BaseEnemy.h"

void ABaseEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
		//GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
	}
}

ABaseEnemyAIController::ABaseEnemyAIController()
{
}

// Called every frame
void ABaseEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	UCharacterMovementComponent* EnemyMovement = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	float distance = GetPawn()->GetDistanceTo(PlayerPawn);

	if (LineOfSightTo(PlayerPawn) && distance < 300.0f) {
		GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
		EnemyMovement->MaxWalkSpeed = 550;
		UE_LOG(LogTemp, Warning, TEXT("Distance to Enemy-> %f"), distance);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("Player"));
		EnemyMovement->MaxWalkSpeed = 300;
		UE_LOG(LogTemp, Warning, TEXT("Distance to Enemy-> %f"), distance);
	}*/

}

bool ABaseEnemyAIController::IsDead() const
{
	return false;
}

void ABaseEnemyAIController::SetEnemyAIState(EAIState state)
{
	AIState = state; //for tracking
	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIStatus"), (uint8)state);

}