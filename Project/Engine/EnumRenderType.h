#pragma once

enum class eRenderPriorityType
{
	Opqaue,
	CutOut,
	Transparent,
	End,
	PostProcess,
};

enum class eCameraPriorityType
{
	Editor,
	BackGround,
	Main,
	UI,
	End
};

enum class eCameraProjectionType
{
	Perspective,
	Orthographic,
	End
};
