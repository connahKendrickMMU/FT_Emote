// Fill out your copyright notice in the Description page of Project Settings.


#include "WallControllerBaseState_PAUSE.h"
#include "WallController.h"

void UWallControllerBaseState_PAUSE::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering PAUSE State"));
	TimePassed = 0;
}

void UWallControllerBaseState_PAUSE::UpdateState(float DeltaTime)
{
	// count how long has passed
	TimePassed += DeltaTime;
}

void UWallControllerBaseState_PAUSE::HandleState()
{
	if (TimePassed > Delay)
	{
		Controller->ChangeState(Controller->PlayState);
	}
}

void UWallControllerBaseState_PAUSE::ExitState()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting PAUSE State"));
}