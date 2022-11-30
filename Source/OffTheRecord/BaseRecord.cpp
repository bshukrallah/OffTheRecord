#include "BaseRecord.h"

#include <string>
#include <cmath>
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABaseRecord::ABaseRecord()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpinValue = 20;

	RecordAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Record Audio"));
	RecordAudioComponent->bAutoActivate = false;
	RecordAudioComponent->SetupAttachment(GetRootComponent());
	MusicSelect = 0;
	CurrentMusicSelect = 0;
}

// Called when the game starts or when spawned
void ABaseRecord::BeginPlay()
{
	Super::BeginPlay();
	if (RecordAudioComponent && RecordAudioCue)
	{
		RecordAudioComponent->SetSound(RecordAudioCue);
		RecordAudioComponent->OnAudioPlaybackPercent.AddUniqueDynamic(this, &ABaseRecord::GetPlaybackPerc);
		if (RecordAudioComponent->OnAudioPlaybackPercent.IsBound())
		{
			RecordAudioComponent->Activate();
		}
	}
}


//SoundCue'/Game/AudioExperiments/Sounds/S_ViolinConcertoInFMajor_Cue.S_ViolinConcertoInFMajor_Cue'
// Called every frame
void ABaseRecord::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(0.f, SpinValue * DeltaTime, 0.f);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ABaseRecord::SetRecordSpeed(int Increment)
{
	SpinValue += Increment;
}

void ABaseRecord::GetMusicSelection()
{
	if (SpinValue <= 25)
	{
		MusicSelect = 0;
	}else if (SpinValue <= 75)
	{
		MusicSelect = 1;
	}else if (SpinValue <= 125)
	{
		MusicSelect = 2;
	}else if (SpinValue <= 200)
	{
		MusicSelect = 3;
	}else
	{
		MusicSelect = 4;
	}
}

void ABaseRecord::GetPlaybackPerc(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	CurrentAudioPercentage = PlaybackPercent;
	GetMusicSelection();
	if (MusicSelect != CurrentMusicSelect)
	{
		RecordAudioComponent->Stop();
		if (CurrentAudioPercentage > 1.0f)
		{
			CurrentAudioPercentage -= round(CurrentAudioPercentage);
		}
		CurrentMusicSelect = MusicSelect;
		RecordAudioComponent->SetIntParameter("Tempo", CurrentMusicSelect);
		RecordAudioComponent->FadeIn(.2f, 1.0f, PlayingSoundWave->Duration * CurrentAudioPercentage, EAudioFaderCurve::Linear );
	}
}

