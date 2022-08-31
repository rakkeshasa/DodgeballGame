// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "DodgeballFunctionLibrary.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* World,
	FVector Location,
	const AActor* TargetActor,
	TArray<const AActor*> IgnoreActors)
{
	FHitResult Hit;

	// 라인 트레이스의 시작 및 끝 위치
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;
	// 지정한 액터들을 무시한다.
	QueryParams.AddIgnoredActors(IgnoreActors);

	// 라인 트레이스를 실행한다.
	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// 게임에서 라인 트레이스를 보여준다.
	DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}