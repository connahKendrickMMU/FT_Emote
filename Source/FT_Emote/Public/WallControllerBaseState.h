// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WallControllerBaseState.generated.h"

/**
 * Common errors for this is:
 * 1. Not marking the class as abstract, and not blueprintable
 * 2. Not implementing the pure virtual functions or trying to set the = 0 in the cpp
 * 3. Not providing a protected constructor to prevent instantiation of the base class
 * 3. Trying to instantiate the abstract class directly, which will result in a compile-time error.
 * 4. Not including the necessary header files for the derived classes that will implement this base state.
 */
UCLASS(Abstract, NotBlueprintable)
class FT_EMOTE_API UWallControllerBaseState : public UObject
{
	GENERATED_BODY()

public:
	// note to set to abstract i set the methods to 0, otherwise know as a pure virtual function, 
	// which means that the derived class must implement these methods, otherwise it will also be abstract and cannot be instantiated.
	virtual void EnterState();
	virtual void ExitState();
	virtual void UpdateState(float DeltaTime);
	virtual void HandleState();
};
