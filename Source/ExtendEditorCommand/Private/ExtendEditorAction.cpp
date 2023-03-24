#include "ExtendEditorCommand/Public/ExtendEditorAction.h"

#include "ExtendEditorStyle.h"


#define LOCTEXT_NAMESPACE "FExtendEditorCommands"

TSharedRef<FUICommandList>FExtendEditorCommands::CommandList = MakeShareable(new FUICommandList());

FExtendEditorCommands::FExtendEditorCommands() :TCommands<FExtendEditorCommands>(
	"ExtendEditorCommands",//����������
	LOCTEXT("Extend Editor Commands", "Extend Editor Commands"),
	NAME_None,
	FExtendEditorStyle::GetStyleSetName()//��ʽ������
	)
{
}

void FExtendEditorCommands::RegisterCommands()
{
	// ���úͰ� FUICommandInfo
	{
		// ע�� FUICommandInfo
		UI_COMMAND(PrintLog, "Print Log Label", "Print Log ToolTip",
			EUserInterfaceActionType::Button, FInputChord());

		//��ͬ������
		//FUICommandInfo::MakeCommandInfo(this->AsShared(),UICommandInfo_MenuEntry2,...);

		//�� FUICommandInfo ���� Action �� ActionList
		CommandList->MapAction(
			PrintLog,
			FExecuteAction::CreateStatic(&FExtendEditorActionCallbacks::PrintLog)
		);
	}

	//�������úͰ� FUICommandInfo
	{
		//...
	}
}
FExtendEditorCommands* FExtendEditorCommands::ExtendEditorCommandsIns = nullptr;

//FExtendEditorCommands* FExtendEditorCommands::Get()
//{
//	if (!ExtendEditorCommandsIns)
//	{
//		ExtendEditorCommandsIns = new FExtendEditorCommands();
//	}
//	return ExtendEditorCommandsIns;
//}
#undef LOCTEXT_NAMESPACE

void FExtendEditorActionCallbacks::PrintLog()
{
	UE_LOG(LogTemp, Warning, TEXT("StyleButtonAction is called!"));
}
