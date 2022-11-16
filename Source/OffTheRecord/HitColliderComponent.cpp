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

	EnableCollision();

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
	if (BaseEnemy) {
		UE_LOG(LogTemp, Warning, TEXT("Enemy Hit"));
		if (OtherActor->GetClass()->IsChildOf(ABaseWeapon::StaticClass())) {
			UE_LOG(LogTemp, Warning, TEXT("Collide with Weapon"));
			FVector LaunchDirection((OtherActor->GetActorLocation() - BaseEnemy->GetActorLocation()).GetSafeNormal()*-1);
			BaseEnemy->LaunchCharacter(FVector(LaunchDirection.X*500, LaunchDirection.Y*500, 200), false, false);

		}
	}
	if (EquippedWeapon) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon Hit"));
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
