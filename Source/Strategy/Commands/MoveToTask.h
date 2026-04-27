// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commands/CommandTask.h"
#include "MoveToTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STRATEGY_API UMoveToTask : public UCommandTask
{
	GENERATED_BODY()
	
protected:
    virtual void OnRunTask() override;
};
