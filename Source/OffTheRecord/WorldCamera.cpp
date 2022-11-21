// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)


#include "WorldCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "BaseCharacter.h"


// Sets default values
AWorldCamera::AWorldCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FocalPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Focal Point"));
	SetRootComponent(FocalPoint);
	FocalPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FocalPoint->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f; 
	SpringArm->bUseCameraLagSubstepping = true;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bDoCollisionTest = false;
	//SpringArm->bUsePawnControlRotation = true; 

	WorldCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("World Camera"));
	WorldCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	WorldCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	CameraTriggerTop = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Trigger Top"));
	CameraTriggerDown = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Trigger Down"));
	CameraTriggerCenter = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Trigger Center"));


}

// Called when the game starts or when spawned
void AWorldCamera::BeginPlay()
{
	Super::BeginPlay();
	OldLocation = CameraTriggerCenter->GetComponentTransform().GetTranslation();
	NewLocation = OldLocation;
	{
		CameraTriggerTop->OnComponentBeginOverlap.AddDynamic(this, &AWorldCamera::OnOverlap);
		CameraTriggerTop->OnComponentEndOverlap.AddDynamic(this, &AWorldCamera::OnEndOverlap);
		CameraTriggerDown->OnComponentBeginOverlap.AddDynamic(this, &AWorldCamera::OnOverlap);
		CameraTriggerDown->OnComponentEndOverlap.AddDynamic(this, &AWorldCamera::OnEndOverlap);
		CameraTriggerCenter->OnComponentBeginOverlap.AddDynamic(this, &AWorldCamera::OnOverlap);
		CameraTriggerCenter->OnComponentEndOverlap.AddDynamic(this, &AWorldCamera::OnEndOverlap);
	}
}

void AWorldCamera::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("HITTING"));
		NewLocation = OverlappedComponent->GetComponentTransform().GetTranslation();
		OldLocation = FocalPoint->GetComponentTransform().GetTranslation();
	}
}

void AWorldCamera::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWorldCamera::MoveFocalPoint(float DeltaTime)
{
	FVector UpdateLocation;
	UpdateLocation.X = FMath::FInterpTo(OldLocation.X, NewLocation.X, DeltaTime, 15.f);
	UpdateLocation.Y = FMath::FInterpTo(OldLocation.Y, NewLocation.Y, DeltaTime, 15.f);
	UpdateLocation.Z = 0;
	FocalPoint->SetRelativeLocation(UpdateLocation);
	OldLocation = UpdateLocation;
}

// Called every frame
void AWorldCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = (UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (FocalPoint->GetRelativeLocation().X == NewLocation.X) {
		UE_LOG(LogTemp, Warning, TEXT("DISTANCE"));
		float Distance = PlayerPawn->GetDistanceTo(this);
		SpringArm->TargetArmLength = 500.0f + Distance;
	}
	else
	{
		MoveFocalPoint(DeltaTime);
	}
}

