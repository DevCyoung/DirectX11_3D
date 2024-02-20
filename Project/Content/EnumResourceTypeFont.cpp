#include "pch.h"
#include "EnumResourceTypeFont.h"

static constexpr const wchar_t* eResFontPath[static_cast<UINT>(eResFont::End)]
{
	L"\\Font\\dummy.font",
};

const wchar_t* EnumResourcePath(eResFont type)
{
	return eResFontPath[static_cast<UINT>(type)];
}

