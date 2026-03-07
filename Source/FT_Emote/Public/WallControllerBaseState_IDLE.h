// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallControllerBaseState.h"
#include "WallControllerBaseState_IDLE.generated.h"

/**
 * This class is the idle statem it handles waiting for the player to enter the play trigger
 * most functionality is blank which is intentional as we wait for something to occur and drive our states
 */
UCLASS()
class FT_EMOTE_API UWallControllerBaseState_IDLE : public UWallControllerBaseState
{
	GENERATED_BODY()
public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void HandleState() override;
};
