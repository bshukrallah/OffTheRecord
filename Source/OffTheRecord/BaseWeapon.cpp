// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#include "BaseWeapon.h"

#include "AttackTriggerComponent.h"
#include "BaseCharacter.h"

#include "Sound/SoundCue.h"
#include "TimerManager.h"

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon() : FallingWeaponTime(1.8f), bOrientWeapon(false), PowerUpLevel(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Weapon Mesh"));
	SetRootComponent(WeaponMesh);

	//Trigger for picking up the weapon
	PickUpTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Pick Up Trigger"));
	PickUpTrigger->SetupAttachment(GetRootComponent());

	//Trigger for Attacking
	AttackBox = CreateDefaultSubobject<UAttackTriggerComponent>(TEXT("Attack Trigger Box"));
	AttackBox->SetupAttachment(GetRootComponent());

	//Audio
	WeaponSwingAC = CreateDefaultSubobject<UAudioComponent>(TEXT("Weapon Swing Sound"));
	WeaponSwingAC->bAutoActivate = false;
	WeaponSwingAC->SetupAttachment(GetRootComponent());
	WeaponSwingAC->SetRelativeLocation(FVector(1.f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();


	SetWeaponStatus(EWeaponStatus::EWS_WEAPONFALLING);

	if (WeaponStatus == EWeaponStatus::EWS_WEAPONFALLING)
	{
		SpawnWeapon();
		UE_LOG(LogTemp, Warning, TEXT("WEAPON SPAWNED"));
	}

	if (WeaponSwingAC && WeaponSwingCue) 
	{
		WeaponSwingAC->SetSound(WeaponSwingCue);
	}

	PickUpTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::OnOverlap);
	PickUpTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseWeapon::OnEndOverlap);
}

void ABaseWeapon::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);
		if (OtherComp == BaseCharacter->GetCapsuleComponent())
		{
			BaseCharacter->OverlapWeaponCounter(1);
			if(BaseCharacter->bPickUpItem)
			{
				BaseCharacter->SwapWeapon(this);
			}
		}
	}
}

void ABaseWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);
		if (BaseCharacter)
		{
			BaseCharacter->OverlapWeaponCounter(-1);
		}
	}
}

void ABaseWeapon::SetWeaponStatus(EWeaponStatus Status)
{

	WeaponStatus = Status;
	switch (Status)
	{
	case EWeaponStatus::EWS_WEAPONPICKUP:
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		PickUpTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		PickUpTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		AttackBox->DisableCollision();

		break;

	case EWeaponStatus::EWS_WEAPONFALLING:
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		PickUpTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		PickUpTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		AttackBox->DisableCollision();

		break;

	case EWeaponStatus::EWS_WEAPONEQUIPPED:
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		PickUpTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		PickUpTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABaseWeapon::KillWeapon()
{
	this->Destroy();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOrientWeapon) {
		FRotator MeshRotation{ 0.f, GetWeaponMesh()->GetComponentRotation().Yaw, 180.f};
		GetWeaponMesh()->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void ABaseWeapon::DropWeapon()
{
	FRotator MeshRotation{ 0.f, WeaponMesh->GetComponentRotation().Yaw, 0.f };
	WeaponMesh->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);

	const FVector MeshForward{ WeaponMesh->GetForwardVector() };
	const FVector MeshRight{ WeaponMesh->GetRightVector() };
	//Direction to throw weapon
	FVector ImpulseDirection = MeshRight.RotateAngleAxis(-20.f, MeshForward);

	ImpulseDirection = MeshRight.RotateAngleAxis(30.f, FVector(0.f, 0.f, 1.f));

	SetWeaponStatus(EWeaponStatus::EWS_WEAPONFALLING);
	WeaponMesh->AddImpulse(ImpulseDirection*3000);

	FTimerHandle FallingWeaponTimer;
	GetWorldTimerManager().SetTimer(FallingWeaponTimer, this, &ABaseWeapon::KillWeapon, FallingWeaponTime-.5f, false);
}

void ABaseWeapon::SpawnWeapon()
{
		FVector ImpulseDirection(0.f, 0.f, 1'000.f);
		WeaponMesh->AddImpulse(ImpulseDirection);
		bOrientWeapon = true;
		FTimerHandle FallingWeaponTimer;
		GetWorldTimerManager().SetTimer(FallingWeaponTimer, this, &ABaseWeapon::StopFalling, FallingWeaponTime, false);
}

void ABaseWeapon::PlayWeaponSwingSound(int8 type)
{
	WeaponSwingAC->SetIntParameter("WeaponSwingType", type);
	WeaponSwingAC->Play();
}

void ABaseWeapon::StopFalling()
{
	SetWeaponStatus(EWeaponStatus::EWS_WEAPONPICKUP);
	bOrientWeapon = false;
}

