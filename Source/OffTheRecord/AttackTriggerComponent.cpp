// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "AttackTriggerComponent.h"
#include "Math/Color.h"

UAttackTriggerComponent::UAttackTriggerComponent() : bCollisionEnabled(false)
{

}

void UAttackTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	DisableCollision();

	this->OnComponentBeginOverlap.AddDynamic(this, &UAttackTriggerComponent::OnOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UAttackTriggerComponent::OnEndOverlap);
}

void UAttackTriggerComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void UAttackTriggerComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void UAttackTriggerComponent::DisableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SetCollisionResponseToAllChannels(ECR_Ignore);
	bCollisionEnabled = false;
}

void UAttackTriggerComponent::EnableCollision()
{
	this->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->SetCollisionResponseToAllChannels(ECR_Overlap);
	bCollisionEnabled = true;
}
