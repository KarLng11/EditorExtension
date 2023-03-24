//ExtendMenuBase.cpp

#include "ExtendMenuBase.h"

#include "LevelEditor.h"
#include "ContentBrowserModule.h"

#include "ToolMenus.h"

#include "ExtendEditorStyle/Public/ExtendEditorStyle.h"

#include "ExtendEditorCommand/Public/ExtendEditorCommand.h"
#include "ExtendEditorCommand/Public/ExtendEditorAction.h"

#include "CustomMessage/Public/MessageClass.h"

IMPLEMENT_GAME_MODULE(FExtendMenuBase, ExtendMenuBase);

void FExtendMenuBase::StartupModule()
{
	IModuleInterface::StartupModule();

	ExtendMenuByFExtend();

	ExtendContentBrowserByFExtend();

	ExtendViewportByFExtend();


	//ExtendByToolMenu();
	/** 由 LevelEditor 管理拓展的入口*/
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.OnLevelEditorCreated().AddRaw(this, &FExtendMenuBase::OnLevelEditorCreatedEven);


	/** 在 ToolBar 上添加一个按钮，并应用于自己的 Icon */
	StyleSample();


	//通过 UToolMenus 配置 Entry 时，由于没有要求指定 CommandList 的地方，此时配置完毕的 Entry 是不具备 Action 功能的。需要在之后单独为生成的 Entry 指定 CommandList
	/** 确保 FExtendEditorCommandModule 已加载*/
	FModuleManager::LoadModuleChecked<FExtendEditorCommandModule>("ExtendEditorCommand");
	CommandSample();
}

void FExtendMenuBase::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

void FExtendMenuBase::ExtendMenuByFExtend()
{
	//新建FExtender
	TSharedPtr<FExtender>MainMenuExtender = MakeShareable(new FExtender());

	//设置FExtender

	/* FExtender可以添加的扩展为
	* AddMenuExtension 主菜单按钮的子按钮
	* AddMenuBarExtension 主菜单按钮
	* AddToolBarExtension ToolBar上的按钮
	*/
	MainMenuExtender->AddMenuExtension(
		"EpicGamesHelp",                           //用于定位ExtensionHook的名称
		EExtensionHook::After,                     //添加的具体位置(该Hook之前还是之后
		nullptr,                                   // CommandList 暂时缺省
		FMenuExtensionDelegate::CreateRaw(         //绑定制作按钮的代理函数
			this, &FExtendMenuBase::MakeExistingMainMenuEntry)
	);

	MainMenuExtender->AddMenuBarExtension(
		"Help", //用于定位ExtensionHook(MenuButton)的名称
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMenuBarEntry)
	);


	//添加新建的FExtender到ExtensibilityManager
	//创建通用的拓展管理器
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//创建主菜单的函数
	/*auto MenuExtenders = LevelEditorModule.GetAllLevelEditorLevelMenuExtenders();
	MenuExtenders.Add(...);*/
	TSharedPtr<FExtensibilityManager>ExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();

	ExtensibilityManager->AddExtender(MainMenuExtender);
}

void FExtendMenuBase::MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	/*FMenuBuilder可以Add的内容：
	* AddMenuEntry 添加普通按钮
	* AddWidget 添加Widget
	* AddSeparator 添加分割线
	* AddMenuSeparator
	* AddSearchWidget
	* AddSubMenu
	* AddWrapperSubMenu
	* AddEditableText
	*/
	MenuBuilder.AddMenuEntry(
		FText::FromString("Existing Hook Extension"),        //按钮的显示名称
		FText::FromString("This is a existing hook extend"), //按钮提示
		FSlateIcon(),                                        //为按钮添加图标 这里暂时缺省
		FUIAction(FExecuteAction::CreateRaw                  //绑定执行按钮的回调函数
		(
			this, &FExtendMenuBase::ExistingMainMenuEntryAction
		))
	);
}

