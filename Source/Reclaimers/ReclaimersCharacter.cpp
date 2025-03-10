// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReclaimersCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "ThirdParty/Discord/discord.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


/*									INFORMATION								*/
//						This file defines our base character.
//		Character Properties + Movement are managed and handled within this file.
//				This C++ Character is used as base of the BP equivalent.
//				The BP Character is used for mesh and asset management.
/*																			*/

/* Discord Integration */
discord::Core* core{};

//////////////////////////////////////////////////////////////////////////
// AReclaimersCharacter

AReclaimersCharacter::AReclaimersCharacter()
{
	// Start of default UE5 Properties //

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// End of default UE5 Properties //

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - HEALTH
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - STAMINA
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - HUNGER
	HungerComponent = CreateDefaultSubobject<UHungerComponent>(TEXT("HungerComponent"));

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - THIRST
	ThirstComponent = CreateDefaultSubobject<UThirstComponent>(TEXT("ThirstComponent"));

	//////////////////////////////////////////////////////////////////////////
	// CHARACTER - MOVEMENT
	MovementStateComponent = CreateDefaultSubobject<UMovementStateComponent>(TEXT("MovementStateComponent"));

	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	RunSpeed = WalkSpeed * 1.5;
	AmbushSpeedMultiplier = 1.2f;
}

void AReclaimersCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/* Discord Integration */
	auto result = discord::Core::Create(1180436830961815552, DiscordCreateFlags_Default, &core);
	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Fruit Loops");
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void AReclaimersCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/* Discord Integration */
	::core->RunCallbacks();

	// Check whether the character is not moving
	// TODO: set JUMPING State whenever the character is currently jumping.
	if (MovementStateComponent) {
		if (GetVelocity().Y == 0.0f && !GetCharacterMovement()->IsFalling()) {
			MovementStateComponent->SetMovementState(EMovementState::E_IDLE);
		}

		/*
		// If the character is running / sprinting, decrease / consume stamina.
		if (MovementStateComponent->IsIdle()) {
			if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
				UE_LOG(LogTemplateCharacter, Warning, TEXT("(IDLE) INCREASING STAMINA ..."));
				StaminaComponent->SetStamina(
					FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, StaminaComponent->GetRecoveryRate())
				);
			}
		} // Increase Stamina by recharge rate 1x.
		else if (MovementStateComponent->IsResting()) {
			if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
				UE_LOG(LogTemplateCharacter, Warning, TEXT("(RESTING) INCREASING STAMINA ..."));
				StaminaComponent->SetStamina(
					FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, (float)(StaminaComponent->GetRecoveryRate() * 2.5))
				);
			}
		} // Increase Stamina by recharge rate 2.5x
		else if (MovementStateComponent->IsWalking()) {
			if (StaminaComponent->GetStamina() < StaminaComponent->GetMaxStamina()) {
				UE_LOG(LogTemplateCharacter, Warning, TEXT("(WALKING) INCREASING STAMINA ..."));
				StaminaComponent->SetStamina(
					FMath::FInterpConstantTo(StaminaComponent->GetStamina(), StaminaComponent->GetMaxStamina(), DeltaTime, (float)(StaminaComponent->GetRecoveryRate() * .5))
				);
			}
		} // Increase Stamina by recharge rate 0.5x
		else if (MovementStateComponent->IsRunning()) { // Decrease Stamina.
			if (StaminaComponent->GetStamina() > 0.0f) {
				UE_LOG(LogTemplateCharacter, Warning, TEXT("DECREASING STAMINA ..."));
				StaminaComponent->SetStamina(
					FMath::FInterpConstantTo(StaminaComponent->GetStamina(), 0.0f, DeltaTime, StaminaComponent->GetDecayRate())
				);
			}
			else
			{
				ResetSprinting();
			}
		}
		*/
	}
	// HealthComponent->SetHealth(HealthComponent->GetHealth() - .1f);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AReclaimersCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AReclaimersCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AReclaimersCharacter::Look);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AReclaimersCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AReclaimersCharacter::StopSprinting);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AReclaimersCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		// Change character movement state to walking
		if (MovementStateComponent && !MovementStateComponent->IsRunning()) {
			MovementStateComponent->SetMovementState(EMovementState::E_WALKING);
		}
	}
}

void AReclaimersCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AReclaimersCharacter::Sprint(const FInputActionValue& Value) {
	if (StaminaComponent->CanSprint()) {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("SPRINTING - STARTED"));

		MovementStateComponent->SetMovementState(EMovementState::E_RUNNING);
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AReclaimersCharacter::StopSprinting() {
	UE_LOG(LogTemplateCharacter, Warning, TEXT("SPRINTING - STOPPED"));

	MovementStateComponent->SetMovementState(EMovementState::E_WALKING);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AReclaimersCharacter::ResetSprinting() {
	UE_LOG(LogTemplateCharacter, Warning, TEXT("SPRINTING - RESET"));

	// If the character is running while he can't, abort.
	if (MovementStateComponent->IsRunning()) {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("SPRINTING - FORCE STOPPED"));
		StopSprinting();
	}
}