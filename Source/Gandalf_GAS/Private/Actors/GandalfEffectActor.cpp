// Copyright Jakub Balcerzak


#include "Actors/GandalfEffectActor.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>

AGandalfEffectActor::AGandalfEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root")));


}

void AGandalfEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGandalfEffectActor::ApplyEffectToTarget(TSubclassOf<UGameplayEffect> GameplayEffectClass, AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

