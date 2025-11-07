// Copyright Jakub Balcerzak


#include "UI/WidgetController/OverlayWidgetController.h"
#include "GAS/GandalfAttributeSet.h"
#include "GAS/GandalfAbilitySystemComponent.h"
#include "UI/Widgets/GandalfUserWidget.h"

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
		GandalfAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnManaChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GandalfAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnMaxManaChanged.Broadcast(Data.NewValue); });

	Cast<UGandalfAbilitySystemComponent>(AbilitySystemComponent)->OnEffectAssetTagsApplied.AddLambda([this](const FGameplayTagContainer& GameplayTagContainer) 
		{
			for (const FGameplayTag& Tag : GameplayTagContainer)
			{
				if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(MessageTagName)))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					OnMessageWidgetRow.Broadcast(*Row);
				}
			}
		}
	);
}
