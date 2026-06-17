// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"

#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TimerManager.h"

AGuardAIController::AGuardAIController()
{
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

    SetPerceptionComponent(*AIPerception);                                           // AI Controller에게 이 컴포넌트가 공식 Perception임을 등록      
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));    // 시각 감각의 설정값 오브젝트 생성
    
    SightConfig->SightRadius = 800.f;          // 이 거리 안에 들어오면 감지 시작
    SightConfig->LoseSightRadius = 1200.f;     // 감지한 대상이 이 거리 밖으로 나가면 감지를 잃음
    SightConfig->PeripheralVisionAngleDegrees = 45.f;

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerception->ConfigureSense(*SightConfig);
    AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

    AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AGuardAIController::OnTargetPerceptionUpdated);
}

// Called when the game starts or when spawned
void AGuardAIController::BeginPlay()
{
    Super::BeginPlay();

    if (!BehaviorTree)
    {
        UE_LOG(LogTemp, Warning, TEXT("BehaviorTree NullPtr"));
        return;
    }

    RunBehaviorTree(BehaviorTree);
}

void AGuardAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!IsValid(Actor)) return;

    if (Stimulus.WasSuccessfullySensed())
    {
        bCanSeePlayer = true;
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Actor->GetActorLocation());
    }
    else
    {
        bCanSeePlayer = false;
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
    }
}

bool AGuardAIController::GetCanSeePlayer() const
{
    return bCanSeePlayer;
}
