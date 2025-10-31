// Copyright Jakub Balcerzak


#include "Characters/EnemyCharacter.h"

#include "Gandalf_GAS/Public/GAS/GandalfAbilitySystemComponent.h"
#include "Gandalf_GAS/Public/GAS/GandalfAttributeSet.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGandalfAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGandalfAttributeSet>(TEXT("AttributeSet"));

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

