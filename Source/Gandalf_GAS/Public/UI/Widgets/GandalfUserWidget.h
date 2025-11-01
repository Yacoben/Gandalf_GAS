// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GandalfUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GANDALF_GAS_API UGandalfUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);	

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
