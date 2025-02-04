#include "RtsHudPreview.h"

#include "LevelEditor.h"
#include "RTS/UnitSelectionViewWidget.h"


#define LOCTEXT_NAMESPACE "FRtsHudPreviewModule"

void FRtsHudPreviewModule::StartupModule()
{
	CreateConsoleCommand();
	CreateMenuEntry();
}

void FRtsHudPreviewModule::ShutdownModule() {}

void FRtsHudPreviewModule::CreateConsoleCommand()
{
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("OpenRtsHudPreview"),
		TEXT("Opens the RTS HUD Preview window"),
		FConsoleCommandDelegate::CreateRaw(this, &FRtsHudPreviewModule::OpenSlateWindow),
		ECVF_Default);
}

void FRtsHudPreviewModule::CreateMenuEntry()
{
	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

		TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
		Extender->AddMenuExtension(
			"WindowLayout",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FRtsHudPreviewModule::AddMenuEntry)
		);

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extender);
	}
}

void FRtsHudPreviewModule::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("RtsHudPreviewMenu", "Open RTS HUD Preview"),
		LOCTEXT("RtsHudPreviewMenu", "Opens the RTS HUD Preview Window"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FRtsHudPreviewModule::OpenSlateWindow)));
}

void FRtsHudPreviewModule::OpenSlateWindow()
{
	if (WindowInstanceWeak.IsValid())
	{	// Wipe duplicate instances before showing/refreshing
		FSlateApplication::Get().RequestDestroyWindow(WindowInstanceWeak.Pin().ToSharedRef());
		WindowInstanceWeak.Reset();
	}

	const TSharedRef<SWindow> WindowInstance = SNew(SWindow)
		.Title(FText::FromString("RtsHudPreview"))
		.ClientSize(FVector2D(640, 480))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			SNew(SUnitSelectionViewWidget)
		];

	WindowInstanceWeak = WindowInstance;

	FSlateApplication::Get().AddWindow(WindowInstance);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRtsHudPreviewModule, RtsHudPreview)
