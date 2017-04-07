#pragma once

#include "Components/ActorComponent.h"

#include "EzEase.h"
#include "EzPeriodicAnimationComponent.h"

#include "EzEaseAnimationComponent.generated.h"

class UEzAnimationFunctionLibrary;

UCLASS( ClassGroup=(Custom) )
class EZANIMPLUGIN_API UEzEaseAnimationComponent : public UEzPeriodicAnimationComponent
{
friend UEzAnimationFunctionLibrary;
	GENERATED_BODY()

public:	
	UEzEaseAnimationComponent();

protected:
	virtual void BeginPlay() override;

	void SetStartAndEndValue(float start, float end);
	inline float GetEaseValue() const;

private:
	// �̸� ������ ���� BeginPlay���� ��������°� �����Ѵ�.
	void FreezeStartValue();

private:
	UPROPERTY(EditAnywhere, Category = "EzAnim_Easing")
	bool useCurve;

	UPROPERTY(EditAnywhere, Category = "EzAnim_Easing", meta = (EditCondition = "useCurve"))
	UCurveFloat *curve;

	UPROPERTY(EditAnywhere, Category = "EzAnim_Easing", meta = (EditCondition = "!useCurve"))
	TEnumAsByte<EzEaseType> easeType;
	
	float startValue, deltaValue;

	bool frozen;
};
