#pragma once

enum class eResSound
{
	Die,
	song_chinatown,
	End
};

const wchar_t* EnumResourcePath(eResSound type);

