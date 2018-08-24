// Copyright (c) 2018 Nineva Studios

using UnrealBuildTool;
using System.Collections.Generic;

public class MapsTestProjectTarget : TargetRules
{
	public MapsTestProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "MapsTestProject" } );
	}
}
