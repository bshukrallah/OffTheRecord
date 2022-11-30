// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseEnemy.h"


#include "BaseEnemyAnimInstance.h"
#include "BaseEnemyAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "OffTheRecordGameModeBase.h"
#include "HitColliderComponent.h"
#include "Sound/SoundCue.h"
#include "WeaponSpawnComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy() : HitState(EHitState::EHS_NORMAL), CombatState(ECombatState::ECS_READY), bCharge(false), PowerLevel(100), CurrentMatColor(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeftAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Left Hand Attack Box"));
	LeftAttackBox->SetupAttachment(GetRootComponent());

	RightAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Right Hand Attack Box"));
	RightAttackBox->SetupAttachment(GetRootComponent());
	
	ChargeAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Charge Attack Box"));
	ChargeAttackBox->SetupAttachment(GetRootComponent());

	JumpAttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Jump Attack Box"));
	JumpAttackBox->SetupAttachment(GetRootComponent());

	WeaponSpawner = CreateDefaultSubobject<UWeaponSpawnComponent>(TEXT("Weapon Spawner"));
	WeaponSpawner->SetupAttachment(GetRootComponent());

	FrontHitTriggerBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Front Hit Trigger"));
	FrontHitTriggerBox->SetupAttachment(GetRootComponent());
	FrontHitTriggerBox->SetType(EBoxTypes::EBT_FRONT);

	BackHitTriggerBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Back Hit Trigger"));
	BackHitTriggerBox->SetupAttachment(GetRootComponent());
	BackHitTriggerBox->SetType(EBoxTypes::EBT_BACK);

	TopHitTriggerBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Top Hit Trigger"));
	TopHitTriggerBox->SetupAttachment(GetRootComponent());
	TopHitTriggerBox->SetType(EBoxTypes::EBT_TOP);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyMat = GetMesh()->GetMaterial(1);
	DynMat = UMaterialInstanceDynamic::Create(EnemyMat, this);
	GetMesh()->SetMaterial(1, DynMat);
	DynMat->SetVectorParameterValue(TEXT("EnemyColor"), FVector(CurrentMatColor, 0.f, 0.f));
	OTRGameMode = Cast<AOffTheRecordGameModeBase>(UGameplayStatics::GetGameMode(this));
	AIController = Cast<ABaseEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetEnemyAIState(EAIState::EAS_READY);
	}
	DisableAttackBoxes();
}


void ABaseEnemy::PlayImpactSound()
{
	if (ImpactSound)
	{
		UGameplayStatics::PlaySound2D(this, ImpactSound);
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCharge == true ? MatSwap(true, DeltaTime) : MatSwap(false, DeltaTime);
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
	PlayImpactSound();
	DisableHitBoxes();
	DisableAttackBoxes();
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
	PlayImpactSound();
	DisableHitBoxes();
	DisableAttackBoxes();
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
	DisableAttackBoxes();
	PlayImpactSound();
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("ForwardImpact"));
	}
}

void ABaseEnemy::MatSwap(bool Swap, float DeltaTime)
{
	Swap == true ? CurrentMatColor = FMath::FInterpTo(CurrentMatColor, 255.0f, DeltaTime, 1.0f) : CurrentMatColor = FMath::FInterpTo(CurrentMatColor, 0.0f, DeltaTime, 2.0f);

	DynMat->SetVectorParameterValue(TEXT("EnemyColor"), FVector(CurrentMatColor, 0.f, 0.f));
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
	bCharge = true;
}

void ABaseEnemy::Death()
{
	if (OTRGameMode) {
		OTRGameMode->IncreaseScore();
	}
	UBaseEnemyAnimInstance* AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->Montage_Play(FallingMontage, 1.0);
		AnimInstance->Montage_JumpToSection(FName("FallingDeath"));
	}
	FTimerHandle EnemyDeathTimer;
	GetWorldTimerManager().SetTimer(EnemyDeathTimer, this, &ABaseEnemy::DestroyActor, 1.5f, false);
}

void ABaseEnemy::DestroyActor()
{
	Destroy();
}

void ABaseEnemy::DisableHitBoxes()
{
	FrontHitTriggerBox->DisableCollision();
	BackHitTriggerBox->DisableCollision();
	TopHitTriggerBox->DisableCollision();
}

void ABaseEnemy::EnableHitBoxes()
{
	FrontHitTriggerBox->EnableCollision();
	BackHitTriggerBox->EnableCollision();
	TopHitTriggerBox->EnableCollision();
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
	JumpAttackBox->EnableCollision();
}

UWeaponSpawnComponent* ABaseEnemy::GetWeaponSpawner()
{
	return WeaponSpawner;
}

void ABaseEnemy::DisableChargeAttackBox()
{
	if (ChargeAttackBox->GetCollisionEnabled()) {
		ChargeAttackBox->DisableCollision();
		bCharge = false;
	}
}

void ABaseEnemy::EnableChargeAttackBox()
{
	if (!ChargeAttackBox->GetCollisionEnabled()) {
		ChargeAttackBox->EnableCollision();
	} 
}
