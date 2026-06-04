// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EchoProtocol : ModuleRules
{
	public EchoProtocol(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"EchoProtocol",
			"EchoProtocol/Variant_Platforming",
			"EchoProtocol/Variant_Platforming/Animation",
			"EchoProtocol/Variant_Combat",
			"EchoProtocol/Variant_Combat/AI",
			"EchoProtocol/Variant_Combat/Animation",
			"EchoProtocol/Variant_Combat/Gameplay",
			"EchoProtocol/Variant_Combat/Interfaces",
			"EchoProtocol/Variant_Combat/UI",
			"EchoProtocol/Variant_SideScrolling",
			"EchoProtocol/Variant_SideScrolling/AI",
			"EchoProtocol/Variant_SideScrolling/Gameplay",
			"EchoProtocol/Variant_SideScrolling/Interfaces",
			"EchoProtocol/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
