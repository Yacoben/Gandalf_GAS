// Copyright Jakub Balcerzak


#include "Actors/GandalfEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include <GAS/GandalfAttributeSet.h>

AGandalfEffectActor::AGandalfEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
}

void AGandalfEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGandalfEffectActor::OnOverlapBegin);
}

void AGandalfEffectActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UGandalfAttributeSet* GandalfAttributeSet = Cast<UGandalfAttributeSet>(ASInterface->GetAbilitySystemComponent()->GetAttributeSet(UGandalfAttributeSet::StaticClass()));

		UGandalfAttributeSet* MutableGandalfAttributeSet = const_cast<UGandalfAttributeSet*>(GandalfAttributeSet);
		MutableGandalfAttributeSet->SetHealth(GandalfAttributeSet->GetHealth() + 10.f);
		MutableGandalfAttributeSet->SetMana(GandalfAttributeSet->GetMana() + 10.f);
	}
}

