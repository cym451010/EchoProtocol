// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AGuardAIController::AGuardAIController()
{
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

    SetPerceptionComponent(*AIPerception);                                           // AI Controller에게 이 컴포넌트가 공식 Perception임을 등록      
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));    // 시각 감각의 설정값 오브젝트 생성
    
    SightConfig->SightRadius = 800.f;          // 이 거리 안에 들어오면 감지 시작
    SightConfig->LoseSightRadius = 1200.f;     // 감지한 대상이 이 거리 밖으로 나가면 감지를 잃음

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerception->ConfigureSense(*SightConfig);                          // 시각 설정을 Perception 컴포넌트에 등록
    AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());  // 여러 감각 중 주된 감각을 시각으로 지정

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

    BlackboardComponent = GetBlackboardComponent();
}

void AGuardAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!BlackboardComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent NullPtr"));

        return;
    }
    

    if (Stimulus.WasSuccessfullySensed())
    {
        BlackboardComponent->SetValueAsBool(TEXT("bCanSeePlayer"), true);
        UE_LOG(LogTemp, Warning, TEXT("bCanSeePlayer True"));
    }
    else
    {
        BlackboardComponent->SetValueAsBool(TEXT("bCanSeePlayer"), false);
        BlackboardComponent->SetValueAsBool(TEXT("bCanChase"), false);
        UE_LOG(LogTemp, Warning, TEXT("bCanSeePlayer False"));

    }

    //TODO : BT 구현하기
}
