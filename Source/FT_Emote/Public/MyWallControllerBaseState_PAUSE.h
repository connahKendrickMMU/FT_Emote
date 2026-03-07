// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallControllerBaseState.h"
#include "MyWallControllerBaseState_PAUSE.generated.h"

/**
 * This is a simple state we simply allow a small break between spawns, but this could be tailored
 * e.g. less time between spawns, set wall speed, particle effect start and ends
 * Score tracking, and general difficulty modifications
 */
UCLASS()
class FT_EMOTE_API UMyWallControllerBaseState_PAUSE : public UWallControllerBaseState
{
	GENERATED_BODY()
public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void HandleState() override;
};
