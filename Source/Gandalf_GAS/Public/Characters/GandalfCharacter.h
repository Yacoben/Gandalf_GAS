// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GandalfCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class GANDALF_GAS_API AGandalfCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AGandalfCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComp;

	/* Input */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> DodgeAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	

};
