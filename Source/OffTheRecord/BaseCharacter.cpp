// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseCharacter.h"
#include "BaseCharacterAnimInstance.h"
#include "BaseWeapon.h"
#include "BaseEnemy.h"
#include "BaseRecord.h"

#include "AttackTriggerComponent.h"

#include "Camera/CameraComponent.h"

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Engine/SkeletalMeshSocket.h"

#include "GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "HitColliderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Camera/CameraShakeBase.h"

#include "Sound/SoundCue.h"
#include "OffTheRecordGameModeBase.h"


// Sets default values
ABaseCharacter::ABaseCharacter() :
	CharacterState(ECharacterState::ECS_UNARMED),
	OverlappedWeaponCount(0), OverlappedEnemyCount(0),
	//Character States
	CombatState(ECombatState::ECS_NOTREADY), ComboState(EComboState::ECS_NOCOMBO),
	//Attack Vars
	bAttackButtonHeld(false), PowerUpCounter(100),
	//Camera
	bZoomCam(false), CurrentTargetLength(500.f), bDynamicRotation(false), CurrentPitch(-35.f), DefaultDynamicYaw(0.f), DynamicYawSpeed(2.f),
	bDisableMovement(false),
	bGamePaused(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetRelativeRotation(FRotator(-35.f, 0.f, DefaultDynamicYaw));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetFieldOfView(105.f);

	CameraControl = CreateDefaultSubobject<USphereComponent>(TEXT("CameraController"));
	CameraControl->SetupAttachment(GetRootComponent());
	CameraControl->SetRelativeScale3D(FVector(8.0f, 8.0f, 8.0f));

	//Trigger for Attacking
	AttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Attack Trigger Box"));
	AttackBox->SetupAttachment(GetRootComponent());

	FrontHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Front Hit Box"));
	FrontHitBox->SetupAttachment(GetRootComponent());
	FrontHitBox->SetType(EBoxTypes::EBT_FRONT);

	BackHitBox = CreateDefaultSubobject<UHitColliderComponent>(TEXT("Back Hit Box"));
	BackHitBox->SetupAttachment(GetRootComponent());
	BackHitBox->SetType(EBoxTypes::EBT_BACK);

	//Character movement settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; //Character moves in direction of input
	GetCharacterMovement()->JumpZVelocity = 900.f;
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentDynamicYaw = DefaultDynamicYaw;
	OTRGameMode = Cast<AOffTheRecordGameModeBase>(UGameplayStatics::GetGameMode(this));
	CameraControl->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnOverlap);
	CameraControl->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::OnEndOverlap);

	if (StartingWeapon) {
		StartWeapon = GetWorld()->SpawnActor<AActor>(StartingWeapon);
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("Hand_RSocket"));
		if (HandSocket)
		{
			HandSocket->AttachActor(StartWeapon, GetMesh());
		}
	}
}

void ABaseCharacter::Pause()
{
	if (bGamePaused) {
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		bGamePaused = false;
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		bGamePaused = true;
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DynamicCamera(DeltaTime);
}

//Set up player input
void ABaseCharacter::SetupControls()
{
	static bool bindingsAdded = false;
	if (!bindingsAdded)
	{
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ForwardMotion", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ForwardMotion", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ForwardMotion", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LateralMotion", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LateralMotion", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LateralMotion", EKeys::Gamepad_LeftX, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Jump", EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Jump", EKeys::Gamepad_FaceButton_Bottom));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("AttackSetup", EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("AttackSetup", EKeys::Gamepad_FaceButton_Left));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Pause", EKeys::P));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Pause", EKeys::P));

		bindingsAdded = true;
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupControls();

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ForwardMotion", this, &ABaseCharacter::ForwardMotion);
	PlayerInputComponent->BindAxis("LateralMotion", this, &ABaseCharacter::LateralMotion);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("AttackSetup", IE_Pressed, this, &ABaseCharacter::AttackSetup);
	PlayerInputComponent->BindAction("AttackSetup", IE_Released, this, &ABaseCharacter::AttackRelease);

	FInputActionBinding& toggle = InputComponent->BindAction("Pause", IE_Pressed, this, &ABaseCharacter::Pause);
	toggle.bExecuteWhenPaused = true;
}


