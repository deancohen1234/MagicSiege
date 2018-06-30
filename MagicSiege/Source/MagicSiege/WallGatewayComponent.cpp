// Fill out your copyright notice in the Description page of Project Settings.

#include "WallGatewayComponent.h"

#define OUT


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

	SetupInputComponent();
	
}


// Called every frame
void UWallGatewayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWallGatewayComponent::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("OpenGateway", IE_Pressed, this, &UWallGatewayComponent::SpawnGateway);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UWallGatewayComponent::SpawnGateway() 
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();

	if (!ActorHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit is null"));
		return;
	}

	UWorld* world = GetWorld();

	if (world)
	{
		//Get hit location and normal to span actor blueprint 
		const FRotator SpawnRotation = HitResult.ImpactNormal.ToOrientationRotator();
		const FVector SpawnLocation = HitResult.ImpactPoint;
		FActorSpawnParameters Parameters;
		world->SpawnActor<AGateway>(GatewayClass ,SpawnLocation, SpawnRotation, Parameters);

		//change the hit wall's actor's collison to make it pass through able
		if (UPrimitiveComponent* PrimitiveComponent = ActorHit->FindComponentByClass<UPrimitiveComponent>())
		{
			PrimitiveComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		}
	}
	
}

const FHitResult UWallGatewayComponent::GetFirstPhysicsBodyInReach()
{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetCastLineStart(),
		GetCastLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParameters
	);
	return HitResult;
}

FVector UWallGatewayComponent::GetCastLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UWallGatewayComponent::GetCastLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * CastMaxDistance);
}

