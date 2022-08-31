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

	// ���� Ʈ���̽��� ���� �� �� ��ġ
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;
	// ������ ���͵��� �����Ѵ�.
	QueryParams.AddIgnoredActors(IgnoreActors);

	// ���� Ʈ���̽��� �����Ѵ�.
	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// ���ӿ��� ���� Ʈ���̽��� �����ش�.
	DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}