// Copyright Jakub Balcerzak


#include "UI/WidgetController/OverlayWidgetController.h"
#include <GAS/GandalfAttributeSet.h>

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UGandalfAttributeSet* GandalfAttributeSet = CastChecked<UGandalfAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(GandalfAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GandalfAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(GandalfAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(GandalfAttributeSet->GetMaxMana());

}
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UGandalfAttributeSet* GandalfAttributeSet = CastChecked<UGandalfAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
