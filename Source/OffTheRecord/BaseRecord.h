#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "BaseRecord.generated.h"

//Record status
UENUM(BlueprintType)
enum class ERecordStatus : uint8
{
	ERS_PLAYING UMETA(DisplayName = "Record Playing"),
	ERS_STOPPED UMETA(DisplayName = "Record Stopped")

};

UCLASS()
class OFFTHERECORD_API ABaseRecord : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseRecord();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float SpinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Music)
	class UAudioComponent* RecordAudioComponent;

private:
	//Record Enum Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		ERecordStatus RecordStatus;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetRecordSpeed(float Increment);
};
