// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/ArrowComponent.h>
#include <Components/CapsuleComponent.h>
#include <../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include "Math/UnrealMathUtility.h"
#include "BasePawn.generated.h"

UCLASS()
class DEVILPIGSPROJ_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleAnywhere)
		//class UPawnMovementComponent* MovementComponent;
		class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* CollisionComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetInputForward() {
		return InputForward;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetInputRight() {
		return InputRight;
	}



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasePawn")
		float CollisionCapsuleRadious = 36.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasePawn")
		float CollisionCapsuleHalfHeight = 52.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		class UPaperFlipbookComponent* PaperFlipbookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_45;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_90;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_135;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_180;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_225;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_270;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Idle")
		class UPaperFlipbook* FBIdle_315;


///
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_45;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_90;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_135;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_180;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_225;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		class UPaperFlipbook* FBMove_270;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		float FBLastFrame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Move")
		 UPaperFlipbook* FBMove_315;
///
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_45;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_90;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_135;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_180;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_225;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_270;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Attack")
		class UPaperFlipbook* FBAttack_315;
///
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlipBooks/Death")
		class UPaperFlipbook* PFBDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		FRotator AngleToRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		FRotator AngleToRotateForChoosinFB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		float HealthPoints = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn")
		bool IsDead = false;

	UPROPERTY()
		float FinalRotation;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void DirectionDetect();	
	void TurnFBToPlayer();
	void StateFunction(); 
	void PlayIdleAnim();
	void PlayMoveAnim();
	void PlayAttackAnim();
	void AttachFlipbook(UPaperFlipbook* Flipbook);

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn")
		class UArrowComponent* ArrowComponent;
#endif


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector PlayerLocaton = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector ObjectLocaton = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator ObjectRotation = FRotator::ZeroRotator;

private:

	float InputForward = 0.0f;
	float InputRight = 0.0f;
	ACharacter* myCharacter;
};
