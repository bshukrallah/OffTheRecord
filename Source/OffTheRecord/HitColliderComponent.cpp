// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "HitColliderComponent.h"
#include "AttackTriggerComponent.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "WeaponSpawnComponent.h"
#include "BaseWeapon.h"
#include "BaseRecord.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

UHitColliderComponent::UHitColliderComponent() : bCollisionEnabled(false)
{

}

void UHitColliderComponent::BeginPlay()
{
	Super::BeginPlay();

	EnableCollision();
	
	BaseRecord = Cast<ABaseRecord>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseRecord::StaticClass()));

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

	this->OnComponentBeginOverlap.AddDynamic(this, &UHitColliderComponent::OnOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UHitColliderComponent::OnEndOverlap);
}

void UHitColliderComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherComp->GetClass()->IsChildOf(UHitColliderComponent::StaticClass()))
	{

		return;
	}
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
						BaseEnemyOwner->KnockBack(LaunchDirection, WeaponPower*8);
						if (BaseRecord)
						{
							BaseRecord->SetRecordSpeed(.009f);
							UE_LOG(LogTemp, Warning, TEXT("Record Speed increase"));
						}
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
						BaseEnemyOwner->KnockForward(LaunchDirection, WeaponPower*9);
						if (BaseRecord)
						{
							BaseRecord->SetRecordSpeed(.009f);
							UE_LOG(LogTemp, Warning, TEXT("Record Speed increase"));
						}
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
					FVector LaunchDirection((OtherActor->GetActorLocation() - this->GetOwner()->GetActorLocation()).GetSafeNormal() * -1);
					if (BaseEnemyOwner)
					{
						BaseEnemyOwner->KnockDown();
						BaseCharacter->JumpBoost(LaunchDirection);
						BaseEnemyOwner->GetWeaponSpawner()->SpawnWeapon();
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
		if (BaseEnemy)
		{
			if (OtherComp->GetClass()->IsChildOf(UAttackTriggerComponent::StaticClass()))
			{
				FVector LaunchDirection((OtherActor->GetActorLocation() - this->GetOwner()->GetActorLocation()).GetSafeNormal() * -1);
				if (HitBoxType == EBoxTypes::EBT_FRONT)
				{
					if (BaseCharacterOwner)
					{
						BaseCharacterOwner->KnockBack(LaunchDirection, "FallBack", BaseEnemy->GetPowerLevel()*5);
					}
					if (BaseEnemyOwner && BaseEnemy->bCharge)
					{
						BaseEnemyOwner->KnockBack(LaunchDirection, BaseEnemy->GetPowerLevel() * 5);
					}
				}
				if (HitBoxType == EBoxTypes::EBT_BACK)
				{
					if (BaseCharacterOwner)
					{
						BaseCharacterOwner->KnockBack(LaunchDirection, "FallForward", BaseEnemy->GetPowerLevel()*6);
					}
					if (BaseEnemyOwner && BaseEnemy->bCharge)
					{
						BaseEnemyOwner->KnockForward(LaunchDirection, BaseEnemy->GetPowerLevel() * 6);
					}
				}
			}
		}
	}
	

	//Temp Logging
	/*
	if (EquippedWeapon) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon Hit"));
	}
	if (BaseCharacterOwner) {
		UE_LOG(LogTemp, Warning, TEXT("Character Hit"));
	}
	UE_LOG(LogTemp, Warning, TEXT("This Object: %s --- Collision with: %s"), *FString(OverlappedComponent->GetName()), * FString(OtherComp->GetName()));
	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Collide with Base Enemy"));
	}
	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Collide with Base Character"));
	}
	*/
}

void UHitColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void UHitColliderComponent::DisableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SetCollisionResponseToAllChannels(ECR_Ignore);
	bCollisionEnabled = false;
}

void UHitColliderComponent::EnableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->SetCollisionResponseToAllChannels(ECR_Overlap);
	bCollisionEnabled = true;
}

void UHitColliderComponent::SetType(EBoxTypes NewHitState)
{
	HitBoxType = NewHitState;
}
