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
	uint8 SpinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Music)
	class UAudioComponent* RecordAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class USoundCue* RecordAudioCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 MusicSelect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 CurrentMusicSelect;

	void GetMusicSelection();

	UFUNCTION()
	void GetPlaybackPerc(const USoundWave* PlayingSoundWave, const float PlaybackPercent);

	float CurrentAudioPercentage;

private:
	//Record Enum Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		ERecordStatus RecordStatus;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetRecordSpeed(int Increment);

	void ResetRecordSpeed();
};
