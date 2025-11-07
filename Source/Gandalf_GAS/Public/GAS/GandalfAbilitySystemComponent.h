// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GandalfAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags */);


/**
 * 
 */
UCLASS()
class GANDALF_GAS_API UGandalfAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

	FEffectAssetTags OnEffectAssetTagsApplied;

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);


};
