// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToTask.h"
#include "Tasks/AITask_MoveTo.h"
#include "AIController.h"

void UMoveToTask::OnRunTask()
{
    Super::OnRunTask();

    UAITask_MoveTo* MoveTask = UAITask_MoveTo::AIMoveTo(AIController, TargetLocation, TargetActor, -1.f,
        EAIOptionFlag::Default, EAIOptionFlag::Default, true, false, false);

    if (!MoveTask)
    {
        FinishTask();
        return;
    }

    MoveTask->OnMoveTaskFinished.AddLambda([this](EPathFollowingResult::Type, AAIController*) { FinishTask(); });
}
