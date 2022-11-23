// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "HitColliderComponent.h"
#include "AttackTriggerComponent.h"
#include "Math/Color.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"

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
						BaseEnemyOwner->KnockBack(LaunchDirection, WeaponPower*5);
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
						BaseEnemyOwner->KnockForward(LaunchDirection, WeaponPower*6);
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
		if (BaseEnemy)
		{
			if (OtherComp->GetClass()->IsChildOf(UAttackTriggerComponent::StaticClass()))
			{
				FVector LaunchDirection((OtherActor->GetActorLocation() - this->GetOwner()->GetActorLocation()).GetSafeNormal() * -1);
				if (HitBoxType == EBoxTypes::EBT_FRONT)
				{
					if (BaseCharacterOwner)
					{
						UE_LOG(LogTemp, Warning, TEXT("This Object: %s %s --- Collision with: %s %s"), *FString(OverlappedComponent->GetOwner()->GetName()), *FString(OverlappedComponent->GetName()), *FString(OtherComp->GetName()), *FString(OtherComp->GetOwner()->GetName()));
						BaseCharacterOwner->KnockBack(LaunchDirection, "FallBack", BaseEnemy->GetPowerLevel()*5);
					}
				}
				if (HitBoxType == EBoxTypes::EBT_BACK)
				{
					if (BaseCharacterOwner)
					{
						UE_LOG(LogTemp, Warning, TEXT("This Object: %s %s --- Collision with: %s %s"), *FString(OverlappedComponent->GetOwner()->GetName()), *FString(OverlappedComponent->GetName()), *FString(OtherComp->GetName()), *FString(OtherComp->GetOwner()->GetName()));
						BaseCharacterOwner->KnockBack(LaunchDirection, "FallForward", BaseEnemy->GetPowerLevel()*6);
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
