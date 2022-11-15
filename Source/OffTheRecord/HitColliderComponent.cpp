// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "HitColliderComponent.h"
#include "Math/Color.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"

UHitColliderComponent::UHitColliderComponent() : bCollisionEnabled(false)
{

}

void UHitColliderComponent::BeginPlay()
{
	Super::BeginPlay();

	DisableCollision();

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
	{
		BaseCharacter = Cast<ABaseCharacter>(this->GetOwner());
		ComponentOwner = FString(BaseCharacter->GetName());
	}

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseWeapon::StaticClass()))
	{
		EquippedWeapon = Cast<ABaseWeapon>(this->GetOwner());
		ComponentOwner = FString(EquippedWeapon->GetName());
	}

	if (this->GetOwner()->GetClass()->IsChildOf(ABaseEnemy::StaticClass()))
	{
		BaseEnemy = Cast<ABaseEnemy>(this->GetOwner());
		ComponentOwner = FString(BaseEnemy->GetName());
	}

	if (ComponentOwner.Len() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Collider %s --- Has Owner: %s"), *FString(this->GetName()), *ComponentOwner);
	}

	this->OnComponentBeginOverlap.AddDynamic(this, &UHitColliderComponent::OnOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UHitColliderComponent::OnEndOverlap);
}

void UHitColliderComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->ShapeColor = FColor(255, 0, 0, 1);
}

void UHitColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void UHitColliderComponent::DisableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->SetVisibility(true);
	this->bHiddenInGame(false);
	this->ShapeColor.Green;
	bCollisionEnabled = false;
}

void UHitColliderComponent::EnableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	this->SetCollisionResponseToAllChannels(ECR_Overlap);
	this->SetVisibility(true);
	this->ShapeColor = FColor(0, 255, 0, 1);
	bCollisionEnabled = true;
}
