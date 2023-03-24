//ExtendEdiroAction.h

#pragma once

/** ���ǻ�ʹ�� TCommands �е� Register() ������ע�� FExtendEditorCommands �е� FUICommandInfo������������ջ���� FExtendEditorCommands ��� RegisterCommands()��

* ��ˣ�������Ҫ�� FExtendEditorCommands ����д RegisterCommands()��
* 
* ��Σ����ǻ���Ҫ�ڹ��� FExtendEditorCommands ʱָ��һЩ��Ϣ���Է����ں����ܹ���һ��������� FExtendEditorStyle �е���ʽ����Ϊÿ�� FUICommandInfo ������ʽ������������Ҫ�Լ��ṩ FExtendEditorCommands() ���캯����
* 
* Ȼ�󣬵�Ȼ�����������ǵ����� FUICommandInfo���������嵥����ʽ�����������������PrintLog����������Ҫʹ�õ���һ�� FUICommandInfo�����������Ҫ��Ӹ�������������׷�ӡ�
* 
* CommandList Ϊ������� FUICommandInfo ��Ҫִ�е� Action ��ӳ����Թ��������ӳ�����������ط�ִ�У���Ҳ�����ڵ���ģ��������ʱִ����һ������������Ϊ��ͳһ���ǽ������ FExtendEditorCommands ���С�
* 
* FExtendEditorActionCallbacks ��Ϊ Action �ĺϼ������������ǽ����е� Action �����з���������С�
*/

/** ���ã����й��� FUICommandInfo */
class EXTENDEDITORCOMMAND_API FExtendEditorCommands : public TCommands<FExtendEditorCommands>
{
public:
	FExtendEditorCommands();

	virtual void RegisterCommands()override;
	//static FExtendEditorCommands* Get();
public:
	//FUICommandsList �ɶԵ�ӳ�� UICommandInfo ���� Action
	static TSharedRef<FUICommandList>CommandList;

public:
	//UICommandInfo List
	//FUICommandInfo �洢 Command ��ʽ��Ϣ
	TSharedPtr<FUICommandInfo>PrintLog;

private:
	static FExtendEditorCommands* ExtendEditorCommandsIns;
};

/** Action �ϼ��� */
class FExtendEditorActionCallbacks
{
public:
	//Action List
	static void PrintLog();
};