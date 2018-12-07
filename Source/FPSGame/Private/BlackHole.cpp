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
	InnerBlackHole->SetSphereRadius(200);
	InnerBlackHole->SetupAttachment(BlackHole);
	InnerBlackHole->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnOverlapBegin);


	OutterBlackHole = CreateDefaultSubobject<USphereComponent>(TEXT("OutterBlackHole"));
	OutterBlackHole->SetSphereRadius(3000);
	OutterBlackHole->SetupAttachment(BlackHole);

}

void ABlackHole::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Inner Overlap Called"))
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OutterBlackHole->GetOverlappingComponents(OverlappingComponents);

	for (int32 i = 0; i < OverlappingComponents.Num(); i++)
	{
		UPrimitiveComponent* Component = OverlappingComponents[i];
		UE_LOG(LogTemp, Error, TEXT("Overlapping!!!"))
		//Component->AddRadialForce(GetActorLocation(), 1000.0, 10000.0, ERadialImpulseFalloff::RIF_Constant, false);
	}
}


