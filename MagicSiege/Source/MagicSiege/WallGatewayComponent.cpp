// Fill out your copyright notice in the Description page of Project Settings.

#include "WallGatewayComponent.h"


// Sets default values for this component's properties
UWallGatewayComponent::UWallGatewayComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallGatewayComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* actor = GetOwner();

	UE_LOG(LogTemp, Warning, TEXT("Wall Gateway Owner is %s"), *actor->GetName());
	
}


// Called every frame
void UWallGatewayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

