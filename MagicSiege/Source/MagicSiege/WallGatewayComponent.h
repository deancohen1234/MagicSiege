// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

#include "Gateway.h"
#include "CollisionQueryParams.h"

#include "GameFramework/Actor.h"
#include "WallGatewayComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICSIEGE_API UWallGatewayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallGatewayComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGateway> GatewayClass;

	float CastMaxDistance = 1000.f;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void SetupInputComponent();
	void SpawnGateway();
	const FHitResult GetFirstPhysicsBodyInReach();

	FVector GetCastLineStart();
	FVector GetCastLineEnd();

	UInputComponent* InputComponent = nullptr;
	
};
