﻿#include "pch.h"
#include "EnumResourceTypeMesh.h"

static constexpr const wchar_t* eResMeshPath[static_cast<UINT>(eResMesh::End)]
{
	L"\\Mesh\\Boss Stage(Gargoyles)_child_0.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_1.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_10.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_11.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_12.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_13.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_14.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_15.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_16.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_17.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_18.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_19.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_2.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_20.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_21.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_22.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_23.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_24.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_25.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_26.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_27.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_28.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_29.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_3.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_30.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_31.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_32.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_33.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_34.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_35.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_4.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_5.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_6.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_7.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_8.mesh",
	L"\\Mesh\\Boss Stage(Gargoyles)_child_9.mesh",
	L"\\Mesh\\gargoyles_child_0.mesh",
	L"\\Mesh\\gargoyles_child_1.mesh",
	L"\\Mesh\\gargoyles_child_10.mesh",
	L"\\Mesh\\gargoyles_child_11.mesh",
	L"\\Mesh\\gargoyles_child_12.mesh",
	L"\\Mesh\\gargoyles_child_13.mesh",
	L"\\Mesh\\gargoyles_child_14.mesh",
	L"\\Mesh\\gargoyles_child_15.mesh",
	L"\\Mesh\\gargoyles_child_16.mesh",
	L"\\Mesh\\gargoyles_child_17.mesh",
	L"\\Mesh\\gargoyles_child_18.mesh",
	L"\\Mesh\\gargoyles_child_19.mesh",
	L"\\Mesh\\gargoyles_child_2.mesh",
	L"\\Mesh\\gargoyles_child_20.mesh",
	L"\\Mesh\\gargoyles_child_3.mesh",
	L"\\Mesh\\gargoyles_child_4.mesh",
	L"\\Mesh\\gargoyles_child_5.mesh",
	L"\\Mesh\\gargoyles_child_6.mesh",
	L"\\Mesh\\gargoyles_child_7.mesh",
	L"\\Mesh\\gargoyles_child_8.mesh",
	L"\\Mesh\\gargoyles_child_9.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_0.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_1.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_2.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_3.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_4.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_5.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_6.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_7.mesh",
	L"\\Mesh\\Taurus_Demon_Fianl_child_8.mesh",
};

const wchar_t* EnumResourcePath(eResMesh type)
{
	return eResMeshPath[static_cast<UINT>(type)];
}

