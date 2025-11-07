// Copyright Jakub Balcerzak

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GANDALF_GAS_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void InitAbilityActorInfo() override;
};
