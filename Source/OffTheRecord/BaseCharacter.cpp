// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "BaseCharacter.h"
#include "BaseCharacterAnimInstance.h"

#include "Camera/CameraComponent.h"

#include "Components/BoxComponent.h"

#include "Engine/SkeletalMeshSocket.h"

#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "BaseWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter() : 
	CharacterState(ECharacterState::ECS_UNARMED), OverlappedWeaponCount(0), CombatState(ECombatState::ECS_NOTREADY), ComboState(EComboState::ECS_NOCOMBO)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Character movement settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; //Character moves in direction of input
	GetCharacterMovement()->JumpZVelocity = 600.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}



// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("AttackSetup", IE_Released, this, &ABaseCharacter::AttackSetup);

}


//Forward & backward movement
void ABaseCharacter::ForwardMotion(float Value)
{
	//if (ComboState == EComboState::ECS_COMBO2) { return; }
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
	//if (ComboState == EComboState::ECS_COMBO2) { return; }
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
};

void ABaseCharacter::FinishAttack()
{
	UBaseCharacterAnimInstance* AnimInstance = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->Montage_Stop(0.2f, AttackMontage);
	AnimInstance->SetComboFinal(false);
	SetCombatState(ECombatState::ECS_READY);
	SetComboState(EComboState::ECS_NOCOMBO);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ABaseCharacter::ComboHit()
{
	//Don't do anything if on final swing
	if (ComboState == EComboState::ECS_COMBO2) { return; }
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

void ABaseCharacter::ComboAttack(UBaseCharacterAnimInstance* AnimInstanceReference, FName MontageSequence, float Speed, float MaxWalkSpeed)
{
	AnimInstanceReference->Montage_Play(AttackMontage, Speed);
	AnimInstanceReference->Montage_JumpToSection(FName(MontageSequence));
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	SetCombatState(ECombatState::ECS_ATTACKING);
}
