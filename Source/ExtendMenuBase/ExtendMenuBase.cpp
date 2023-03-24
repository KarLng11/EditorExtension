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
	/** �� LevelEditor ������չ�����*/
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.OnLevelEditorCreated().AddRaw(this, &FExtendMenuBase::OnLevelEditorCreatedEven);


	/** �� ToolBar �����һ����ť����Ӧ�����Լ��� Icon */
	StyleSample();


	//ͨ�� UToolMenus ���� Entry ʱ������û��Ҫ��ָ�� CommandList �ĵط�����ʱ������ϵ� Entry �ǲ��߱� Action ���ܵġ���Ҫ��֮�󵥶�Ϊ���ɵ� Entry ָ�� CommandList
	/** ȷ�� FExtendEditorCommandModule �Ѽ���*/
	FModuleManager::LoadModuleChecked<FExtendEditorCommandModule>("ExtendEditorCommand");
	CommandSample();
}

void FExtendMenuBase::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

void FExtendMenuBase::ExtendMenuByFExtend()
{
	//�½�FExtender
	TSharedPtr<FExtender>MainMenuExtender = MakeShareable(new FExtender());

	//����FExtender

	/* FExtender������ӵ���չΪ
	* AddMenuExtension ���˵���ť���Ӱ�ť
	* AddMenuBarExtension ���˵���ť
	* AddToolBarExtension ToolBar�ϵİ�ť
	*/
	MainMenuExtender->AddMenuExtension(
		"EpicGamesHelp",                           //���ڶ�λExtensionHook������
		EExtensionHook::After,                     //��ӵľ���λ��(��Hook֮ǰ����֮��
		nullptr,                                   // CommandList ��ʱȱʡ
		FMenuExtensionDelegate::CreateRaw(         //��������ť�Ĵ�����
			this, &FExtendMenuBase::MakeExistingMainMenuEntry)
	);

	MainMenuExtender->AddMenuBarExtension(
		"Help", //���ڶ�λExtensionHook(MenuButton)������
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMenuBarEntry)
	);


	//����½���FExtender��ExtensibilityManager
	//����ͨ�õ���չ������
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//�������˵��ĺ���
	/*auto MenuExtenders = LevelEditorModule.GetAllLevelEditorLevelMenuExtenders();
	MenuExtenders.Add(...);*/
	TSharedPtr<FExtensibilityManager>ExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();

	ExtensibilityManager->AddExtender(MainMenuExtender);
}

void FExtendMenuBase::MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	/*FMenuBuilder����Add�����ݣ�
	* AddMenuEntry �����ͨ��ť
	* AddWidget ���Widget
	* AddSeparator ��ӷָ���
	* AddMenuSeparator
	* AddSearchWidget
	* AddSubMenu
	* AddWrapperSubMenu
	* AddEditableText
	*/
	MenuBuilder.AddMenuEntry(
		FText::FromString("Existing Hook Extension"),        //��ť����ʾ����
		FText::FromString("This is a existing hook extend"), //��ť��ʾ
		FSlateIcon(),                                        //Ϊ��ť���ͼ�� ������ʱȱʡ
		FUIAction(FExecuteAction::CreateRaw                  //��ִ�а�ť�Ļص�����
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
	/*FMenuBarBuilder��Add��������
	* EditableText
	* MenuEntry
	* PullDownMenu
	* VerifiedEditableText
	*/
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("New Menu"),//��������˵���ť
		FText::FromString("This is a new menu bar button!"),
		FNewMenuDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMainMenuEntry),//����Menu��ť��ִ�к���
		"New Main Hook"//�ð�ť��ExtensionHook
	);
}

void FExtendMenuBase::MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Section 1", FText::FromString("Section 1"));//����Section

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

	MenuBuilder.EndSection();//����Section����
}

void FExtendMenuBase::NewMainMenuEntryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is called!"), *__FUNCTION__);
}

void FExtendMenuBase::ExtendContentBrowserByFExtend()
{
	/** ��ȡContentBrowserModule*/
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().GetModuleChecked<FContentBrowserModule>("ContentBrowser");

	/** ͨ��GetAllAssetContextMenuExtenders() ��ȡExtenders*/
	TArray<FContentBrowserMenuExtender_SelectedPaths>& Extenders = ContentBrowserModule.GetAllAssetContextMenuExtenders();
	/** ��ע��˴���ӵ�ί��Ӧ�� Extenders �еĶ�Ӧ*/
	Extenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FExtendMenuBase::ExtendAssetContextMenu));

	// ͨ��AssetViewContextMenuExtender��չѡ���ʲ������Ĳ˵�
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

	/** Level ������ѡ�� Actor ���Ҽ��˵� */
	LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	/** �ӿ�ѡ��˵�������ӿ����Ͻ�С����ʱ�����Ĳ˵� */
	LevelEditorModule.GetAllLevelViewportOptionsMenuExtenders();
	/** �ӿ���ͼ�˵�������ӿ����Ͻ�С�۾�ʱ�����Ĳ˵� */
	LevelEditorModule.GetAllLevelViewportShowMenuExtenders();
	/** ��ס�Ҽ�����ק Object ���ӿ����ɿ�ʱ�����Ĳ˵� */
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
	// ���� LevelEditor.MainMenu
	//UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");

	//���ڵĵ���ʱ��Ϊ OnLevelEditorCreated ���� FindMenu
	UToolMenu* ToolMenu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu");

	//��λ LevelEditor.MainMenu �е� Section
	 //LevelEditor.MainMenu ��û�� Section ���Դ��� Name_None
	FToolMenuSection& Section = ToolMenu->FindOrAddSection(NAME_None);

	//�����Ӳ˵� Entry
	FToolMenuEntry& Entry = Section.AddSubMenu(
		"NewMenuByToolMenu",//���Ӳ˵� Name
		LOCTEXT("NewMenu2", "New Menu 2"),//��ǩ
		LOCTEXT("NewMenu2_ToolTip", "This is a extended menu by tool menu!"),
		FNewToolMenuChoice()    //��Щ��ֵ���
	);

	//���� Entry ���ֵ�λ��
	Entry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);

	//LevelEditor.MainMenu.NewMenuByUToolMenus ע��Ϊ�˵�
	static const FName BaseMenuName = "LevelEditor.MainMenu.NewMenuByToolMenu";
	ToolMenu = UToolMenus::Get()->RegisterMenu(BaseMenuName);

	//���²˵������ Section �� Entry
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
	(//���һ�� ToolBar ��ť
		"Style Button",
		FToolUIActionChoice(FExecuteAction::CreateRaw(this, &FExtendMenuBase::StyleButtonAction)),
		FText::FromString("Lable:Style Button"),
		FText::FromString("This is a style button by style sample!"),
		FSlateIcon(FExtendEditorStyle::GetStyleSetName(), "AliceTool"//ʹ���Լ�ע��ʱ SlateStyleSet ���� SlateIcon ��ʽ
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

	//ʹ�� Command ��ʽ���� ToolBarEntry
	FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(FExtendEditorCommands::Get().PrintLog);
	//Ϊ ToolBar ���� CommandList
	ToolMenuEntry.SetCommandList(FExtendEditorCommands::Get().CommandList);
	//�����úõ� ToolMenuEntry ��ӵ�ָ��λ��
	Section.AddEntry(ToolMenuEntry);
}
