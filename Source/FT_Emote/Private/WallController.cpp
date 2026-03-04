// Fill out your copyright notice in the Description page of Project Settings.


#include "WallController.h"

// Sets default values
AWallController::AWallController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

