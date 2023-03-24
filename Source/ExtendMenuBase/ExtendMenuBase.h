// ExtendMenuBase.h

#pragma once

#include "Modules/ModuleInterface.h"

class FExtendMenuBase :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;

	virtual ~FExtendMenuBase() {};
private:
	/************************** ʹ�� FExtender ��չ *********************************/
	/* ��FExtend��ʽ��չ��ں���
	* 1 ����һ��FExtender����
	* 2 ����Ҫ��չ���������õ���FExtender������
	* 3 ����FExtender������ӵ���FExtensibilityManager�����Extenders��
	*/
	void ExtendMenuByFExtend();

	/* ��������չ��ExtensionHook����һ���˵���ť*/
	void MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder);
	/* ��������չ��ExtensionHook���ɵĲ˵���ť�Ļص��¼�*/
	void ExistingMainMenuEntryAction();

	/*����һ��MenuBar�˵���ť*/
	void MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder);
	/* ������չ������һ���˵���ť*/
	void MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder);
	/* ���Զ�����չ�����ɵĲ˵���ť�Ļص�����*/
	void NewMainMenuEntryAction();

private:

	/** FExtend ��չ ContentBrowser����ں���
	* ����ContentBrowserModuleģ��
	* ͨ��GetAll***Extenders()������ȡ ContentBrowser ��Ӧ���ֵ�Extenders
	* ע���Լ��� FExtender �� Extenders
	*/
	void ExtendContentBrowserByFExtend();

	/** ��չ�ʲ���������Ĳ˵� */
	TSharedRef<FExtender>ExtendAssetContextMenu(const TArray<FString>& SelectedPaths);
	/** ����һ���ʲ���������Ĳ˵���ť*/
	void MakeAssetContextMenuEntry(FMenuBuilder& MenuBuilder);
	/** ���ʲ���������Ĳ˵���ť�����¼�*/
	void AssetContextMenuEntryAction();

	/** ��չѡ���ʲ������Ĳ˵�*/
	TSharedRef<FExtender>ExtendAssetViewContextMenu(const TArray<FAssetData>& SelectedAssets);
	/** ����һ��ѡ���ʲ������Ĳ˵���ť*/
	void MakeAssetViewContextMenuEntry(FMenuBuilder& MenuBuilder);
	/** ��ѡ���ʲ������Ĳ˵���ť��������¼�*/
	void AssetViewContextMenuEntryAction();

private:
	//û���������
	/** ��չ�ӿڲ˵�����ں��� */
	void ExtendViewportByFExtend();
	/** ��չ�ӿ��е��Ҽ���� Actor �˵� */
	TSharedRef<FExtender>ExtendViewportSeletedActorMenu(const TSharedRef<FUICommandList>UIComandList,
		const TArray<AActor*>SelectedActors);
	/** ����һ���ӿ��� Actor �Ĳ˵���ť */
	void MakeViewportActorMenuEntry(FMenuBuilder& MenuBuilder);
	/** Actor �˵���ť�ĳ����¼� */
	void ViewportActorEntryAction();

	/** ʹ��FExtender�ܽ�
	* ContentBrowser �е� Collection �˵�����ʱֻ������ FExtender ��չ�ķ�ʽ
	* ��δ����ͨ�� FExtender ��չ Outliner �ķ���
	* ��δ����ͨ�� FExtender ��չ Material Editor �ķ���
	*/
private:
	/******************************** ʹ�� UToolMenu ��չ *****************************************/

	/**ͨ�� UToolMenu ��չ���в˵��Ļ�������
	* 1 ͨ�� Name ���в˵��� UToolMenu
	*    Name �Ĺ��й���
	*     ���˵�����LevelEditor.MainMenu.XXX
	*     ToolBar��LevelEditor.LevelEditorToolBar.XXX
	*     ContentBrowser�˵�ContentBrowser.XXX
	*     ��ͼ�༭����AssetEditor.BlueprintEditor.XXX
	*     ���ʱ༭����AssetEditor.MaterialEditor.XXX
	*     ��˵ȵ�...
	* 2 ͨ���� UToolMenu �ҵ������ UToolMenuSection
	* 3 ͨ�� FToolMenuSection ��Ӳ˵���
	*/

	/** UToolMenu ��չ��ʽ��ں��� */
	void ExtendByToolMenu();

	/** NewMenuButton2�����¼� */
	void NewMenuButton2EntryAction();

	/** �� LevelEditorModule �������չ��� */
	void OnLevelEditorCreatedEven(TSharedPtr<class ILevelEditor>LevelEditor);

	/** UToolMenus �ܽ�
	* ��д��ʽ����ͳһ
	* �������ܹ��������չ�ӱ༭��������λ�õľ����˵�
	* �в������õ��༭�����κεط������� Outline �е� Settings �˵�
	*/

private:
	/** Style ʾ����� */
	void StyleSample();
	void StyleButtonAction();


private:
	/** Command ʾ����� */
	void CommandSample();

private:
	/** Message ʾ��*/
	class UMessageClass* MessageDelegate = nullptr;

};