void FExtendMenuBase::ExistingMainMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("ExistingMainMenuEntryAction is called!"));
}

void FExtendMenuBase::MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
	/*FMenuBarBuilder可Add的内容有
	* EditableText
	* MenuEntry
	* PullDownMenu
	* VerifiedEditableText
	*/
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("New Menu"),//添加下拉菜单按钮
		FText::FromString("This is a new menu bar button!"),
		FNewMenuDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMainMenuEntry),//创建Menu按钮的执行函数
		"New Main Hook"//该按钮的ExtensionHook
	);
}

void FExtendMenuBase::MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Section 1", FText::FromString("Section 1"));//设置Section

	MenuBuilder.AddMenuEntry(
		FText::FromString("New Menu Button"),
		FText::FromString("This is new menu button!"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::NewMainMenuEntryAction))
	);

	MenuBuilder.AddSeparator();

	MenuBuilder.AddMenuEntry(
		FText::FromString("New Menu Button2"),
		FText::FromString("This is new menu button2!"),
		FSlateIcon(),
		FUIAction()
	);

	MenuBuilder.EndSection();//结束Section设置
}

void FExtendMenuBase::NewMainMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is called!"), *__FUNCTION__);
}

void FExtendMenuBase::ExtendContentBrowserByFExtend()
{
	/** 获取ContentBrowserModule*/
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().GetModuleChecked<FContentBrowserModule>("ContentBrowser");

	/** 通过GetAllAssetContextMenuExtenders() 获取Extenders*/
	TArray<FContentBrowserMenuExtender_SelectedPaths>& Extenders = ContentBrowserModule.GetAllAssetContextMenuExtenders();
	/** 需注意此处添加的委托应于 Extenders 中的对应*/
	Extenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FExtendMenuBase::ExtendAssetContextMenu));

	// 通过AssetViewContextMenuExtender拓展选定资产上下文菜单
	TArray<FContentBrowserMenuExtender_SelectedAssets>& Extenders2 = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	Extenders2.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FExtendMenuBase::ExtendAssetViewContextMenu));
}

TSharedRef<FExtender> FExtendMenuBase::ExtendAssetContextMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender>MenuExtender(new FExtender());
	if (SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(
			"ContentBrowserGetContent",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeAssetContextMenuEntry)
		);
	}
	return MenuExtender;
}

void FExtendMenuBase::MakeAssetContextMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Asset Content Menu Button"),
		FText::FromString("This is a asset context button!"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::AssetContextMenuEntryAction))
	);
}

void FExtendMenuBase::AssetContextMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetContextMenuEntryAction is called!"));
}

TSharedRef<FExtender> FExtendMenuBase::ExtendAssetViewContextMenu(const TArray<FAssetData>& SelectedAssets)
{
	TSharedRef<FExtender>MenuExtender(new FExtender());
	if (SelectedAssets.Num() > 0)
	{
		MenuExtender->AddMenuExtension(
			"GetAssetActions",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeAssetViewContextMenuEntry)
		);
	}
	return MenuExtender;
}

void FExtendMenuBase::MakeAssetViewContextMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Section 1", FText::FromString("Section 1"));

	MenuBuilder.AddMenuEntry(
		FText::FromString("Asset View Context Menu Button"),
		FText::FromString("This is a asset view context menu button!"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::AssetViewContextMenuEntryAction))
	);

	MenuBuilder.EndSection();
}

void FExtendMenuBase::AssetViewContextMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetViewContextMenuEntryAction is called!"));
}

