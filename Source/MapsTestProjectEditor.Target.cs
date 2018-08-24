// Copyright (c) 2018 Nineva Studios

using UnrealBuildTool;
using System.Collections.Generic;

public class MapsTestProjectEditorTarget : TargetRules
{
	public MapsTestProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "MapsTestProject" } );
	}
}