//Forward & backward movement
void ABaseCharacter::ForwardMotion(float Value)
{
	if (bDisableMovement) return;
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);
	}
}

//Left & right movement
void ABaseCharacter::LateralMotion(float Value)
{
	if (bDisableMovement) return;
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::DropWeapon()
{
	if (EquippedWeapon)
	{
		FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
		EquippedWeapon->GetWeaponMesh()->DetachFromComponent(DetachmentRules); //detatch from socket

		EquippedWeapon->DropWeapon();
		SetCharacterStatus(ECharacterState::ECS_UNARMED);
		SetCombatState(ECombatState::ECS_NOTREADY);
	}
}

void ABaseCharacter::EquipWeapon(ABaseWeapon* Weapon)
{
	if (Weapon)
	{
		//ignore collisions channels while equipped
		Weapon->GetPickUpTrigger()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("Hand_RSocket"));
		if (HandSocket)
		{
			HandSocket->AttachActor(Weapon, GetMesh());
		}
		EquippedWeapon = Weapon;
		if (EquippedWeapon) {
			EquippedWeapon->SetWeaponStatus(EWeaponStatus::EWS_WEAPONEQUIPPED);
			SetCharacterStatus(ECharacterState::ECS_ARMED);
			SetCombatState(ECombatState::ECS_READY);
		}
	}
}

void ABaseCharacter::SwapWeapon(ABaseWeapon* Weapon)
{
	if (Weapon) {
		DropWeapon();
		EquipWeapon(Weapon);
	}
}

void ABaseCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) {
		OverlapEnemyCounter(1);
	}
}

void ABaseCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlapEnemyCounter(-1);
}

void ABaseCharacter::OverlapEnemyCounter(int8 Amount)
{
	if (OverlappedWeaponCount + Amount <= 0) {
		OverlappedWeaponCount = 0;
		bZoomCam = false;
		bDynamicRotation = false;
	}
	else
	{
		OverlappedWeaponCount += Amount;
		bZoomCam = true;
		if (!bDynamicRotation)
		{
			bDynamicRotation = true;
			SetDynamicYaw();
		} 
	}
}
void ABaseCharacter::SetDynamicYaw()
{
	DynamicYawSpeed = .3;
	TargetDynamicYaw = 125.f;
}

void ABaseCharacter::PlayImpactSound()
{
	if (ImpactSound)
	{
		UGameplayStatics::PlaySound2D(this, ImpactSound);
	}
}

void ABaseCharacter::DynamicCamera(float DeltaTime)
{
	bZoomCam == true ? CurrentTargetLength = FMath::FInterpTo(CurrentTargetLength, 300.f, DeltaTime, 3.f) : CurrentTargetLength = FMath::FInterpTo(CurrentTargetLength, 500.f, DeltaTime, 6.f);

	if (bDynamicRotation) {
		CurrentPitch = FMath::FInterpTo(CurrentPitch, -5.f, DeltaTime, 2.f);
		CurrentDynamicYaw = FMath::FInterpTo(CurrentDynamicYaw, TargetDynamicYaw, DeltaTime, DynamicYawSpeed);
	}
	else
	{
		CurrentPitch = FMath::FInterpTo(CurrentPitch, -35.f, DeltaTime, 5.f);
		CurrentDynamicYaw = FMath::FInterpTo(CurrentDynamicYaw, DefaultDynamicYaw, DeltaTime, DynamicYawSpeed);
	}
	CameraBoom->TargetArmLength = CurrentTargetLength;
	CameraBoom->SetRelativeRotation(FRotator(CurrentPitch, CurrentDynamicYaw, 0.f));
}

void ABaseCharacter::OverlapWeaponCounter(int8 Amount)
{
	if (OverlappedWeaponCount + Amount <= 0) {
		OverlappedWeaponCount = 0;
		bPickUpItem = false;
	}
	else
	{
		OverlappedWeaponCount += Amount;
		bPickUpItem = true;
	}

}

void ABaseCharacter::SetCharacterStatus(ECharacterState Status)
{
	CharacterState = Status;
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {	AnimInstance->SetCharacterState(CharacterState); }
}

