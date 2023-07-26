// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation=GetActorLocation();
	SetActorLocation(StartLocation);
	UE_LOG(LogTemp, Display, TEXT("Name: %s ;"), *GetName());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurVector = GetActorLocation();
	if ( ShouldReturn(CurVector) )
	{
		StartLocation += Speed.GetSafeNormal()*MaxRange ;
		SetActorLocation(CurVector);
		Speed *= -1;
	} 
	else 
	{
		CurVector += Speed*DeltaTime;
		SetActorLocation(CurVector);	
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FVector CurVector = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Platform %s spawned"),*GetName()); 
	FRotator CurRotation = GetActorRotation();
	CurRotation += RotationSpeed * DeltaTime;
	AddActorLocalRotation(RotationSpeed * DeltaTime);
	/*CurVector += Speed*DeltaTime;
	SetActorLocation(CurVector);	
	float DistanceMoved = FVector::Dist(CurVector, StartLocation);
	if ( DistanceMoved > MaxRange )
	{
		float OverMoved = DistanceMoved - MaxRange;
		UE_LOG(LogTemp, Display, TEXT("Platform %s overmoved: %f ;"), *GetName(), OverMoved);
		StartLocation += Speed.GetSafeNormal()*MaxRange ;
		Speed *= -1;
	}*/

}


bool AMovingPlatform::ShouldReturn(FVector CurVector) const
{
	float DistanceMoved = FVector::Dist(CurVector, StartLocation);
	return (DistanceMoved > MaxRange);
}