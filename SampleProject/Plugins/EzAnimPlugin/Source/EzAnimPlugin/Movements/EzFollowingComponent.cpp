#include "EzAnimPlugin.h"
#include "EzFollowingComponent.h"

UEzFollowingComponent::UEzFollowingComponent() :
    targetType(EzMovementTarget::EZMT_Actor),
    playerIndex(0),
    target(nullptr),
    distance(0,0,0) {

    PrimaryComponentTick.TickGroup = ETickingGroup::TG_PostUpdateWork;
	PrimaryComponentTick.bCanEverTick = true;
}

void UEzFollowingComponent::BeginPlay() {
	Super::BeginPlay();

}

void UEzFollowingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector targetLocation;
    
    if (targetType == EzMovementTarget::EZMT_Actor) {
        if (IsValid(target))
            targetLocation = target->GetActorLocation();
    }
    else if (targetType == EzMovementTarget::EZMT_PlayerCamera) {
        auto camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), playerIndex);
        if (IsValid(camManager))
            targetLocation = camManager->GetCameraLocation();
    }
    else if (targetType == EzMovementTarget::EZMT_PlayerPawn) {
        auto pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), playerIndex);
        if (IsValid(pawn))
            targetLocation = pawn->GetActorLocation();
    }
    
    GetOwner()->SetActorLocation(targetLocation + distance);
}

#if WITH_EDITOR
bool UEzFollowingComponent::CanEditChange(const UProperty* prop) const {
    auto name = prop->GetFName();

    if (name == GET_MEMBER_NAME_CHECKED(UEzFollowingComponent, playerIndex)) {
        return
            targetType == EzMovementTarget::EZMT_PlayerCamera ||
            targetType == EzMovementTarget::EZMT_PlayerPawn;
    }
    else if (name == GET_MEMBER_NAME_CHECKED(UEzFollowingComponent, target))
        return targetType == EzMovementTarget::EZMT_Actor;

    return Super::CanEditChange(prop);
}
#endif