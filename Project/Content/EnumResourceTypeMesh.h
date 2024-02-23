#pragma once

enum class eResMesh
{
	black,
	coba,
	dummy,
	hero,
	monster,
	Room,
	Spider_3,
	End
};

const wchar_t* EnumResourcePath(eResMesh type);

