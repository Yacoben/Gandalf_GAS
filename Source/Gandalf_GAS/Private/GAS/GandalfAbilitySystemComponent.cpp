// Copyright Jakub Balcerzak


#include "GAS/GandalfAbilitySystemComponent.h"

void UGandalfAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGandalfAbilitySystemComponent::EffectApplied);
}

void UGandalfAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);
	OnEffectAssetTagsApplied.Broadcast(GameplayTagContainer);
}
