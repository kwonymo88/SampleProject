// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TZCore : ModuleRules
{
	public TZCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
	}
}
