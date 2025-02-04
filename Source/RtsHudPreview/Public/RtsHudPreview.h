#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRtsHudPreviewModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void CreateConsoleCommand();
    void CreateMenuEntry();
    void AddMenuEntry(FMenuBuilder& MenuBuilder);
    void OpenSlateWindow();

private:
    TWeakPtr<SWindow> WindowInstanceWeak;
};
