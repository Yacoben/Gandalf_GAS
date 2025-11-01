// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GandalfEffectActor.generated.h"

UCLASS()
class GANDALF_GAS_API AGandalfEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGandalfEffectActor();

protected:
	virtual void BeginPlay() override;

public:	

};
