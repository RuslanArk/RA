// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RA : ModuleRules
{
	public RA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
            "Core",
            "CoreUObject",
            "Engine", 
            "InputCore", 
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "UMG",
        });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"RA/",
		});
	}
}
