// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ���� ���� �÷��̾� ĳ���Ϳ��� ���� ������
	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 34.f;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* BounceSound;

	// ���� ������ ���� ����
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundAttenuation* BounceSoundAttenuation;

	// �÷��̾ �¾��� �� �������� ������ ��ƼŬ �ý���
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;

	// �÷��̾ �¾��� �� ���� ����
	UPROPERTY(EditAnywhere, Category = Particles)
	class USoundBase* DamageSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}
};
