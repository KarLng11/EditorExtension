#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MessageClass.generated.h"

UCLASS()
class CUSTOMMESSAGE_API UMessageClass :public UObject
{
	GENERATED_BODY()

public:

	/** ���� UViewportStatsSubsystem �Ļص����� */
	UFUNCTION()
		bool MessageCallback(FText&OutText,FLinearColor&OutColor);

	/** ������ʾ���� */
	void SetMessage(FText InText, FLinearColor InColor);

	/** �򿪻��߹ر���Ϣ��ʾ */
	void ToggleDisplay();

	/** ���� MessageCallback �󶨵� ViewportStatsSubsystem */
	void BindToViewportStatsSubsystem();

	/** ��ѯ��״̬ */
	bool IsBind();

private:

	FText Text = FText();
	FLinearColor Color = FLinearColor();

	bool bShouldDisplay = false;

	bool bIsBind = false;
};