//ExtendEdiroAction.h

#pragma once

/** 我们会使用 TCommands 中的 Register() 函数来注册 FExtendEditorCommands 中的 FUICommandInfo，这个函数最终会调用 FExtendEditorCommands 里的 RegisterCommands()。

* 因此，我们需要在 FExtendEditorCommands 中重写 RegisterCommands()。
* 
* 其次，我们还需要在构造 FExtendEditorCommands 时指定一些信息，以方便在后续能够以一定规则查找 FExtendEditorStyle 中的样式集，为每个 FUICommandInfo 分配样式。所以我们需要自己提供 FExtendEditorCommands() 构造函数。
* 
* 然后，当然不能忘了我们的主角 FUICommandInfo，我们以清单的形式将它们罗列在类里，“PrintLog”就是我们要使用到的一个 FUICommandInfo，后续如果需要添加更多个，都在其后追加。
* 
* CommandList 为我们完成 FUICommandInfo 与要执行的 Action 的映射配对工作。这个映射可以在任意地方执行，你也可以在调用模块中来临时执行这一步操作。这里为了统一我们将其放在 FExtendEditorCommands 类中。
* 
* FExtendEditorActionCallbacks 作为 Action 的合集类来管理，我们将所有的 Action 都集中放在这个类中。
*/

/** 作用：集中管理 FUICommandInfo */
class EXTENDEDITORCOMMAND_API FExtendEditorCommands : public TCommands<FExtendEditorCommands>
{
public:
	FExtendEditorCommands();

	virtual void RegisterCommands()override;
	//static FExtendEditorCommands* Get();
public:
	//FUICommandsList 成对的映射 UICommandInfo 与其 Action
	static TSharedRef<FUICommandList>CommandList;

public:
	//UICommandInfo List
	//FUICommandInfo 存储 Command 样式信息
	TSharedPtr<FUICommandInfo>PrintLog;

private:
	static FExtendEditorCommands* ExtendEditorCommandsIns;
};

/** Action 合集类 */
class FExtendEditorActionCallbacks
{
public:
	//Action List
	static void PrintLog();
};