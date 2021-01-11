// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <Components/PrimitiveComponent.h>

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	CollisionComponent->SetCapsuleRadius(CollisionCapsuleRadious);
	CollisionComponent->SetCapsuleHalfHeight(CollisionCapsuleHalfHeight);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->BodyInstance.bLockXRotation = true;
	CollisionComponent->BodyInstance.bLockYRotation = true;
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	//MovementComponent->SetUpdatedComponent(RootComponent);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);
	SceneComponent->SetWorldLocation(FVector(0, 0, -50.0f));

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);
	PaperFlipbookComponent->SetWorldRotation(FRotator(0, 90.0f, 0));

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(RootComponent);
#endif
}

void ABasePawn::MoveForward(float Value)
{
	InputForward = Value;
	if (!FMath::IsNearlyZero(Value, 0.001f))
	{
		AddMovementInput(CollisionComponent->GetForwardVector(), Value);
	}
}

void ABasePawn::MoveRight(float Value)
{
	InputRight = Value;
	if (!FMath::IsNearlyZero(Value, 0.001f))
	{
		AddMovementInput(CollisionComponent->GetRightVector(), Value);
	}
}

void ABasePawn::Jump()
{

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ABasePawn::TurnFBToPlayer()
{
	PlayerLocaton = myCharacter->GetActorLocation();
	ObjectLocaton = CollisionComponent->GetComponentLocation();
	ObjectRotation = CollisionComponent->GetComponentRotation();
	AngleToRotate = UKismetMathLibrary::FindLookAtRotation(PlayerLocaton, ObjectLocaton);
	
	FinalRotation = AngleToRotate.Yaw - ObjectRotation.Yaw;

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("PreFinalRotation equals %f"), FinalRotation));

	if (FinalRotation > 180)
	{
		FinalRotation = -180 + (FinalRotation - 180);
	}

	if (FinalRotation < -180)
	{
		FinalRotation = 180 - (-FinalRotation - 180);
	}
}

void ABasePawn::StateFunction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("FinalRotation equals %f"), FinalRotation));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ObjectRotation equals %f"), ObjectRotation.Yaw));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("AngleToRotate equals %f"), AngleToRotate.Yaw));

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ForwardVector %f"), (GetVelocity().X))); 
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ForwardVector %f"), (GetVelocity().Y)));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ForwardVector %f"), (GetVelocity().Z)));
	
	if (IsDead)
	{
		PaperFlipbookComponent->SetLooping(false);
		AttachFlipbook(PFBDeath);
	}
	else if (FMath::IsNearlyZero((GetVelocity().X), 0.00001f))
	{
		PlayIdleAnim();
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("PlayIdleAnim")));

	}
	else
	{
		PlayMoveAnim();
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("PlayMoveAnim")));
	}
}

void ABasePawn::PlayIdleAnim()
{
	if (UKismetMathLibrary::Abs(FinalRotation) < 22.5f)
	{
	AttachFlipbook(FBIdle_180);
	}
	else if (FinalRotation >= 22.5f && FinalRotation < 67.5f)
	{
	AttachFlipbook(FBIdle_135);
	}
	else if (FinalRotation >= 67.5f && FinalRotation < 112.5f)
	{
	AttachFlipbook(FBIdle_90);
	}
	else if (FinalRotation >= 112.5f && FinalRotation < 157.5f)
	{
	AttachFlipbook(FBIdle_45);
	}
	else if (FinalRotation <= -22.5f && FinalRotation > -67.5f)
	{
	AttachFlipbook(FBIdle_225);
	}
	else if (FinalRotation <= -67.5f && FinalRotation > -112.5f)
	{
	AttachFlipbook(FBIdle_270);
	}
	else if (FinalRotation <= -112.5f && FinalRotation > -157.5f)
	{
	AttachFlipbook(FBIdle_315);
	}
	else if (UKismetMathLibrary::Abs(FinalRotation) >= 157.5f)
	{
	AttachFlipbook(FBIdle_0);
	}
}

void ABasePawn::PlayMoveAnim()
{
	//FBLastFrame = PaperFlipbookComponent->GetPlaybackPositionInFrames();

	if (UKismetMathLibrary::Abs(FinalRotation) < 22.5f)
	{
		AttachFlipbook(FBMove_180);
	}
	else if (FinalRotation >= 22.5f && FinalRotation < 67.5f)
	{
		AttachFlipbook(FBMove_135);
	}
	else if (FinalRotation >= 67.5f && FinalRotation < 112.5f)
	{
		AttachFlipbook(FBMove_90);
	}
	else if (FinalRotation >= 112.5f && FinalRotation < 157.5f)
	{
		AttachFlipbook(FBMove_45);
	}
	else if (FinalRotation <= -22.5f && FinalRotation > -67.5f)
	{
		AttachFlipbook(FBMove_225);
	}
	else if (FinalRotation <= -67.5f && FinalRotation > -112.5f)
	{
		AttachFlipbook(FBMove_270);
	}
	else if (FinalRotation <= -112.5f && FinalRotation > -157.5f)
	{
		AttachFlipbook(FBMove_315);
	}
	else if (UKismetMathLibrary::Abs(FinalRotation) >= 157.5f)
	{
		AttachFlipbook(FBMove_0);
	}

}

void ABasePawn::PlayAttackAnim()
{
	if (UKismetMathLibrary::Abs(FinalRotation) < 22.5f)
	{
		AttachFlipbook(FBAttack_180);
	}
	else if (FinalRotation >= 22.5f && FinalRotation < 67.5f)
	{
		AttachFlipbook(FBAttack_135);
	}
	else if (FinalRotation >= 67.5f && FinalRotation < 112.5f)
	{
		AttachFlipbook(FBAttack_90);
	}
	else if (FinalRotation >= 112.5f && FinalRotation < 157.5f)
	{
		AttachFlipbook(FBAttack_45);
	}
	else if (FinalRotation <= -22.5f && FinalRotation > -67.5f)
	{
		AttachFlipbook(FBAttack_225);
	}
	else if (FinalRotation <= -67.5f && FinalRotation > -112.5f)
	{
		AttachFlipbook(FBAttack_270);
	}
	else if (FinalRotation <= -112.5f && FinalRotation > -157.5f)
	{
		AttachFlipbook(FBAttack_315);
	}
	else if (UKismetMathLibrary::Abs(FinalRotation) >= 157.5f)
	{
		AttachFlipbook(FBAttack_0);
	}
}

void ABasePawn::AttachFlipbook(UPaperFlipbook* Flipbook)
{
	PaperFlipbookComponent->SetFlipbook(Flipbook);

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ForwardVector %d"), PaperFlipbookComponent->GetPlaybackPositionInFrames()));
	PaperFlipbookComponent->SetWorldRotation(FRotator(0, ((AngleToRotate)+(FRotator(0, 90.0f, 0))).Yaw, 0));
}


float ABasePawn::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HealthPoints -= Damage;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), Damage));	
	if (HealthPoints <= 0.0f)
	{
		IsDead = true;
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	}
	return Damage;
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TurnFBToPlayer();
	StateFunction();
	
	if (!IsDead)
	{
		MoveForward(1.0f);
	}	
}
	
// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

