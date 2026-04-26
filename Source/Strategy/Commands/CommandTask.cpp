// Fill out your copyright notice in the Description page of Project Settings.

#include "Commands/CommandTask.h"
#include "CheckFieldMacros.h"

UTexture2D* UCommandTask::GetCommandIcon() const
{
    CHECK_FIELD(LogTemp, CommandIcon);
    return CommandIcon;
}

void UCommandTask::Activate()
{
    Super::Activate();

}

void UCommandTask::Finish()
{
    OnTaskFinished.Broadcast(this);
    EndTask();
}
