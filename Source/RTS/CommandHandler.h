// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandHandler.generated.h"


class ADecalActor;
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS_API UCommandHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommandHandler();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "CommandHandler")
	void HandleIssueActiveCommand();
	
	UFUNCTION(BlueprintCallable, Category = "CommandHandler")
	void HandleIssueMoveCommand();
	
protected:
	virtual void BeginPlay() override;
	void SpawnCommandReticle(const FVector3d& Location) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* FxCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADecalActor> CommandReticleDecal;
	
}; 
