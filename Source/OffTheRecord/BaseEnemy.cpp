// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemy.h"


#include "BaseEnemyAnimInstance.h"
#include "BaseEnemyAIController.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "HitColliderComponent.h"


// Sets default values
ABaseEnemy::ABaseEnemy() : HitState(EHitState::EHS_NORMAL), CombatState(ECombatState::ECS_READY), bCharge(false), PowerLevel(150)
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

	LeftAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Left Hand Attack Box"));
	LeftAttackBox->SetupAttachment(GetRootComponent());

	RightAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Right Hand Attack Box"));
	RightAttackBox->SetupAttachment(GetRootComponent());
	
	ChargeAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Charge Attack Box"));
	ChargeAttackBox->SetupAttachment(GetRootComponent());

	JumpAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Jump Attack Box"));
	JumpAttackBox->SetupAttachment(GetRootComponent());

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
	DisableAttackBoxes();
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

void ABaseEnemy::Idle(FName MontageSection)
{
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(IdleMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName(MontageSection));
	}
}

void ABaseEnemy::KnockBack(FVector ForceDirection, int32 PowerLvl)
{
	LaunchCharacter(FVector(ForceDirection.X * PowerLvl, ForceDirection.Y * PowerLvl, 300), false, false);
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
	LaunchCharacter(FVector(ForceDirection.X * PowerLvl, ForceDirection.Y * PowerLvl, 300), false, false);
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

void ABaseEnemy::Attack(FName MontageSection, float AnimSpeed)
{
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(AttackMontage, AnimSpeed);
		AnimInstance->Montage_JumpToSection(FName(MontageSection));
	}
}

void ABaseEnemy::Charge()
{
	UCharacterMovementComponent* EnemyMovement = Cast<UCharacterMovementComponent>(this->GetMovementComponent());
	if (EnemyMovement)
	{
		EnemyMovement->MaxWalkSpeed = 1200.0f;
		EnemyMovement->MaxAcceleration = 1200.0f;
		EnemyMovement->GroundFriction = .5f;
	}
	Attack("Taunt", 1.0f);
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

void ABaseEnemy::DisableAttackBoxes()
{
	LeftAttackBox->DisableCollision();
	RightAttackBox->DisableCollision();
	ChargeAttackBox->DisableCollision();
	JumpAttackBox->DisableCollision();
}

void ABaseEnemy::EnableJumpAttackBox()
{
	UE_LOG(LogTemp, Warning, TEXT("JumpBox Enabled"));
	JumpAttackBox->EnableCollision();
}

void ABaseEnemy::DisableChargeAttackBox()
{
	if (ChargeAttackBox->GetCollisionEnabled()) {
		ChargeAttackBox->DisableCollision();
	}
}

void ABaseEnemy::EnableChargeAttackBox()
{
	if (!ChargeAttackBox->GetCollisionEnabled()) {
		UE_LOG(LogTemp, Warning, TEXT("ChargeBox Enabled"));
		ChargeAttackBox->EnableCollision();
	} 
}
