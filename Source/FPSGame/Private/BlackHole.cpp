// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackHole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHole"));
	BlackHole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BlackHole;

	InnerBlackHole = CreateDefaultSubobject<USphereComponent>(TEXT("InnerBlackHole"));
	InnerBlackHole->SetSphereRadius(100);
	InnerBlackHole->SetupAttachment(BlackHole);
	InnerBlackHole->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	OutterBlackHole = CreateDefaultSubobject<USphereComponent>(TEXT("OutterBlackHole"));
	OutterBlackHole->SetSphereRadius(3000);
	OutterBlackHole->SetupAttachment(BlackHole);

}

void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingOuterComponents;

	OutterBlackHole->GetOverlappingComponents(OverlappingOuterComponents);

	for (int32 i = 0; i < OverlappingOuterComponents.Num(); i++)
	{
		UPrimitiveComponent* Component = OverlappingOuterComponents[i];

		if (Component && Component->IsSimulatingPhysics())
		{
			Component->AddRadialForce(GetActorLocation(), OutterBlackHole->GetScaledSphereRadius(), -2000.0, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}


