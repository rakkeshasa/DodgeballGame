// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 현재 플레이어가 제어하는 캐릭터 구하기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 매 프레임마다 플레이어 캐릭터를 바라본다
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget();

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	// 새 닷지볼 스폰하기
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
	Projectile->FinishSpawning(SpawnTransform);
}

