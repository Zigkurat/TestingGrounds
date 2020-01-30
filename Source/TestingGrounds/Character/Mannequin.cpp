// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Weapons/Gun.h"

AMannequin::AMannequin()
{
	PrimaryActorTick.bCanEverTick = true;

	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("TP_SpringArm"));
	ThirdPersonSpringArm->SetupAttachment(GetCapsuleComponent());
	ThirdPersonSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	ThirdPersonSpringArm->TargetArmLength = 300.f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(FName("TP_Camera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm);
	ThirdPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	ThirdPersonCamera->bUsePawnControlRotation = false;
	ThirdPersonCamera->SetAutoActivate(false);

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(2.44f, 5.75f, 73.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetAutoActivate(true);

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCamera);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetRelativeRotation(FRotator(5.2f, -19.19f, 1.9f));
	FirstPersonMesh->SetRelativeLocation(FVector(3.3f, -5.f, -161.32f));
}

void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(WeaponBlueprint))
	{
		Weapon = GetWorld()->SpawnActor<AGun>(WeaponBlueprint);

		if (IsPlayerControlled())
		{
			Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		else
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}

		Weapon->FirstPersonAnimInstance = FirstPersonMesh->GetAnimInstance();
		Weapon->ThirdPersonAnimInstance = GetMesh()->GetAnimInstance();
	}
}

void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMannequin::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
}

void AMannequin::UnPossessed() 
{
	Super::UnPossessed();

	if (Weapon != nullptr) {
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

void AMannequin::PullTrigger()
{
	if (ensure(Weapon))
	{
		Weapon->OnFire();
	}
}