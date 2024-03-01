﻿#include "pch.h"
#include "EnumResourceTypeMaterial.h"

static constexpr const wchar_t* eResMaterialPath[static_cast<UINT>(eResMaterial::End)]
{
	L"\\Material\\Boss Stage(Gargoyles)_child_0_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_10_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_11_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_12_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_13_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_14_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_15_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_16_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_17_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_18_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_19_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_1_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_20_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_21_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_22_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_23_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_24_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_25_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_26_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_27_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_28_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_29_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_2_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_30_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_31_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_32_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_33_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_34_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_35_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_3_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_4_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_5_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_6_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_7_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_8_0.mat",
	L"\\Material\\Boss Stage(Gargoyles)_child_9_0.mat",
	L"\\Material\\Capsule_child_0_0.mat",
	L"\\Material\\Cube_child_0_0.mat",
	L"\\Material\\gargoyles_child_0_0.mat",
	L"\\Material\\gargoyles_child_10_0.mat",
	L"\\Material\\gargoyles_child_11_0.mat",
	L"\\Material\\gargoyles_child_12_0.mat",
	L"\\Material\\gargoyles_child_13_0.mat",
	L"\\Material\\gargoyles_child_14_0.mat",
	L"\\Material\\gargoyles_child_15_0.mat",
	L"\\Material\\gargoyles_child_16_0.mat",
	L"\\Material\\gargoyles_child_17_0.mat",
	L"\\Material\\gargoyles_child_18_0.mat",
	L"\\Material\\gargoyles_child_19_0.mat",
	L"\\Material\\gargoyles_child_1_0.mat",
	L"\\Material\\gargoyles_child_20_0.mat",
	L"\\Material\\gargoyles_child_2_0.mat",
	L"\\Material\\gargoyles_child_3_0.mat",
	L"\\Material\\gargoyles_child_4_0.mat",
	L"\\Material\\gargoyles_child_5_0.mat",
	L"\\Material\\gargoyles_child_6_0.mat",
	L"\\Material\\gargoyles_child_7_0.mat",
	L"\\Material\\gargoyles_child_8_0.mat",
	L"\\Material\\gargoyles_child_9_0.mat",
	L"\\Material\\Plane_child_0_0.mat",
	L"\\Material\\Quad_child_0_0.mat",
	L"\\Material\\Sphere_child_0_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_0_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_1_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_2_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_3_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_4_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_5_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_6_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_7_0.mat",
	L"\\Material\\Taurus_Demon_Fianl_child_8_0.mat",
};

const wchar_t* EnumResourcePath(eResMaterial type)
{
	return eResMaterialPath[static_cast<UINT>(type)];
}

