// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "HitColliderComponent.h"
#include "AttackTriggerComponent.h"
#include "Math/Color.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"
#include "BaseRecord.h"

UHitColliderComponent::UHitColliderComponent() : bCollisionEnabled(false), HitBoxType(EBoxTypes::EBT_DEFAULT)
{

}

void UHitColliderComponent::BeginPlay()
{
	Super::BeginPlay();

	EnableCollision();

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
	{
		BaseCharacterOwner = Cast<ABaseCharacter>(this->GetOwner());
		ComponentOwner = FString(BaseCharacterOwner->GetName());
	}

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseWeapon::StaticClass()))
	{
		EquippedWeaponOwner = Cast<ABaseWeapon>(this->GetOwner());
		ComponentOwner = FString(EquippedWeaponOwner->GetName());
	}

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseEnemy::StaticClass()))
	{
		BaseEnemyOwner = Cast<ABaseEnemy>(this->GetOwner());
		ComponentOwner = FString(BaseEnemyOwner->GetName());
	}

	if (ComponentOwner.Len() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Collider %s --- Has Owner: %s"), *FString(this->GetName()), *ComponentOwner);
	}

	this->OnComponentBeginOverlap.AddDynamic(this, &UHitColliderComponent::OnOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UHitColliderComponent::OnEndOverlap);
}

void UHitColliderComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ABaseWeapon::StaticClass()))
	{
		EquippedWeapon = Cast<ABaseWeapon>(OtherComp->GetOwner());
		if (EquippedWeapon) {
			int32 WeaponPower = EquippedWeapon->GetPowerLevel();
			FVector LaunchDirection((OtherActor->GetActorLocation() - this->GetOwner()->GetActorLocation()).GetSafeNormal() * -1);
			if (OtherComp->GetClass()->IsChildOf(UAttackTriggerComponent::StaticClass()))
			{
				if (HitBoxType == EBoxTypes::EBT_FRONT)
				{
					if (BaseEnemyOwner)
					{
						BaseEnemyOwner->KnockBack(LaunchDirection, WeaponPower);
					}
					if (BaseCharacterOwner)
					{
						return;
					}
				}
				if (HitBoxType == EBoxTypes::EBT_BACK)
				{
					if (BaseEnemyOwner)
					{
						BaseEnemyOwner->KnockForward(LaunchDirection, WeaponPower);
					}
					if (BaseCharacterOwner)
					{
						return;
					}
				}
			}
		}
	}

	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))  {
		BaseCharacter = Cast<ABaseCharacter>(OtherComp->GetOwner());
		if (BaseCharacter)
		{
			if (OtherComp->GetClass()->IsChildOf(UAttackTriggerComponent::StaticClass()))
			{
				if (HitBoxType == EBoxTypes::EBT_TOP)
				{
					if (BaseEnemyOwner)
					{
						BaseEnemyOwner->KnockDown();
					}
					if (BaseCharacterOwner)
					{
						return;
					}
				}
			}
		}
	}

	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) {
		BaseEnemy = Cast<ABaseEnemy>(OtherComp->GetOwner());
		if (BaseCharacter)
		{
			if (HitBoxType == EBoxTypes::EBT_FRONT)
			{
				if (BaseCharacterOwner)
				{
					return;
				}
			}
			if (HitBoxType == EBoxTypes::EBT_BACK)
			{
				if (BaseCharacterOwner)
				{
					return;
				}
			}
		}
	}
	

	//Temp Logging
	if (EquippedWeapon) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon Hit"));
		//the goal here is to increase the record speed on successful weapon hits. however this crashes the editor on enemy hit. Suggestions?? 
		BaseRecord->SetRecordSpeed(.3f);
	}
	if (BaseCharacter) {
		UE_LOG(LogTemp, Warning, TEXT("Character Hit"));
	}
	UE_LOG(LogTemp, Warning, TEXT("This Object: %s --- Collision with: %s"), *FString(OverlappedComponent->GetName()), * FString(OtherComp->GetName()));
	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Collide with Base Enemy"));
	}
	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Collide with Base Character"));
	}

}

void UHitColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void UHitColliderComponent::DisableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->SetVisibility(true);
	this->ShapeColor.Green;
	bCollisionEnabled = false;
}

void UHitColliderComponent::EnableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->SetCollisionResponseToAllChannels(ECR_Overlap);
	this->SetVisibility(true);
	this->ShapeColor.Blue;
	bCollisionEnabled = true;
}

void UHitColliderComponent::SetType(EBoxTypes NewHitState)
{
	HitBoxType = NewHitState;
}
