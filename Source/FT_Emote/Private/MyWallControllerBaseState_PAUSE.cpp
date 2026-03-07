// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWallControllerBaseState_PAUSE.h"

void UMyWallControllerBaseState_PAUSE::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering PAUSE State"));
}

void UMyWallControllerBaseState_PAUSE::UpdateState(float DeltaTime)
{
	
}

void UMyWallControllerBaseState_PAUSE::HandleState()
{

}

void UMyWallControllerBaseState_PAUSE::ExitState()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting PAUSE State"));
}