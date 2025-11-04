// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GandalfAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;

	/* Source */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr <AActor> SourceAvatarActor;

	UPROPERTY()
	TObjectPtr <AController> SourceController;

	UPROPERTY()
	TObjectPtr <ACharacter> SourceCharacter;
	/* Source */

	/* Target */
	UPROPERTY()
	TObjectPtr <UAbilitySystemComponent> TargetASC;

	UPROPERTY()
	TObjectPtr <AActor> TargetAvatarActor;

	UPROPERTY()
	TObjectPtr <AController> TargetController;

	UPROPERTY()
	TObjectPtr <ACharacter> TargetCharacter;
	/* Target */
};

/**
 * 
 */
UCLASS()
class GANDALF_GAS_API UGandalfAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UGandalfAttributeSet();

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override; //It's working before any attribute CURRENT VALUE change.

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override; // It's working before any attribute BASE VALUE change. For clamping attributes values.

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	/* Health */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGandalfAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGandalfAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	/* end Health */


	/* Mana */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGandalfAttributeSet, Mana);


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGandalfAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	/* end Mana */

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
