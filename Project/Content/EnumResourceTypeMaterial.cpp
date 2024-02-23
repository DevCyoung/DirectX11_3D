#include "pch.h"
#include "EnumResourceTypeMaterial.h"

static constexpr const wchar_t* eResMaterialPath[static_cast<UINT>(eResMaterial::End)]
{
	L"\\Material\\black_0.mat",
	L"\\Material\\black_1.mat",
	L"\\Material\\black_2.mat",
	L"\\Material\\black_3.mat",
	L"\\Material\\coba_0.mat",
	L"\\Material\\hero_0.mat",
	L"\\Material\\monster_0.mat",
	L"\\Material\\monster_1.mat",
	L"\\Material\\monster_2.mat",
	L"\\Material\\monster_3.mat",
	L"\\Material\\Room_0.mat",
	L"\\Material\\Room_1.mat",
	L"\\Material\\Spider_3_0.mat",
};

const wchar_t* EnumResourcePath(eResMaterial type)
{
	return eResMaterialPath[static_cast<UINT>(type)];
}

