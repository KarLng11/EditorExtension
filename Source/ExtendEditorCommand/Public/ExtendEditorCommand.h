// ExtendMenuBase.h

#pragma once

#include "Modules/ModuleInterface.h"
/**�� Commands.h ����һ�� TCommands �����࣬�����ṩһ�׷����������ǹ��� FUICommandInfo��

ʲô�� FUICommandInfo �أ����Խ������������ڴ��� Entry ��ʽ��Ϣ��һ�������塣

FUICommandInfo �м�¼���������� Entry �ĸ�����Ϣ���������ơ���ʾ��ͼ�ꡢ��ݼ��ȵȡ�

Ҫ���� FUICommandInfo �� FSlateStyleSet ������FSlateStyleSet ��¼����Ϣ������һ��װ�Σ��� FUICommandInfo ��¼������ Entry ������ص���Ϣ
*/

class FExtendEditorCommandModule :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;

	virtual ~FExtendEditorCommandModule() {};

};