void FExtendMenuBase::ExtendViewportByFExtend()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");

	/** Level 场景中选中 Actor 的右键菜单 */
	LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	/** 视口选项菜单，点击视口右上角小齿轮时弹出的菜单 */
	LevelEditorModule.GetAllLevelViewportOptionsMenuExtenders();
	/** 视口视图菜单。点击视口右上角小眼睛时弹出的菜单 */
	LevelEditorModule.GetAllLevelViewportShowMenuExtenders();
	/** 按住右键并拖拽 Object 到视口中松开时弹出的菜单 */
	LevelEditorModule.GetAllLevelViewportDragDropContextMenuExtenders();

	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors>LevelViewportContextMenuExtenders =
		LevelEditorModule.GetAllLevelViewportContextMenuExtenders();

	LevelViewportContextMenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FExtendMenuBase::ExtendViewportSeletedActorMenu));
}
TSharedRef<FExtender> FExtendMenuBase::ExtendViewportSeletedActorMenu(const TSharedRef<FUICommandList> UIComandList, const TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender>ViewportSelectedActorMenu(new FExtender());

	if (SelectedActors.Num() > 0)
	{
		ViewportSelectedActorMenu->AddMenuExtension(
			"View Options",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeViewportActorMenuEntry)
		);
	}
	return ViewportSelectedActorMenu;
}

void FExtendMenuBase::MakeViewportActorMenuEntry(FMenuBuilder& MenuBuilder)
{
	//MenuBuilder.BeginSection("Section of mine");
	MenuBuilder.AddMenuEntry(
		FText::FromString("Viewport Actor Menu Button"),
		FText::FromString("This is a viewport actor menu button!"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::ViewportActorEntryAction))
	);
	//MenuBuilder.AddSubMenu()
	//MenuBuilder.AddSeparator();
	//MenuBuilder.EndSection();
}

void FExtendMenuBase::ViewportActorEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Viewport Actor Entry Action is called!"));
}


#define LOCTEXT_NAMESPACE "ExtendByToolMenu"
void FExtendMenuBase::ExtendByToolMenu()
{
	// 持有 LevelEditor.MainMenu
	//UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");

	//现在的调用时机为 OnLevelEditorCreated 可用 FindMenu
	UToolMenu* ToolMenu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu");

	//定位 LevelEditor.MainMenu 中的 Section
	 //LevelEditor.MainMenu 中没有 Section 所以传入 Name_None
	FToolMenuSection& Section = ToolMenu->FindOrAddSection(NAME_None);

	//制作子菜单 Entry
	FToolMenuEntry& Entry = Section.AddSubMenu(
		"NewMenuByToolMenu",//新子菜单 Name
		LOCTEXT("NewMenu2", "New Menu 2"),//标签
		LOCTEXT("NewMenu2_ToolTip", "This is a extended menu by tool menu!"),
		FNewToolMenuChoice()    //做些奇怪的事
	);

	//设置 Entry 出现的位置
	Entry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);

	//LevelEditor.MainMenu.NewMenuByUToolMenus 注册为菜单
	static const FName BaseMenuName = "LevelEditor.MainMenu.NewMenuByToolMenu";
	ToolMenu = UToolMenus::Get()->RegisterMenu(BaseMenuName);

	//在新菜单下添加 Section 和 Entry
	FToolMenuSection& NewSection = ToolMenu->AddSection("New Section", FText::FromString("New Section"));
	NewSection.AddMenuEntry(
		"New Menu 2 Button",
		FText::FromString("Lable:New Menu 2 Button"),
		FText::FromString("This is a new 2 button by UToolMenus!"),
		FSlateIcon(),
		FToolUIActionChoice(FExecuteAction::CreateRaw(this, &FExtendMenuBase::NewMenuButton2EntryAction))
	);

	NewSection.AddSeparator("MySeparator");

	FToolMenuEntry MyToolMenuEntry = NewSection.AddSubMenu(
		"NewMySubMenu",
		LOCTEXT("MySubMenu1", "My Sub Menu 1"),
		LOCTEXT("MySubMenu1_ToolTip", "This is my sub menu1 by tool menu!"),
		FNewToolMenuChoice()
	);

	//MyToolMenuEntry.AddOptionsDropdown(

	//);
	UToolMenu* ToolMenu3 = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.NewMenuByToolMenu");
	if (ToolMenu3)
	{
		FToolMenuSection& Section3 = ToolMenu3->FindOrAddSection(NAME_None);

		Section3.AddMenuEntry(
			"New Sub Menu Button",
			FText::FromString("Label : New Sub Menu Button"),
			FText::FromString("This is a new sub button!"),
			FSlateIcon(),
			FUIAction()
		);
	}
	//#define LOCTEXT_NAMESPACE "MainMenu"

	const FName MainMenuName("MainFrame.MainMenu");
	UToolMenu* MenuBar = UToolMenus::Get()->FindMenu(MainMenuName);
	if (MenuBar)
	{
		MenuBar->AddSubMenu(
			"MainMenu",
			NAME_None,
			"Cherry",
			LOCTEXT("CustomMenu", "Cherry"),
			LOCTEXT("CustomMenu_ToolTip", "Open the custom menu")
		);

		UToolMenu* Menu = UToolMenus::Get()->RegisterMenu("LevelEditor.MainMenu.Cherry", "MainFrame.MainMenu.Cherry");
		FToolMenuSection& Section2 = Menu->AddSection("Cherry_Section1", LOCTEXT("CherrySeciton1", "CherrySeciton1"));
		Section2.AddMenuEntry(
			"New Menu 3 Button",
			FText::FromString("Lable:New Menu 3 Button"),
			FText::FromString("This is a new 3 button by UToolMenus!"),
			FSlateIcon(FExtendEditorStyle::GetStyleSetName(), "AliceTool"),
			FToolUIActionChoice(FExecuteAction::CreateLambda([]() {UE_LOG(LogTemp, Warning, TEXT("This is new button 3 clicked event!"))}))
		);
	}



}
//#undef LOCTEXT_NAMESPACE

