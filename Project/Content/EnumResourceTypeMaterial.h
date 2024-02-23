#pragma once

enum class eResMaterial
{
	black_0,
	black_1,
	black_2,
	black_3,
	coba_0,
	hero_0,
	monster_0,
	monster_1,
	monster_2,
	monster_3,
	Room_0,
	Room_1,
	Spider_3_0,
	End
};

const wchar_t* EnumResourcePath(eResMaterial type);

