// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CleanupClash : ModuleRules
{
	public CleanupClash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		// ...need this or we will get errors because Unreal will not know of slates existance otherwise
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
