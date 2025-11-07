// Copyright Jakub Balcerzak


#include "Characters/GandalfCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Player/GandalfPlayerState.h>
#include "Gandalf_GAS/Public/GAS/GandalfAbilitySystemComponent.h"
#include "Gandalf_GAS/Public/GAS/GandalfAttributeSet.h"
#include <Player/GandalfPlayerController.h>
#include <UI/HUD/GandalfHUD.h>

AGandalfCharacter::AGandalfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bEnableCameraLag = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AGandalfCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AGandalfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGandalfCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info here for the server
	InitAbilityActorInfo();
}

void AGandalfCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info here for the client
	InitAbilityActorInfo();
}

void AGandalfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGandalfCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGandalfCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGandalfCharacter::Jump);
		Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AGandalfCharacter::Zoom);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AGandalfCharacter::Attack);
	}

}

void AGandalfCharacter::InitAbilityActorInfo()
{
	AGandalfPlayerState* GandalfPlayerState = GetPlayerState<AGandalfPlayerState>();
	check(GandalfPlayerState);
	GandalfPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GandalfPlayerState, this);
	Cast<UGandalfAbilitySystemComponent>(GandalfPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = GandalfPlayerState->GetAbilitySystemComponent();
	AttributeSet = GandalfPlayerState->GetAttributeSet();

	if (AGandalfPlayerController* GandalfPlayerController = Cast<AGandalfPlayerController>(GetController()))
	{
		if (AGandalfHUD* GandalfHUD = Cast<AGandalfHUD>(GandalfPlayerController->GetHUD()))
		{
			GandalfHUD->InitOverlay(GandalfPlayerController, GandalfPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

}

void AGandalfCharacter::Move(const FInputActionValue& Value)
{
	if (GetController())
	{
		const FVector2D MoveAxisValue = Value.Get<FVector2D>();

		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MoveAxisValue.Y);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MoveAxisValue.X);
	}
}

void AGandalfCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AGandalfCharacter::Zoom(const FInputActionValue& Value)
{
}

void AGandalfCharacter::Attack(const FInputActionValue& Value)
{
}

void AGandalfCharacter::Dodge(const FInputActionValue& Value)
{
}

