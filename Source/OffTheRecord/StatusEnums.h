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