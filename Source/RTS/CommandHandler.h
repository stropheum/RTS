// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommandableInterface.h"
#include "Components/ActorComponent.h"
#include "CommandHandler.generated.h"


class ADecalActor;
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EReticleType : uint8
{
	Vfx = 0		UMETA(DisplayName="VFX"),
	Decal = 1	UMETA(DisplayName="Decal"),
	Both = 2	UMETA(DisplayName="Both"),
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS_API UCommandHandler : public UActorComponent
{
	GENERATED_BODY()
	
#pragma region Methods
	
public:
	UCommandHandler();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CommandHandler")
	void HandleIssueActiveCommand();

	UFUNCTION(BlueprintCallable, Category = "CommandHandler")
	void HandleIssueMoveCommand();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnCommandReticle(const FVector3d& CommandLocation) const;
	void CachePlayerController();
	void MoveActiveUnits(const FVector3d& CommandLocation);

#pragma endregion

#pragma region Variables
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CommandHandler", meta = (AllowprivateAccess = "true"))
	EReticleType ReticleType = EReticleType::Decal;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommandHandler", meta = (AllowPrivateAccess = "true", EditCondition="ReticleType != EReticleType::Vfx", EditConditionHides))
	UNiagaraSystem* FxCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommandHandler", meta = (AllowPrivateAccess = "true", EditCondition="ReticleType != EReticleType::Decal", EditConditionHides))
	TSubclassOf<ADecalActor> CommandReticleDecal;

	APlayerController* PlayerController;

#pragma endregion
	
};
