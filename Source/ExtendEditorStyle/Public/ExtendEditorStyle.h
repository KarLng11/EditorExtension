// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
/*FSlateStyleSet

FSlateStyleSet ����˼����һ�����ڴ��� Slate ��ʽ����ʽ�����ݡ�

��ɢ�Ĵ�������̤�������ĸ��ĺ������������Ӷ�ġ��� FSlateStyleSet ���԰���������ͳһ�ĵط�������Щ��ʽ���ݡ�

FSlateStyleSet ��ʹ�úܼ򵥣��������ǽ�����Ϊһ��������ģ�飬���Թ��� ExtendEditor ��Ҫ�õ������е� SlateStyle��*/


class FExtendEditorStyle :public IModuleInterface
{
public:

	virtual void StartupModule()override;
	virtual void ShutdownModule()override;
	virtual ~FExtendEditorStyle(){}

private:
	inline static TSharedPtr<class FSlateStyleSet>StyleSet = nullptr;
	inline static const FName StyleSetName = FName("ExtendEditorStyle");

public:
	static EXTENDEDITORSTYLE_API FName GetStyleSetName();

private:
	void Initialize();
	TSharedRef<class FSlateStyleSet>CreateSlateStyleSet();
};
