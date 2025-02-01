// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommandableInterface.generated.h"

UENUM(BlueprintType)
enum class ECommand : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Move = 1 UMETA(DisplayName = "Move"),
};


UINTERFACE()
class UCommandableInterface : public UInterface
{
	GENERATED_BODY()
};

class RTS_API ICommandableInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ICommandable")
	void Command(ECommand Command, const FVector& Location);

};
