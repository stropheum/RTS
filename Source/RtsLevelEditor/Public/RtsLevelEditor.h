#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRtsLevelEditorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

protected:
	void ExtendToolBar(FToolBarBuilder& ToolBarBuilder);

	TSharedRef<SDockTab> SpawnRtsEditorTab(const FSpawnTabArgs& Args);

	void OpenEditorWindow() const;

private:
	const FName NomadTabName = "RtsLevelEditor";
	TSharedPtr<FExtender> ToolBarExtender;
};
