#include "pch.h"
#include "EnumResourceTypeMaterial.h"

static constexpr const wchar_t* eResMaterialPath[static_cast<UINT>(eResMaterial::End)]
{
	L"\\Material\\dummy.mat",
};

const wchar_t* EnumResourcePath(eResMaterial type)
{
	return eResMaterialPath[static_cast<UINT>(type)];
}