void ABaseCharacter::SetCombatState(ECombatState State)
{
	CombatState = State;
}

void ABaseCharacter::SetComboState(EComboState State)
{
	ComboState = State;
}

void ABaseCharacter::AttackSetup()
{
	bAttackButtonHeld = true;
	if (EquippedWeapon && CombatState == ECombatState::ECS_READY)
	{
		ComboSetup();
	}
}

void ABaseCharacter::AttackRelease()
{
	bAttackButtonHeld = false;
}

void ABaseCharacter::ComboSetup() 
{
	if (CombatState == ECombatState::ECS_ATTACKING) { return; }

	if (EquippedWeapon) {
		UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance && AttackMontage)
		{
			//First Swing
			if (CombatState == ECombatState::ECS_READY && ComboState == EComboState::ECS_NOCOMBO) {
				ComboAttack(AnimInstance, "WeaponSwing", 1.5f, 450.f);
				SetComboState(EComboState::ECS_COMBO0);
			}
			//Second Swing
			if (CombatState == ECombatState::ECS_READY && ComboState == EComboState::ECS_COMBO1) {
				ComboAttack(AnimInstance, "Swing2", 1.0f, 400.f);
			}
			//Third Swing
			if (CombatState == ECombatState::ECS_READY && ComboState == EComboState::ECS_COMBO2) {
				ComboAttack(AnimInstance, "Swing3", 1.3f, 10.f);
				AnimInstance->SetComboFinal(true);
			}
		}
	}
}

void ABaseCharacter::EnableAttackBox()
{
	AttackBox->EnableCollision();
}

void ABaseCharacter::DisableAttackBox()
{
	AttackBox->DisableCollision();
}

void ABaseCharacter::KnockBack(FVector ForceDirection, FName Type, int32 PowerLvl)
{
	GetWorldTimerManager().SetTimer(DisableCharacterTimer, this, &ABaseCharacter::Recover, .8f, false);
	DisableCharacter(true);
	PlayImpactSound();
	LaunchCharacter(FVector(ForceDirection.X * PowerLvl, ForceDirection.Y * PowerLvl, 200), false, false);
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->Montage_Play(FallingMontage, 1.5f);
	AnimInstance->Montage_JumpToSection(FName(Type));
	if (HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

}

void ABaseCharacter::Recover()
{
	if (GetWorldTimerManager().TimerExists(DisableCharacterTimer))
	{
		GetWorldTimerManager().ClearTimer(DisableCharacterTimer);
		DisableCharacterTimer.Invalidate();
	}
	DisableCharacter(false);
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetComboFinal(false);
	AnimInstance->Montage_Stop(0.2f, FallingMontage);
	SetComboState(EComboState::ECS_NOCOMBO);
	PowerUpCounter = 100;
	if (EquippedWeapon)
	{
		EquippedWeapon->SetPowerLevel(100);
	}
}

void ABaseCharacter::DisableCharacter(bool disable)
{
	if (disable)
	{
		SetCombatState(ECombatState::ECS_NOTREADY);
		//GetController()->SetIgnoreMoveInput(true);
		bDisableMovement = true;
		GetCharacterMovement()->SetJumpAllowed(false);
		DisableAttackBox();
		DisableHitBoxes();
	}
	else {
		//GetController()->SetIgnoreMoveInput(false);
		bDisableMovement = false;
		GetCharacterMovement()->SetJumpAllowed(true);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		if (CharacterState != ECharacterState::ECS_UNARMED) {
			SetCombatState(ECombatState::ECS_READY);
		}
		EnableHitBoxes();
	}
}

void ABaseCharacter::Death()
{
	OTRGameMode->SetLives(-1);
	CameraLocation = CameraBoom->GetRelativeLocation();
	DropWeapon();
	FTimerHandle CharacterRespawnTimer;
	GetWorldTimerManager().SetTimer(CharacterRespawnTimer, this, &ABaseCharacter::Respawn, 1.5f, false);
	CameraBoom->CameraLagSpeed = .01f;
	BaseRecord = Cast<ABaseRecord>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseRecord::StaticClass()));
	if (BaseRecord)
	{
		BaseRecord->ResetRecordSpeed();
	}
}

