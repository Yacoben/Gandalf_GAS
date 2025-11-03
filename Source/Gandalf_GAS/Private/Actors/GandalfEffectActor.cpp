// Copyright Jakub Balcerzak


#include "Actors/GandalfEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"


AGandalfEffectActor::AGandalfEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root")));


}

void AGandalfEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FGameplayEffectSpecHandle AGandalfEffectActor::GetEffectSpecHandleForTargetASC(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent* ASC)
{
	if (!IsValid(ASC)) return FGameplayEffectSpecHandle();

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	return EffectSpecHandle;
}

void AGandalfEffectActor::ApplyAllEffectToTarget(const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffectClasses, AActor* TargetActor)
{
	if (!IsValid(TargetActor)) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	for (const TSubclassOf<UGameplayEffect>& GameplayEffectClass : GameplayEffectClasses)
	{
		if (!IsValid(GameplayEffectClass)) continue;
		const FGameplayEffectSpecHandle EffectSpecHandle = GetEffectSpecHandleForTargetASC(GameplayEffectClass, TargetASC);
		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite; // Gameplay Effect

		if (bIsInfinite && InfiniteEffectRemovalPolicy == EInfiniteEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			if (ActiveGameplayEffectHandle.IsValid())
			{
				ActiveEffectHandlesMap.Add(ActiveGameplayEffectHandle, TargetASC);
			}
		}
	}
}


void AGandalfEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyAllEffectToTarget(InstantGameplayEffectClasses, TargetActor);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyAllEffectToTarget(DurationGameplayEffectClasses, TargetActor);	
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyAllEffectToTarget(InfiniteGameplayEffectClasses, TargetActor);
	}

}

void AGandalfEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyAllEffectToTarget(InstantGameplayEffectClasses, TargetActor);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyAllEffectToTarget(DurationGameplayEffectClasses, TargetActor);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyAllEffectToTarget(InfiniteGameplayEffectClasses, TargetActor);
	}

	if (InfiniteEffectRemovalPolicy == EInfiniteEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		for (auto It = ActiveEffectHandlesMap.CreateConstIterator(); It; ++It)
		{
			if (It.Value() == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(It.Key(), 1);
				HandlesToRemove.Add(It.Key());
			}
		}

		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandlesMap.Remove(Handle);
		}
	}
}

