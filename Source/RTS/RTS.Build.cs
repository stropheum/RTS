// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTS : ModuleRules
{
	public RTS(ReadOnlyTargetRules _) : base(_)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

        PublicDependencyModuleNames.AddRange(collection: new string[]
        {
	        "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput"
        });
        
        PublicDependencyModuleNames.AddRange(collection: new string[]
        {
	        "Slate", "SlateCore"
        });
    }
}
