//ExtendMenuBase.cpp

#include "ExtendEditorCommand/Public/ExtendEditorCommand.h"

#include "ExtendEditorCommand/Public/ExtendEditorAction.h"

IMPLEMENT_MODULE(FExtendEditorCommandModule, ExtendEditorCommand);


void FExtendEditorCommandModule::StartupModule()
{
	IModuleInterface::StartupModule();

	FExtendEditorCommands::Register();
}

void FExtendEditorCommandModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

	FExtendEditorCommands::Unregister();
}
