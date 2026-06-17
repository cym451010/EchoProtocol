#include "BTService_UpdatePlayerLocation.h"
#include "EchoPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
    NodeName = TEXT("Update Player Location");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AEchoPlayerCharacter* Player = Cast<AEchoPlayerCharacter>(UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(), 0));
    if (!Player) return;

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent) return;

    BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
    BlackboardComponent->SetValueAsVector(TEXT("LastKnownLocation"), Player->GetActorLocation());
}