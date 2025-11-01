// Copyright Jakub Balcerzak


#include "GAS/GandalfAttributeSet.h"
#include "Net/UnrealNetwork.h"

UGandalfAttributeSet::UGandalfAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
}

void UGandalfAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* Health */
	DOREPLIFETIME_CONDITION_NOTIFY(UGandalfAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGandalfAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	/* end Health */

	/* Mana */	
	DOREPLIFETIME_CONDITION_NOTIFY(UGandalfAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGandalfAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	/* end Mana */	
}

void UGandalfAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGandalfAttributeSet, Health, OldHealth);
}

void UGandalfAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGandalfAttributeSet, MaxHealth, OldMaxHealth);
}

void UGandalfAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGandalfAttributeSet, Mana, OldMana);
}

void UGandalfAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGandalfAttributeSet, MaxMana, OldMaxMana);
}
