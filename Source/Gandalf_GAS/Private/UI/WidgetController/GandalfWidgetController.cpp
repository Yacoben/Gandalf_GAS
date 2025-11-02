// Copyright Jakub Balcerzak


#include "UI/WidgetController/GandalfWidgetController.h"

void UGandalfWidgetController::SetWidgetControllerContext(const FWidgetControllerContext& WCContext)
{
	PlayerController = WCContext.PlayerController;
	PlayerState = WCContext.PlayerState;
	AbilitySystemComponent = WCContext.AbilitySystemComponent;
	AttributeSet = WCContext.AttributeSet;
}

void UGandalfWidgetController::BroadcastInitialValues()
{
}

void UGandalfWidgetController::BindCallbacksToDependencies()
{

}
