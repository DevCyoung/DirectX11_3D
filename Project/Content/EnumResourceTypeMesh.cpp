﻿#include "pch.h"
#include "EnumResourceTypeMesh.h"

static constexpr const wchar_t* eResMeshPath[static_cast<UINT>(eResMesh::End)]
{
	L"\\Mesh\\coba_child_0.mesh",
	L"\\Mesh\\coba_child_1.mesh",
	L"\\Mesh\\coba_child_2.mesh",
	L"\\Mesh\\coba_child_3.mesh",
	L"\\Mesh\\coba_child_4.mesh",
	L"\\Mesh\\coba_child_5.mesh",
	L"\\Mesh\\hero_child_0.mesh",
	L"\\Mesh\\hero_child_1.mesh",
	L"\\Mesh\\Iron_Golem3_child_0.mesh",
	L"\\Mesh\\Iron_Golem3_child_1.mesh",
	L"\\Mesh\\Iron_Golem3_child_2.mesh",
	L"\\Mesh\\night_child_0.mesh",
	L"\\Mesh\\night_child_1.mesh",
	L"\\Mesh\\night_child_10.mesh",
	L"\\Mesh\\night_child_11.mesh",
	L"\\Mesh\\night_child_12.mesh",
	L"\\Mesh\\night_child_13.mesh",
	L"\\Mesh\\night_child_14.mesh",
	L"\\Mesh\\night_child_15.mesh",
	L"\\Mesh\\night_child_16.mesh",
	L"\\Mesh\\night_child_17.mesh",
	L"\\Mesh\\night_child_18.mesh",
	L"\\Mesh\\night_child_19.mesh",
	L"\\Mesh\\night_child_2.mesh",
	L"\\Mesh\\night_child_20.mesh",
	L"\\Mesh\\night_child_21.mesh",
	L"\\Mesh\\night_child_22.mesh",
	L"\\Mesh\\night_child_23.mesh",
	L"\\Mesh\\night_child_24.mesh",
	L"\\Mesh\\night_child_25.mesh",
	L"\\Mesh\\night_child_26.mesh",
	L"\\Mesh\\night_child_27.mesh",
	L"\\Mesh\\night_child_28.mesh",
	L"\\Mesh\\night_child_29.mesh",
	L"\\Mesh\\night_child_3.mesh",
	L"\\Mesh\\night_child_30.mesh",
	L"\\Mesh\\night_child_31.mesh",
	L"\\Mesh\\night_child_32.mesh",
	L"\\Mesh\\night_child_33.mesh",
	L"\\Mesh\\night_child_34.mesh",
	L"\\Mesh\\night_child_35.mesh",
	L"\\Mesh\\night_child_36.mesh",
	L"\\Mesh\\night_child_37.mesh",
	L"\\Mesh\\night_child_38.mesh",
	L"\\Mesh\\night_child_39.mesh",
	L"\\Mesh\\night_child_4.mesh",
	L"\\Mesh\\night_child_40.mesh",
	L"\\Mesh\\night_child_41.mesh",
	L"\\Mesh\\night_child_42.mesh",
	L"\\Mesh\\night_child_43.mesh",
	L"\\Mesh\\night_child_5.mesh",
	L"\\Mesh\\night_child_6.mesh",
	L"\\Mesh\\night_child_7.mesh",
	L"\\Mesh\\night_child_8.mesh",
	L"\\Mesh\\night_child_9.mesh",
	L"\\Mesh\\unitychan_child_0.mesh",
	L"\\Mesh\\unitychan_child_1.mesh",
	L"\\Mesh\\unitychan_child_10.mesh",
	L"\\Mesh\\unitychan_child_11.mesh",
	L"\\Mesh\\unitychan_child_12.mesh",
	L"\\Mesh\\unitychan_child_13.mesh",
	L"\\Mesh\\unitychan_child_14.mesh",
	L"\\Mesh\\unitychan_child_15.mesh",
	L"\\Mesh\\unitychan_child_16.mesh",
	L"\\Mesh\\unitychan_child_17.mesh",
	L"\\Mesh\\unitychan_child_18.mesh",
	L"\\Mesh\\unitychan_child_19.mesh",
	L"\\Mesh\\unitychan_child_2.mesh",
	L"\\Mesh\\unitychan_child_20.mesh",
	L"\\Mesh\\unitychan_child_21.mesh",
	L"\\Mesh\\unitychan_child_22.mesh",
	L"\\Mesh\\unitychan_child_3.mesh",
	L"\\Mesh\\unitychan_child_4.mesh",
	L"\\Mesh\\unitychan_child_5.mesh",
	L"\\Mesh\\unitychan_child_6.mesh",
	L"\\Mesh\\unitychan_child_7.mesh",
	L"\\Mesh\\unitychan_child_8.mesh",
	L"\\Mesh\\unitychan_child_9.mesh",
};

const wchar_t* EnumResourcePath(eResMesh type)
{
	return eResMeshPath[static_cast<UINT>(type)];
}

