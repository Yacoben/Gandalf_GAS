// Copyright Jakub Balcerzak


#include "UI/Widgets/GandalfUserWidget.h"

void UGandalfUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}
