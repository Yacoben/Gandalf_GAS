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

	for (const FGameplayTag& Tag : GameplayTagContainer)
	{
		//  Broadcast all tags applied by the effect to the Widget Controller
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Effect Tag: %s"), *Tag.ToString()));
	}
}
