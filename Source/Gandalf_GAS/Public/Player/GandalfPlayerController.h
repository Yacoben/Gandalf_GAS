

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GandalfPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GANDALF_GAS_API AGandalfPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGandalfPlayerController();
protected:
	virtual void BeginPlay() override;
public:


};
