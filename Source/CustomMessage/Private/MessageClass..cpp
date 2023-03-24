#include "MessageClass.h"

#include "LevelEditorViewport.h"
#include "Engine/ViewportStatsSubsystem.h"

bool UMessageClass::MessageCallback(FText& OutText, FLinearColor& OutColor)
{
	OutText = Text;
	OutColor = Color;
	return bShouldDisplay;
}

void UMessageClass::SetMessage(FText InText, FLinearColor InColor)
{
	Text = InText;
	Color = InColor;
}

void UMessageClass::ToggleDisplay()
{
	bShouldDisplay = !bShouldDisplay;
}

void UMessageClass::BindToViewportStatsSubsystem()
{
	if (UViewportStatsSubsystem* ViewportStatsSubsystem =
		GEditor->GetLevelViewportClients()[0]->GetWorld()->GetSubsystem<UViewportStatsSubsystem>())
	{
		FViewportDisplayCallback ViewportDisplayCallback;

		ViewportDisplayCallback.BindDynamic(this, &UMessageClass::MessageCallback);
		ViewportStatsSubsystem->AddDisplayDelegate(ViewportDisplayCallback);
	}

	bIsBind = true;
	}

bool UMessageClass::IsBind()
{
	return bIsBind;
}
