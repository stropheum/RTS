// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/DecalActor.h"
#include "NiagaraFunctionLibrary.h"
#include "CommandHandler.h"


// Sets default values for this component's properties
UCommandHandler::UCommandHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCommandHandler::BeginPlay()
{
	Super::BeginPlay();
}

void UCommandHandler::SpawnCommandReticle(const FVector3d& Location) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		FxCursor, Location,
		FRotator::ZeroRotator,
		FVector(1.f, 1.f, 1.f),
		true,
		true,
		ENCPoolMethod::None,
		true);

	if (!CommandReticleDecal) return;
	FActorSpawnParameters SpawnParams;
	if (AActor* SpawnDecal = GetWorld()->SpawnActor<AActor>(CommandReticleDecal, Location, FRotator::ZeroRotator, SpawnParams))
	{
		UE_LOG(LogTemp, Display, TEXT("Spawn Reticle Decal"));
	}
}

void UCommandHandler::HandleIssueActiveCommand()
{
	UE_LOG(LogTemp, Fatal, TEXT("IssueActiveCommand"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HandleIssueActiveCommand"));
}

void UCommandHandler::HandleIssueMoveCommand()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HandleIssueMoveCommand"));
	UWorld* World = GetWorld();
	if (!World) return;
	// AActor* DecalActor = World->SpawnActor<BP_CommandReticle>()
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController is null"));
		return;
	}
	FHitResult Hit;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		UE_LOG(LogTemp, Log, TEXT("Spawning command reticle"));
		SpawnCommandReticle(Hit.Location);
	}
}

// Called every frame
void UCommandHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

