#include "RtsLevelEditor.h"

#include "LevelEditor.h"
#include "RtsLevelEditor/Public/MirrorModeWidget.h"

#define LOCTEXT_NAMESPACE "FRtsLevelEditorModule"

void FRtsLevelEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("RtsLevelEditorModule::StartupModule() called"));
	FTabSpawnerEntry Entry = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		NomadTabName,
		FOnSpawnTab::CreateRaw(this, &FRtsLevelEditorModule::SpawnRtsEditorTab));
	Entry.SetIcon(FSlateIcon());

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
	TSharedRef<SVerticalBox> VerticalMenuWidget = SNew(SVerticalBox)
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
		];

	TSharedRef<SDockTab> Tab = SNew(SDockTab)
		.TabRole(NomadTab)
		.ShouldAutosize(true)
		.OnTabActivated_Lambda([Tab, VerticalMenuWidget](TSharedRef<SDockTab> ActivatedTab, ETabActivationCause)
		{
			// Resize the parent window once the tab is activated
			if (TSharedPtr<SWindow> ParentWindow = ActivatedTab->GetParentWindow())
			{
				FVector2D DesiredSize = VerticalMenuWidget->GetDesiredSize();
				ParentWindow->Resize(DesiredSize); // Resize parent window to fit content
			}
		})
		[
			VerticalMenuWidget
		];
	
	return Tab;
}

void FRtsLevelEditorModule::OpenEditorWindow() const
{
	FGlobalTabmanager::Get()->TryInvokeTab(NomadTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRtsLevelEditorModule, RtsLevelEditor)
