// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemy.h"
#include "BaseRecord.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HitColliderComponent.h"
#include "BaseEnemyAnimInstance.h"
#include "BaseEnemyAIController.h"

// Sets default values
ABaseEnemy::ABaseEnemy() : HitState(EHitState::EHS_NORMAL), CombatState(ECombatState::ECS_READY), bCharge(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Front Hit Box"));
	FrontHitBox->SetupAttachment(GetRootComponent());
	FrontHitBox->SetType(EBoxTypes::EBT_FRONT);

	BackHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Back Hit Box"));
	BackHitBox->SetupAttachment(GetRootComponent());
	BackHitBox->SetType(EBoxTypes::EBT_BACK);

	TopHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Top Hit Box"));
	TopHitBox->SetupAttachment(GetRootComponent());
	TopHitBox->SetType(EBoxTypes::EBT_TOP);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ABaseEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetEnemyAIState(EAIState::EAS_READY);
	}
}


// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::KnockBack(FVector ForceDirection, int32 PowerLvl)
{
	LaunchCharacter(FVector(ForceDirection.X * (PowerLvl*2), ForceDirection.Y * (PowerLvl*2), 200), false, false);
	SetFallState(EHitState::EHS_FALLBACK);
	DisableHitBoxes();
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("FallBack"));
	}

}

void ABaseEnemy::BackGetUp()
{
	HitState = EHitState::EHS_GETTINGUP;
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("GetUpBack"));
	}
	EnableHitBoxes();
}

void ABaseEnemy::KnockForward(FVector ForceDirection, int32 PowerLvl)
{
	LaunchCharacter(FVector(ForceDirection.X * PowerLvl, ForceDirection.Y * PowerLvl, 200), false, false);
	SetFallState(EHitState::EHS_FALLFORWARD);
	DisableHitBoxes();
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("FallForwards"));
	}
}

void ABaseEnemy::FrontGetUp()
{
	HitState = EHitState::EHS_GETTINGUP;
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("ForwardImpact"));
	}
	EnableHitBoxes();
}

void ABaseEnemy::KnockDown()
{
	SetFallState(EHitState::EHS_KNOCKEDDOWN);
	DisableHitBoxes();
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("ForwardImpact"));
	}
}

void ABaseEnemy::ResetState()
{
	CombatState = ECombatState::ECS_READY;
	HitState = EHitState::EHS_NORMAL;
}

void ABaseEnemy::ResetAI()
{
	if (AIController)
	{
		AIController->SetEnemyAIState(EAIState::EAS_READY);
	}
}

void ABaseEnemy::SetFallState(EHitState eHitState)
{
	SetHitState(eHitState);
	SetCombatState(ECombatState::ECS_NOTREADY);
	if (AIController)
	{
		AIController->SetEnemyAIState(EAIState::EAS_NOTREADY);
	}
}

void ABaseEnemy::Attack(FName MontageSection, bool IsJumpAttack)
{
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATTACK!"));
		AnimInstance->Montage_Play(AttackMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName(MontageSection));
		IsJumpAttack == true ? AnimInstance->isJumpAttack(true) : AnimInstance->isJumpAttack(false);
	}
}

void ABaseEnemy::Charge()
{
}

void ABaseEnemy::DisableHitBoxes()
{
	FrontHitBox->DisableCollision();
	BackHitBox->DisableCollision();
	TopHitBox->DisableCollision();
}

void ABaseEnemy::EnableHitBoxes()
{
	FrontHitBox->EnableCollision();
	BackHitBox->EnableCollision();
	TopHitBox->EnableCollision();
}
