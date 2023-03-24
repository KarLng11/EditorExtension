// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
/*FSlateStyleSet

FSlateStyleSet 顾名思义是一种用于储存 Slate 样式的样式集数据。

林散的代码就像脚踏几条船的负心汉，总是让人嫌恶的。而 FSlateStyleSet 可以帮助我们在统一的地方管理这些样式数据。

FSlateStyleSet 的使用很简单，这里我们将其作为一个独立的模块，用以管理 ExtendEditor 中要用到的所有的 SlateStyle。*/


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
