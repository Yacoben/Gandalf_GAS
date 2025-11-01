// Copyright Jakub Balcerzak


#include "Player/GandalfPlayerState.h"
#include "Gandalf_GAS/Public/GAS/GandalfAbilitySystemComponent.h"
#include "Gandalf_GAS/Public/GAS/GandalfAttributeSet.h"


AGandalfPlayerState::AGandalfPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGandalfAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGandalfAttributeSet>(TEXT("AttributeSet"));

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AGandalfPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
