// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExtendEditorStyle/Public/ExtendEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

IMPLEMENT_MODULE(FExtendEditorStyle, ExtendEditorStyle)

#define REGISTER_SLATESTYLE(IconName,SlateStyleName)\
	const FVector2D IconSize(16.f, 16.f);\
FSlateImageBrush* SlateImageBrush = new FSlateImageBrush(RootPath + TEXT(#IconName), IconSize);\
SlateStyleSet->Set(#SlateStyleName, SlateImageBrush);

void FExtendEditorStyle::StartupModule()
{
	Initialize();
}

void FExtendEditorStyle::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	StyleSet.Reset();
}

FName FExtendEditorStyle::GetStyleSetName()
{
	return StyleSetName;
}

void FExtendEditorStyle::Initialize()
{
	if (!StyleSet.IsValid())
	{
		StyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}
}

TSharedRef<class FSlateStyleSet> FExtendEditorStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet>SlateStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	const FString RootPath = FPaths::ProjectDir() + TEXT("/Resource/");
	SlateStyleSet->SetContentRoot(RootPath);

	//Ìí¼Ó Style
	{
		/*const FVector2D IconSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = new FSlateImageBrush(RootPath + TEXT("AliceIcon.png"), IconSize);

		SlateStyleSet->Set("AliceTool", SlateImageBrush);*/

		REGISTER_SLATESTYLE(AliceIcon.png, AliceTool);
	}

	//Ìí¼Ó ExtendEditorCommands Style
	{
		/*const FVector2D IconSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush =
			new FSlateImageBrush(RootPath + TEXT("AliceIcon.png"), IconSize);

		SlateStyleSet->Set("ExtendEditorCommands.PrintLog", SlateImageBrush);*/

		REGISTER_SLATESTYLE(AliceIcon.png, ExtendEditorCommands.PrintLog);
	}
	return SlateStyleSet;
}
