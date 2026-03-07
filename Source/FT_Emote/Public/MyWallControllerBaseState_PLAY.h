// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallControllerBaseState.h"
#include "MyWallControllerBaseState_PLAY.generated.h"

/**
 * This handles the spawning, movements and despawning of the walls
 * notice i split the functionality into a nice set
 * Enter state handles the spawn
 * Update handles the movement
 * Handle checks if we shoudl switch state
 * Exit cleans up the model
 */
UCLASS()
class FT_EMOTE_API UMyWallControllerBaseState_PLAY : public UWallControllerBaseState
{
	GENERATED_BODY()
public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void HandleState() override;
};
