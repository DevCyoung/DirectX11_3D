﻿#include "pch.h"
#include "EnumResourceTypeMeshData.h"

static constexpr const wchar_t* eResMeshDataPath[static_cast<UINT>(eResMeshData::End)]
{
	L"\\MeshData\\coba.mesh_data",
	L"\\MeshData\\coba_child_0.mesh_data",
	L"\\MeshData\\coba_child_1.mesh_data",
	L"\\MeshData\\coba_child_2.mesh_data",
	L"\\MeshData\\coba_child_3.mesh_data",
	L"\\MeshData\\coba_child_4.mesh_data",
	L"\\MeshData\\coba_child_5.mesh_data",
	L"\\MeshData\\hero.mesh_data",
	L"\\MeshData\\hero_child_0.mesh_data",
	L"\\MeshData\\hero_child_1.mesh_data",
	L"\\MeshData\\Iron_Golem3.mesh_data",
	L"\\MeshData\\Iron_Golem3_child_0.mesh_data",
	L"\\MeshData\\Iron_Golem3_child_1.mesh_data",
	L"\\MeshData\\Iron_Golem3_child_2.mesh_data",
	L"\\MeshData\\night.mesh_data",
	L"\\MeshData\\night_child_0.mesh_data",
	L"\\MeshData\\night_child_1.mesh_data",
	L"\\MeshData\\night_child_10.mesh_data",
	L"\\MeshData\\night_child_11.mesh_data",
	L"\\MeshData\\night_child_12.mesh_data",
	L"\\MeshData\\night_child_13.mesh_data",
	L"\\MeshData\\night_child_14.mesh_data",
	L"\\MeshData\\night_child_15.mesh_data",
	L"\\MeshData\\night_child_16.mesh_data",
	L"\\MeshData\\night_child_17.mesh_data",
	L"\\MeshData\\night_child_18.mesh_data",
	L"\\MeshData\\night_child_19.mesh_data",
	L"\\MeshData\\night_child_2.mesh_data",
	L"\\MeshData\\night_child_20.mesh_data",
	L"\\MeshData\\night_child_21.mesh_data",
	L"\\MeshData\\night_child_22.mesh_data",
	L"\\MeshData\\night_child_23.mesh_data",
	L"\\MeshData\\night_child_24.mesh_data",
	L"\\MeshData\\night_child_25.mesh_data",
	L"\\MeshData\\night_child_26.mesh_data",
	L"\\MeshData\\night_child_27.mesh_data",
	L"\\MeshData\\night_child_28.mesh_data",
	L"\\MeshData\\night_child_29.mesh_data",
	L"\\MeshData\\night_child_3.mesh_data",
	L"\\MeshData\\night_child_30.mesh_data",
	L"\\MeshData\\night_child_31.mesh_data",
	L"\\MeshData\\night_child_32.mesh_data",
	L"\\MeshData\\night_child_33.mesh_data",
	L"\\MeshData\\night_child_34.mesh_data",
	L"\\MeshData\\night_child_35.mesh_data",
	L"\\MeshData\\night_child_36.mesh_data",
	L"\\MeshData\\night_child_37.mesh_data",
	L"\\MeshData\\night_child_38.mesh_data",
	L"\\MeshData\\night_child_39.mesh_data",
	L"\\MeshData\\night_child_4.mesh_data",
	L"\\MeshData\\night_child_40.mesh_data",
	L"\\MeshData\\night_child_41.mesh_data",
	L"\\MeshData\\night_child_42.mesh_data",
	L"\\MeshData\\night_child_43.mesh_data",
	L"\\MeshData\\night_child_5.mesh_data",
	L"\\MeshData\\night_child_6.mesh_data",
	L"\\MeshData\\night_child_7.mesh_data",
	L"\\MeshData\\night_child_8.mesh_data",
	L"\\MeshData\\night_child_9.mesh_data",
	L"\\MeshData\\unitychan.mesh_data",
	L"\\MeshData\\unitychan_child_0.mesh_data",
	L"\\MeshData\\unitychan_child_1.mesh_data",
	L"\\MeshData\\unitychan_child_10.mesh_data",
	L"\\MeshData\\unitychan_child_11.mesh_data",
	L"\\MeshData\\unitychan_child_12.mesh_data",
	L"\\MeshData\\unitychan_child_13.mesh_data",
	L"\\MeshData\\unitychan_child_14.mesh_data",
	L"\\MeshData\\unitychan_child_15.mesh_data",
	L"\\MeshData\\unitychan_child_16.mesh_data",
	L"\\MeshData\\unitychan_child_17.mesh_data",
	L"\\MeshData\\unitychan_child_18.mesh_data",
	L"\\MeshData\\unitychan_child_19.mesh_data",
	L"\\MeshData\\unitychan_child_2.mesh_data",
	L"\\MeshData\\unitychan_child_20.mesh_data",
	L"\\MeshData\\unitychan_child_21.mesh_data",
	L"\\MeshData\\unitychan_child_22.mesh_data",
	L"\\MeshData\\unitychan_child_3.mesh_data",
	L"\\MeshData\\unitychan_child_4.mesh_data",
	L"\\MeshData\\unitychan_child_5.mesh_data",
	L"\\MeshData\\unitychan_child_6.mesh_data",
	L"\\MeshData\\unitychan_child_7.mesh_data",
	L"\\MeshData\\unitychan_child_8.mesh_data",
	L"\\MeshData\\unitychan_child_9.mesh_data",
};

const wchar_t* EnumResourcePath(eResMeshData type)
{
	return eResMeshDataPath[static_cast<UINT>(type)];
}

