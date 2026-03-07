// Fill out your copyright notice in the Description page of Project Settings.


#include "WallController.h"
#include "WallControllerBaseState_IDLE.h"
#include "MyWallControllerBaseState_PLAY.h"// saw the my too late
#include "MyWallControllerBaseState_PAUSE.h"
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
	}
	if (!PlayState)
	{
		PlayState = NewObject<UMyWallControllerBaseState_PLAY>(this);
	}
	if (!PauseState)
	{
		PauseState = NewObject<UMyWallControllerBaseState_PAUSE>(this);
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