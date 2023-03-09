// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ARLGameplayInterface.generated.h"


UINTERFACE(MinimalAPI)
class UARLGameplayInterface : public UInterface
{
private:
	GENERATED_BODY()
};


class ACTIONROGUELIKE_API IARLGameplayInterface
{
private:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
