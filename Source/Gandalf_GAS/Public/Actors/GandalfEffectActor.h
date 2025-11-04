// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"
#include "GandalfEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EInfiniteEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class GANDALF_GAS_API AGandalfEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGandalfEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	FGameplayEffectSpecHandle GetEffectSpecHandleForTargetASC(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void ApplyAllEffectToTarget(const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffectClasses, AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void OnEndOverlap(AActor* TargetActor);

	/* Gameplay Effect Classes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Instant")
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Duration")
	TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Infinite")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;
	/* Gameplay Effect Classes */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	bool bDestroyOnEffectRemoval = false;

	/* EEffectApplicationPolicy */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Instant")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	/* EEffectApplicationPolicy */

	/* EInfiniteEffectRemovalPolicy */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Infinite")
	EInfiniteEffectRemovalPolicy InfiniteEffectRemovalPolicy = EInfiniteEffectRemovalPolicy::RemoveOnEndOverlap;
	/* EInfiniteEffectRemovalPolicy */

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandlesMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects|Stats")
	float ActorLevel = 1.f;
};
