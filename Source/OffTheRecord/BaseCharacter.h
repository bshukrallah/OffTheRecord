// Off The Record - Game Off 2022 Game Jam (Marcus Peck & Ben Shukrallah)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatusEnums.h"
#include "BaseCharacter.generated.h"

UCLASS()
class OFFTHERECORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupControls();

	void ForwardMotion(float Value);
	void LateralMotion(float Value);

	void DropWeapon();
	void AttackSetup();

	void EquipWeapon(class ABaseWeapon* Weapon);



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//Type of Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		EWeaponType WeaponType;

	//Character Battle Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ECharacterState CharacterState;

	//Character Battle Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		EComboState ComboState;

	//Currently equipped weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ABaseWeapon* EquippedWeapon;

	//Character Battle Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ECombatState CombatState;

	//Num of overlapped weapons
	int8 OverlappedWeaponCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SwapWeapon(ABaseWeapon* Weapon);
	void OverlapWeaponCounter(int8 Amount);

	bool bPickUpItem = false;

	UFUNCTION(BlueprintCallable)
		void SetCharacterStatus(ECharacterState Status);

	UFUNCTION(BlueprintCallable)
		void SetCombatState(ECombatState State);

	UFUNCTION(BlueprintCallable)
		void SetComboState(EComboState State);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE ECharacterState GetCharacterStatus() const { return CharacterState; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE ECombatState GetCombatState() const { return CombatState; }

	void FinishAttack();
	void ComboHit();
	void ComboMiss();

};
