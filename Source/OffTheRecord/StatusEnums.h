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
	ECS_READY UMETA(DisplayName = "Unarmed"),
	//Not allowed to attack
	ECS_NOTREADY UMETA(DisplayName = "Unarmed"),
	//Currently attacking
	ECS_ATTACKING UMETA(DisplayName = "Armed"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};