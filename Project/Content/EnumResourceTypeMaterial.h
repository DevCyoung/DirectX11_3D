#pragma once

enum class eResMaterial
{
	black_0,
	black_1,
	black_2,
	black_3,
	dummy,
	End
};

const wchar_t* EnumResourcePath(eResMaterial type);

