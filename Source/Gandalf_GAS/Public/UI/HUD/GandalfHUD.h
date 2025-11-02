// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GandalfHUD.generated.h"

class UGandalfUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerContext;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class GANDALF_GAS_API AGandalfHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UGandalfUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerContext& WCContext);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGandalfUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
