// Fill out your copyright notice in the Description page of Project Settings.


#include "WallControllerBaseState_IDLE.h"

void UWallControllerBaseState_IDLE::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering IDLE State"));
}

void UWallControllerBaseState_IDLE::UpdateState(float DeltaTime)
{

}

void UWallControllerBaseState_IDLE::HandleState()
{

}

void UWallControllerBaseState_IDLE::ExitState()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting IDLE State"));
}