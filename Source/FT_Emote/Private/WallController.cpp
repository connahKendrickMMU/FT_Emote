// Fill out your copyright notice in the Description page of Project Settings.


#include "WallController.h"

// Sets default values
AWallController::AWallController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StartPos = CreateDefaultSubobject<USceneComponent>(TEXT("StartPos"));
	StartPos->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	EndPos = CreateDefaultSubobject<USceneComponent>(TEXT("EndPos"));
	EndPos->SetRelativeLocation(FVector(0.f, 0.f, -5.f));
	SetRootComponent(StartPos);


	StartGameBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StartBox"));
	StartGameBox->SetBoxExtent(FVector(50.f, 10.f, 50.f));
	StartGameBox->SetGenerateOverlapEvents(true);

	EndGameBox = CreateDefaultSubobject< UBoxComponent>(TEXT("EndBox"));
	EndGameBox->SetBoxExtent(FVector(1000.f, 1000.f, 30.f));
	// at the start we onlyt care about the start game box, so we disable the end game box
	EndGameBox->SetGenerateOverlapEvents(false);

	// bind to the functions
	StartGameBox->OnComponentBeginOverlap.AddDynamic(this, &AWallController::StartGameTriggered);
	EndGameBox->OnComponentBeginOverlap.AddDynamic(this, &AWallController::EndGameTriggered);
	
	// need bind the attachments
	StartGameBox->SetupAttachment(StartPos);
	EndPos->SetupAttachment(StartPos);
	EndGameBox->SetupAttachment(EndPos);

}

// Called when the game starts or when spawned
void AWallController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("We are in the Begin Play of the Wall Controller"));
	
	
}

// Called every frame
void AWallController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallController::StartGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Game Triggered"));
	StartGameBox->SetGenerateOverlapEvents(false);
	EndGameBox->SetGenerateOverlapEvents(true);
}

void AWallController::EndGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("We are in the End Game now"));
	StartGameBox->SetGenerateOverlapEvents(true);
	EndGameBox->SetGenerateOverlapEvents(false);
}

