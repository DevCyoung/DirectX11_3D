#include "pch.h"
#include "EnumResourceTypeSound.h"

static constexpr const wchar_t* eResSoundPath[static_cast<UINT>(eResSound::End)]
{
	L"\\Sound\\Die.wav",
	L"\\Sound\\song_chinatown.wav",
};

const wchar_t* EnumResourcePath(eResSound type)
{
	return eResSoundPath[static_cast<UINT>(type)];
}

