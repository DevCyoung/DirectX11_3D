#pragma once

enum class eResMeshData
{
	black,
	coba,
	hero,
	monster,
	Room,
	Spider_3,
	End
};

const wchar_t* EnumResourcePath(eResMeshData type);

