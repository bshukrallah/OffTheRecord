#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_GUITAR UMETA(DisplayName = "Guitar"),
	EWT_HAMMER UMETA(DisplayName = "Hammer"),
	EWT_BBAT UMETA(DisplayName = "Baseball Bat"),

	EWT_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_UNARMED UMETA(DisplayName = "Unarmed"),
	ECS_ARMED UMETA(DisplayName = "Armed"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	//Ready to attack
	ECS_READY UMETA(DisplayName = "Ready to Attack"),
	//Not allowed to attack
	ECS_NOTREADY UMETA(DisplayName = "Not Ready to Attack"),
	//Currently attacking
	ECS_ATTACKING UMETA(DisplayName = "Attacking"),
	ECS_CHARGING UMETA(DisplayName = "Charging"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EComboState : uint8
{
	//Ready to attack
	ECS_COMBO0 UMETA(DisplayName = "Combo 1 Hit"),
	ECS_COMBO1 UMETA(DisplayName = "Combo 2 Hit"),
	ECS_COMBO2 UMETA(DisplayName = "Combo 3 Hit"),
	//Not allowed to attack
	ECS_NOCOMBO UMETA(DisplayName = "No Combo Available"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EHitState : uint8
{
	//Ready to attack
	EHS_FALLBACK UMETA(DisplayName = "Falling Backwards"),
	EHS_FALLFORWARD UMETA(DisplayName = "Falling Forwards"),
	EHS_KNOCKEDDOWN UMETA(DisplayName = "Knocked Straight Down"),
	EHS_GETTINGUP UMETA(DisplayName = "Getting Back Up"),
	EHS_NORMAL UMETA(DisplayName = "Normal State"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EBoxTypes : uint8
{
	//Ready to attack
	EBT_FRONT UMETA(DisplayName = "Front Side Hit Box"),
	EBT_BACK UMETA(DisplayName = "Back Side Hit Box"),
	EBT_TOP UMETA(DisplayName = "Top Hit Box"),

	EBT_MAX UMETA(DisplayName = "DefaultMax")
};