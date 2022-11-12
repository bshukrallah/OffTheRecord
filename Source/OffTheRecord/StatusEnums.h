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
	//Currently powering up
	ECS_POWERUP UMETA(DisplayName = "Powering Up"),
	//Attack following power up
	ECS_POWERUPATTACK UMETA(DisplayName = "Power Up Attack"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EComboState : uint8
{
	//Ready to attack
	ECS_COMBO0 UMETA(DisplayName = "First Strike"),
	ECS_COMBO1 UMETA(DisplayName = "Combo 1 Available"),
	ECS_COMBO2 UMETA(DisplayName = "Combo 2 Available"),
	//Not allowed to attack
	ECS_NOCOMBO UMETA(DisplayName = "No Combo Available"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};