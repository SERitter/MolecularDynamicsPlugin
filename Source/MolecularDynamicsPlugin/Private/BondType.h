/*
Enum to indicate the "type" of a bond (single, double, etc).
*/

#pragma once

#include "BondType.generated.h"

UENUM()
enum class EBondType : uint8
{
	SINGLE   UMETA(DisplayName = "Single"),
	DOUBLE   UMETA(DisplayName = "Double"),
	TRIPLE   UMETA(DisplayName = "Triple"),
	HYDROGEN UMETA(DisplayName = "Hydrogen")
};


