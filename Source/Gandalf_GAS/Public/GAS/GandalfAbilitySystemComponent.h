// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GandalfAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GANDALF_GAS_API UGandalfAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
