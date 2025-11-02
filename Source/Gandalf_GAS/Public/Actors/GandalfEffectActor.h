// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GandalfEffectActor.generated.h"


class UGameplayEffect;


UCLASS()
class GANDALF_GAS_API AGandalfEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGandalfEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void ApplyEffectToTarget(TSubclassOf<UGameplayEffect> GameplayEffectClass, AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> EffectToApplyClass;


};
