#pragma once

#include "CoreMinimal.h"
#include "Delegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdateDelegate, float, OldHealth, float, NewHealth);

/*
 * unused struct. was used to declare a delegate in a separate header file
 */
USTRUCT()
struct FDelegates
{
	GENERATED_BODY()
};
