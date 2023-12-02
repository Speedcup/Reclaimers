// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Reclaimers : ModuleRules
{
	public Reclaimers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });


		PublicIncludePaths.AddRange(new string[] {
			"D:/-DEVELOPMENT-/UE5/Reclaimers/Source/Reclaimers/ThirdParty/Discord"
		});

		PublicAdditionalLibraries.AddRange(new string[] {
			"D:/-DEVELOPMENT-/UE5/Reclaimers/Binaries/Win64/discord_game_sdk.dll.lib"
		});

		// DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		// PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemSteam" });
		// PublicAdditionalLibraries.AddRange(new string[] { "discord_game_sdk" });
    }
}
