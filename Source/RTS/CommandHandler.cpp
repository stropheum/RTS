// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/DecalActor.h"
#include "NiagaraFunctionLibrary.h"
#include "CommandHandler.h"
#include "CommandableInterface.h"
#include "RTSHud.h"


// Sets default values for this component's properties
UCommandHandler::UCommandHandler() : FxCursor(nullptr), PlayerController(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCommandHandler::BeginPlay()
{
	Super::BeginPlay();
	CachePlayerController();
}

void UCommandHandler::SpawnCommandReticle(const FVector3d& CommandLocation) const
{
	if (FxCursor && (ReticleType == EReticleType::Vfx || ReticleType == EReticleType::Both))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		FxCursor, CommandLocation,
		FRotator::ZeroRotator,
		FVector(1.f, 1.f, 1.f),
		true,
		true,
		ENCPoolMethod::None,
		true);	
	}

	if (CommandReticleDecal && (ReticleType == EReticleType::Decal || ReticleType == EReticleType::Both))
	{
		const FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(CommandReticleDecal, CommandLocation, FRotator::ZeroRotator, SpawnParams);
	}
}

void UCommandHandler::CachePlayerController()
{
	const UWorld* World = GetWorld();
	ensureMsgf(World, TEXT("UCommandHandler::CachePlayerController World != nullptr"));
	PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController is null"));
	}
}

void UCommandHandler::MoveActiveUnits(const FVector& CommandLocation) 
{
	ARTSHud* Hud = Cast<ARTSHud>(PlayerController->GetHUD());
	if (!Hud)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hud == nullptr"))
		return;
	}

	// TODO: Move formation point center computation onto selection complete. Redundant on every command
	FVector3d CenterPoint;
	int PointCount = 0;
	auto Units = Hud->GetSelectedUnits();
	for (const auto Unit : Units)
	{
		if (!Unit) { continue; }
		const FVector3d Location = Unit->GetActorLocation();
		CenterPoint += Location;
		PointCount++;
	}

	// TODO: Move formation mapping onto selection complete. Redundant to do on every command
	TMap<const AActor* const, FVector3d> FormationMap;
	for (const AActor* Unit : Units)
	{
		if (!Unit) { continue; }
		FVector3d OffsetFromFormationCenter = CenterPoint - Unit->GetActorLocation();
		FormationMap.Add(Unit, OffsetFromFormationCenter);
	}
	
	CenterPoint /= PointCount;

	for (AActor* Unit : Units)
	{
		if (!Unit) { continue; }
		// Offset unit's command location to retain position in formation at new location
		FVector3d UnitCommandLocation = CommandLocation + FormationMap[Unit];
		if (Unit->Implements<UCommandableInterface>())
		{
			ICommandableInterface::Execute_Command(Unit, ECommand::Move, UnitCommandLocation);
		}
	}
}

void UCommandHandler::HandleIssueActiveCommand()
{
	// TODO: Once multiple command types are implemented, use this as a switch for command delegation
	UE_LOG(LogTemp, Log, TEXT("IssueActiveCommand"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HandleIssueActiveCommand"));
}

void UCommandHandler::HandleIssueMoveCommand()
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController == null. Aborting HandleIssueMoveCommand"));
		return;
	}
	
	FHitResult Hit;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		UE_LOG(LogTemp, Log, TEXT("Spawning command reticle"));
		SpawnCommandReticle(Hit.Location);
	}
	
	MoveActiveUnits(Hit.Location);
}

// Called every frame
void UCommandHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


