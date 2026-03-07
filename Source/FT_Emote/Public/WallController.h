// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallControllerBaseState.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "WallController.generated.h"

UCLASS()
class FT_EMOTE_API AWallController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerStates")
	UWallControllerBaseState* CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerStates")
	UWallControllerBaseState* IdleState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerStates")
	UWallControllerBaseState* ActiveState;

	// these enable the boxes to have a position and rotation
	USceneComponent* StartPos;
	USceneComponent* EndPos;

	// box to start game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerCollider")
	UBoxComponent* StartGameBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerCollider")
	UBoxComponent* EndGameBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallControllerWalls")
	TArray<TSubclassOf<class AActor>> WallsToControl;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void EndGameTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