void ABaseCharacter::Respawn()
{

	Recover();
	SetActorLocation(FVector(0.0f, 0.0f, 45.f));
	CameraBoom->CameraLagSpeed = 2.0f;

	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABaseCharacter::PowerUpWeapon()
{
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (!EquippedWeapon) { return; }
	if (CombatState == ECombatState::ECS_NOTREADY) { return; }
	if (bAttackButtonHeld)
	{
		if (PowerUpCounter == 450) 
		{ PowerUpCounter = 450; }
		else {
			PowerUpCounter += 25;
		}
		ComboAttack(AnimInstance, "WeaponSwing", 1.0f, 100.f);
	}
	else if (PowerUpCounter > 201)
	{
		AnimInstance->SetComboFinal(true);
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		EquippedWeapon->SetPowerLevel(PowerUpCounter);
	}
	else if (PowerUpCounter < 200)
	{
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		EquippedWeapon->SetPowerLevel(PowerUpCounter);
	}
}

void ABaseCharacter::FinishAttack()
{
	DisableCharacter(false);
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->Montage_Stop(0.2f, AttackMontage);
	AnimInstance->SetComboFinal(false);
	SetCombatState(ECombatState::ECS_READY);
	SetComboState(EComboState::ECS_NOCOMBO);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	PowerUpCounter = 100;
	if (EquippedWeapon)
	{
		EquippedWeapon->SetPowerLevel(100);
	}
}

void ABaseCharacter::ComboHit()
{
	//Don't do anything if on final swing or if powered up
	if (ComboState == EComboState::ECS_COMBO2 || PowerUpCounter > 201) { return; }

	//If ComboState is Combo0 or Combo1 update accordingly, character must also be attacking
	if (CombatState == ECombatState::ECS_ATTACKING && ComboState == EComboState::ECS_COMBO0)
	{
		SetComboState(EComboState::ECS_COMBO1);
		SetCombatState(ECombatState::ECS_READY);
	}
	if (CombatState == ECombatState::ECS_ATTACKING && ComboState == EComboState::ECS_COMBO1)
	{
		SetComboState(EComboState::ECS_COMBO2);
		SetCombatState(ECombatState::ECS_READY);
	}
}

void ABaseCharacter::ComboMiss()
{
	SetComboState(EComboState::ECS_NOCOMBO);
}

void ABaseCharacter::JumpBoost(FVector ForceDirection)
{
	LaunchCharacter(FVector(ForceDirection.X, ForceDirection.Y, 1500), false, false);
}

void ABaseCharacter::ComboAttack(UBaseCharacterAnimInstance* AnimInstanceReference, FName MontageSection, float Speed, float MaxWalkSpeed)
{
	AnimInstanceReference->Montage_Play(AttackMontage, Speed);
	AnimInstanceReference->Montage_JumpToSection(FName(MontageSection));
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	SetCombatState(ECombatState::ECS_ATTACKING);
}

void ABaseCharacter::EnableWeaponCollision()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->GetAttackBox()->EnableCollision();
	}
}

void ABaseCharacter::DisableWeaponCollision()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->GetAttackBox()->DisableCollision();
	}
}

void ABaseCharacter::PlayWeaponSwingSound()
{
	switch (ComboState)
	{
	case EComboState::ECS_NOCOMBO:
		EquippedWeapon->PlayWeaponSwingSound(0);
		break;

	case EComboState::ECS_COMBO0:
		EquippedWeapon->PlayWeaponSwingSound(0);
		break;

	case EComboState::ECS_COMBO1:
		EquippedWeapon->PlayWeaponSwingSound(0);
		EquippedWeapon->SetPowerLevel(350);
		break;

	case EComboState::ECS_COMBO2:
		PowerUpCounter < 201 ? EquippedWeapon->PlayWeaponSwingSound(1) : EquippedWeapon->PlayWeaponSwingSound(2);
	}
}

void ABaseCharacter::DisableHitBoxes()
{
	FrontHitBox->DisableCollision();
	BackHitBox->DisableCollision();
}

void ABaseCharacter::EnableHitBoxes()
{
	FrontHitBox->EnableCollision();
	BackHitBox->EnableCollision();
}
