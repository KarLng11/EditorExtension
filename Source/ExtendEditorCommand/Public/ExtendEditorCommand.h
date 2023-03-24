// ExtendMenuBase.h

#pragma once

#include "Modules/ModuleInterface.h"
/**在 Commands.h 中有一个 TCommands 工具类，该类提供一套方法帮助我们管理 FUICommandInfo。

什么是 FUICommandInfo 呢？可以将它看作是用于储存 Entry 样式信息的一种数据体。

FUICommandInfo 中记录了用于生成 Entry 的各种信息，包括名称、提示、图标、快捷键等等。

要分清 FUICommandInfo 与 FSlateStyleSet 的区别，FSlateStyleSet 记录的信息更像是一种装饰，而 FUICommandInfo 记录的是与 Entry 自身相关的信息
*/

class FExtendEditorCommandModule :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;

	virtual ~FExtendEditorCommandModule() {};

};