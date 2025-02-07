#include "RtsLevelEditor.h"

#include "LevelEditor.h"
#include "RtsLevelEditor/MirrorModeWidget.h"

#define LOCTEXT_NAMESPACE "FRtsLevelEditorModule"

void FRtsLevelEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("RtsLevelEditorModule::StartupModule() called"));
	FTabSpawnerEntry Foo = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		NomadTabName,
		FOnSpawnTab::CreateRaw(this, &FRtsLevelEditorModule::SpawnRtsEditorTab));
	Foo.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Levels"));

	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

		ToolBarExtender = MakeShared<FExtender>();
		ToolBarExtender->AddToolBarExtension(
			"Play",
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
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Levels"));
}

TSharedRef<SDockTab> FRtsLevelEditorModule::SpawnRtsEditorTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(SMirrorModeWidget)
		];
}

void FRtsLevelEditorModule::OpenEditorWindow() const
{
	FGlobalTabmanager::Get()->TryInvokeTab(NomadTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRtsLevelEditorModule, RtsLevelEditor)
