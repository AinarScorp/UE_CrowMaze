#pragma once
UENUM(BlueprintType)
enum class EObstaclePositionTypes : uint8
{
	None UMETA(DisplayName = "None"),

	EOPT_TopRight UMETA(DisplayName = "TopRight"),
	EOPT_TopMiddle UMETA(DisplayName = "TopMiddle"),
	EOPT_TopLeft UMETA(DisplayName = "TopLeft"),
	EOPT_CenterRight UMETA(DisplayName = "CenterRight"),
	EOPT_CenterMiddle UMETA(DisplayName = "CenterMiddle"),
	EOPT_CenterLeft UMETA(DisplayName = "CenterLeft"),
	EOPT_BottomRight UMETA(DisplayName = "BottomRight"),
	EOPT_BottomMiddle UMETA(DisplayName = "BottomMiddle"),
	EOPT_BottomLeft UMETA(DisplayName = "BottomLeft"),
	EOPT_MAX UMETA(DisplayName = "Max")
};