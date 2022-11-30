// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	//Idle State
	EAS_IDLE UMETA(DisplayName = "Idle"),
	//Ready to attack
	EAS_READY UMETA(DisplayName = "AI Ready"),
	//Not allowed to attack
	EAS_NOTREADY UMETA(DisplayName = "AI Not Ready"),
	//Attack Patterns
	//1 Regular Attack
	//2 Jump Attack
	//3 Charge Attack
	EAS_ATTACKP1 UMETA(DisplayName = "Attack Pattern 1"),
	EAS_ATTACKP2 UMETA(DisplayName = "Attack Pattern 2"),
	EAS_ATTACKP3 UMETA(DisplayName = "Attack Pattern 3"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class OFFTHERECORD_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	ABaseEnemyAIController();
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;

	EAIState AIState;

public:
	UFUNCTION(BlueprintCallable, Category = "AI State")
		void SetEnemyAIState(EAIState state);

	UFUNCTION(BlueprintCallable, Category = "AI State")
		FORCEINLINE EAIState GetAIState() { return AIState; }
};
