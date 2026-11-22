// Fill out your copyright notice in the Description page of Project Settings.


#include "WallController.h"
#include "WallControllerBaseState_IDLE.h"
#include "WallControllerBaseState_PLAY.h"
#include "WallControllerBaseState_PAUSE.h"
// Sets default values
AWallController::AWallController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StartPos = CreateDefaultSubobject<USceneComponent>(TEXT("StartPos"));
	EndPos = CreateDefaultSubobject<USceneComponent>(TEXT("EndPos"));
	SetRootComponent(StartPos);


	StartGameBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StartBox"));
	StartGameBox->SetBoxExtent(FVector(150.f, 10.f, 150.f));
	StartGameBox->SetGenerateOverlapEvents(true);

	EndGameBox = CreateDefaultSubobject< UBoxComponent>(TEXT("EndBox"));
	EndGameBox->SetBoxExtent(FVector(3000.f, 3000.f, 30.f));
	// at the start we onlyt care about the start game box, so we disable the end game box
	EndGameBox->SetGenerateOverlapEvents(false);

	// bind to the functions
	StartGameBox->OnComponentBeginOverlap.AddDynamic(this, &AWallController::StartGameTriggered);
	EndGameBox->OnComponentBeginOverlap.AddDynamic(this, &AWallController::EndGameTriggered);
	
	// need bind the attachments
	StartGameBox->SetupAttachment(StartPos);
	EndPos->SetupAttachment(StartPos);
	EndPos->SetRelativeLocation(FVector(0.f, 0.f, -210.f));
	EndGameBox->SetupAttachment(EndPos);
}

// Called when the game starts or when spawned
void AWallController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("We are in the Begin Play of the Wall Controller"));

	// note i am doing this the full CPP route for the player you can epose and place these in the blueprint 
	if(!IdleState)
	{
		IdleState = NewObject<UWallControllerBaseState_IDLE>(this);
		IdleState->SetController(this);
	}
	if (!PlayState)
	{
		PlayState = NewObject<UWallControllerBaseState_PLAY>(this);
		PlayState->SetController(this);
	}
	if (!PauseState)
	{
		PauseState = NewObject<UWallControllerBaseState_PAUSE>(this);
		PauseState->SetController(this);
	}
	CurrentState = IdleState;
	if (CurrentState)
	{
		CurrentState->EnterState();// yes it's empty but this is good practice
	}
}

// Called every frame
void AWallController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentState)
	{
		CurrentState->UpdateState(DeltaTime);
		CurrentState->HandleState();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO STATE AHHHHHHH"));
	}
	
}

void AWallController::StartGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Game Triggered"));
	StartGameBox->SetGenerateOverlapEvents(false);
	EndGameBox->SetGenerateOverlapEvents(true);
	ChangeState(PauseState); // enter the pause stae for a brief gap then begin the game woop
}

void AWallController::EndGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("We are in the End Game now"));
	StartGameBox->SetGenerateOverlapEvents(true);
	EndGameBox->SetGenerateOverlapEvents(false);
	ChangeState(IdleState);
}

void AWallController::ChangeState(UWallControllerBaseState* NewState)
{
	if (CurrentState)
	{
		// notice we force the exit state to run furst to clean up or reset any functionality
		CurrentState->ExitState();
		CurrentState = NewState;
		// we also force into the initialisation
		CurrentState->EnterState();
	}
}

void AWallController::CreateWall()
{
	// RandRange(0, -1) would read outside the array if no walls are assigned
	if (WallsToControl.IsEmpty()) return;

	TSubclassOf<AActor> WallClass = WallsToControl[FMath::RandRange(0, WallsToControl.Num() - 1)]; // get random wall

	if (WallClass)
	{
		// in unreal we need to spefify these dont worry about it for now
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector SpawnPos = StartPos->GetComponentLocation();
		SpawnPos.Y += SpawnDistance;

		if (bSnapToGround)
		{
			// trace straight down for static geometry only, so we hit the floor and not the player
			FHitResult Hit;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			const FVector TraceStart = SpawnPos + FVector(0.f, 0.f, 500.f);
			const FVector TraceEnd = SpawnPos - FVector(0.f, 0.f, 2000.f);
			if (GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, FCollisionObjectQueryParams(ECC_WorldStatic), QueryParams))
			{
				SpawnPos.Z = Hit.ImpactPoint.Z;
			}
		}
		SpawnPos.Z += SpawnHeightOffset;
		CurrentWall = GetWorld()->SpawnActor<AActor>(
			WallClass,
			SpawnPos,
			StartPos->GetComponentRotation(),
			Params
		);

		UE_LOG(LogTemp, Warning, TEXT("Spawned wall: %s"), *GetNameSafe(CurrentWall));
	}

}