void FExtendMenuBase::NewMenuButton2EntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("NewMenuButton2EntryAction is called!"));
}
void FExtendMenuBase::OnLevelEditorCreatedEven(TSharedPtr<class ILevelEditor> LevelEditor)
{
	ExtendByToolMenu();
}

#undef LOCTEXT_NAMESPACE

void FExtendMenuBase::StyleSample()
{
	UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");

	FToolMenuSection& Section = ToolMenu->FindOrAddSection(NAME_None);
	Section.AddEntry(FToolMenuEntry::InitToolBarButton
	(//添加一个 ToolBar 按钮
		"Style Button",
		FToolUIActionChoice(FExecuteAction::CreateRaw(this, &FExtendMenuBase::StyleButtonAction)),
		FText::FromString("Lable:Style Button"),
		FText::FromString("This is a style button by style sample!"),
		FSlateIcon(FExtendEditorStyle::GetStyleSetName(), "AliceTool"//使用自己注册时 SlateStyleSet 设置 SlateIcon 样式
		)));
}
void FExtendMenuBase::StyleButtonAction()
{
	UE_LOG(LogTemp, Warning, TEXT("StyleButtonAction is called!"));

	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Red, FString("This is a gengine debug message!"));

	if (!MessageDelegate)
	{
		MessageDelegate = NewObject<UMessageClass>();

		MessageDelegate->AddToRoot();
		MessageDelegate->SetMessage(
			FText::FromString("This is a Bound Message!"), FLinearColor::White
		);

		if (!MessageDelegate->IsBind())
		{
			MessageDelegate->BindToViewportStatsSubsystem();
		}
	}

	MessageDelegate->ToggleDisplay();
}

void FExtendMenuBase::CommandSample()
{
	UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");

	FToolMenuSection& Section = ToolMenu->FindOrAddSection(NAME_None);

	//使用 Command 方式生成 ToolBarEntry
	FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(FExtendEditorCommands::Get().PrintLog);
	//为 ToolBar 配置 CommandList
	ToolMenuEntry.SetCommandList(FExtendEditorCommands::Get().CommandList);
	//将配置好的 ToolMenuEntry 添加到指定位置
	Section.AddEntry(ToolMenuEntry);
}
