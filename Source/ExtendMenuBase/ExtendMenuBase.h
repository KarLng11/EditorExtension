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
	/************************** 使用 FExtender 拓展 *********************************/
	/* 用FExtend方式拓展入口函数
	* 1 创建一个FExtender对象
	* 2 将需要拓展的内容设置到该FExtender对象中
	* 3 将该FExtender对象添加到有FExtensibilityManager管理的Extenders中
	*/
	void ExtendMenuByFExtend();

	/* 在已有扩展点ExtensionHook生成一个菜单按钮*/
	void MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder);
	/* 在已有扩展点ExtensionHook生成的菜单按钮的回调事件*/
	void ExistingMainMenuEntryAction();

	/*生成一个MenuBar菜单按钮*/
	void MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder);
	/* 在新拓展点生成一个菜单按钮*/
	void MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder);
	/* 在自定义拓展点生成的菜单按钮的回调函数*/
	void NewMainMenuEntryAction();

private:

	/** FExtend 拓展 ContentBrowser的入口函数
	* 加载ContentBrowserModule模块
	* 通过GetAll***Extenders()函数获取 ContentBrowser 对应部分的Extenders
	* 注入自己的 FExtender 到 Extenders
	*/
	void ExtendContentBrowserByFExtend();

	/** 拓展资产面板上下文菜单 */
	TSharedRef<FExtender>ExtendAssetContextMenu(const TArray<FString>& SelectedPaths);
	/** 生成一个资产面板上下文菜单按钮*/
	void MakeAssetContextMenuEntry(FMenuBuilder& MenuBuilder);
	/** 新资产面板上下文菜单按钮触发事件*/
	void AssetContextMenuEntryAction();

	/** 拓展选定资产上下文菜单*/
	TSharedRef<FExtender>ExtendAssetViewContextMenu(const TArray<FAssetData>& SelectedAssets);
	/** 生成一个选定资产上下文菜单按钮*/
	void MakeAssetViewContextMenuEntry(FMenuBuilder& MenuBuilder);
	/** 新选定资产上下文菜单按钮点击触发事件*/
	void AssetViewContextMenuEntryAction();

private:
	//没结果。。。
	/** 拓展视口菜单的入口函数 */
	void ExtendViewportByFExtend();
	/** 拓展视口中的右键点击 Actor 菜单 */
	TSharedRef<FExtender>ExtendViewportSeletedActorMenu(const TSharedRef<FUICommandList>UIComandList,
		const TArray<AActor*>SelectedActors);
	/** 生成一个视口中 Actor 的菜单按钮 */
	void MakeViewportActorMenuEntry(FMenuBuilder& MenuBuilder);
	/** Actor 菜单按钮的出发事件 */
	void ViewportActorEntryAction();

	/** 使用FExtender总结
	* ContentBrowser 中的 Collection 菜单，暂时只发现了 FExtender 拓展的方式
	* 还未发现通过 FExtender 拓展 Outliner 的方法
	* 还未发现通过 FExtender 拓展 Material Editor 的方法
	*/
private:
	/******************************** 使用 UToolMenu 拓展 *****************************************/

	/**通过 UToolMenu 拓展已有菜单的基本流程
	* 1 通过 Name 持有菜单的 UToolMenu
	*    Name 的固有规律
	*     主菜单栏：LevelEditor.MainMenu.XXX
	*     ToolBar：LevelEditor.LevelEditorToolBar.XXX
	*     ContentBrowser菜单ContentBrowser.XXX
	*     蓝图编辑器：AssetEditor.BlueprintEditor.XXX
	*     材质编辑器：AssetEditor.MaterialEditor.XXX
	*     如此等等...
	* 2 通过该 UToolMenu 找到或添加 UToolMenuSection
	* 3 通过 FToolMenuSection 添加菜单项
	*/

	/** UToolMenu 拓展方式入口函数 */
	void ExtendByToolMenu();

	/** NewMenuButton2触发事件 */
	void NewMenuButton2EntryAction();

	/** 由 LevelEditorModule 管理的拓展入口 */
	void OnLevelEditorCreatedEven(TSharedPtr<class ILevelEditor>LevelEditor);

	/** UToolMenus 总结
	* 书写形式更加统一
	* 更加灵活，能够方便地拓展子编辑器和任意位置的具名菜单
	* 尚不能运用到编辑器的任何地方，例如 Outline 中的 Settings 菜单
	*/

private:
	/** Style 示例入口 */
	void StyleSample();
	void StyleButtonAction();


private:
	/** Command 示例入口 */
	void CommandSample();

private:
	/** Message 示例*/
	class UMessageClass* MessageDelegate = nullptr;

};