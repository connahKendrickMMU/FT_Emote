// Fill out your copyright notice in the Description page of Project Settings.


#include "WallControllerBaseState_PLAY.h"
#include "WallController.h" 
void UWallControllerBaseState_PLAY::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering PLAY State"));
	// spawn a random wall
	Controller->CreateWall();
}

void UWallControllerBaseState_PLAY::UpdateState(float DeltaTime)
{
	// move the spawned wall
	if (Controller->CurrentWall)
	{
		FVector NewPos = Controller->CurrentWall->GetActorLocation();
		NewPos.Y -= 100 * DeltaTime;
		Controller->CurrentWall->SetActorLocation(NewPos);
	}
}

void UWallControllerBaseState_PLAY::HandleState()
{
	// no wall means the spawn failed, so there is nothing to check
	if (!Controller->CurrentWall) return;

	//Check if the wall should despawn and we should pause for a break
	if (Controller->CurrentWall->GetActorLocation().Y < Controller->GetActorLocation().Y - 100)
	{
		Controller->ChangeState(Controller->PauseState);
	}

}

void UWallControllerBaseState_PLAY::ExitState()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting PLAY State"));
	// exit the state clear up the wall
	if (Controller->CurrentWall)
	{
		Controller->CurrentWall->Destroy();
	}
	Controller->CurrentWall = nullptr;
}