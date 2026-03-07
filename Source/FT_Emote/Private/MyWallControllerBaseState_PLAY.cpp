// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWallControllerBaseState_PLAY.h"

void UMyWallControllerBaseState_PLAY::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering PLAY State"));
	// spawn a random wall
}

void UMyWallControllerBaseState_PLAY::UpdateState(float DeltaTime)
{
	// move the spawned wall
}

void UMyWallControllerBaseState_PLAY::HandleState()
{
	//Check if the wall should despawn and we should pause for a break
}

void UMyWallControllerBaseState_PLAY::ExitState()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting PLAY State"));
	// exit the state clear up the wall
}