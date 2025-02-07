#include "RtsLevelEditor.h"

#include "LevelEditor.h"
#include "RtsLevelEditor/Public/MirrorModeWidget.h"

#define LOCTEXT_NAMESPACE "FRtsLevelEditorModule"

void FRtsLevelEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("RtsLevelEditorModule::StartupModule() called"));
	FTabSpawnerEntry Foo = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		NomadTabName,
		FOnSpawnTab::CreateRaw(this, &FRtsLevelEditorModule::SpawnRtsEditorTab));
	Foo.SetIcon(FSlateIcon());

	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

		ToolBarExtender = MakeShared<FExtender>();
		ToolBarExtender->AddToolBarExtension(
			"Content",
			EExtensionHook::After,
			nullptr,
			FToolBarExtensionDelegate::CreateRaw(this, &FRtsLevelEditorModule::ExtendToolBar)
		);

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	}
}

void FRtsLevelEditorModule::ShutdownModule()
{
	if (ToolBarExtender.IsValid())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.GetToolBarExtensibilityManager()->RemoveExtender(ToolBarExtender);
		ToolBarExtender.Reset();
	}

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NomadTabName);
}

void FRtsLevelEditorModule::ExtendToolBar(FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.AddToolBarButton(
		FUIAction(FExecuteAction::CreateRaw(this, &FRtsLevelEditorModule::OpenEditorWindow)),
		NAME_None,
		FText::FromString("Open My Editor"),
		FText::FromString("Opens my custom editor window"),
		FSlateIcon());
}

// ReSharper disable once CppMemberFunctionMayBeStatic
TSharedRef<SDockTab> FRtsLevelEditorModule::SpawnRtsEditorTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SExpandableArea)
				.AreaTitle(FText::FromString("Brush Options"))
				.InitiallyCollapsed(false)
				.BodyContent()
				[
					SNew(SMirrorModeWidget)	
				]
			]
		];
}

void FRtsLevelEditorModule::OpenEditorWindow() const
{
	FGlobalTabmanager::Get()->TryInvokeTab(NomadTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRtsLevelEditorModule, RtsLevelEditor)
