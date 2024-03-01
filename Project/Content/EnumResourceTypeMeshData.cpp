﻿#include "pch.h"
#include "EnumResourceTypeMeshData.h"

static constexpr const wchar_t* eResMeshDataPath[static_cast<UINT>(eResMeshData::End)]
{
	L"\\MeshData\\Boss Stage(Gargoyles).mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_0.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_1.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_10.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_11.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_12.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_13.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_14.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_15.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_16.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_17.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_18.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_19.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_2.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_20.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_21.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_22.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_23.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_24.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_25.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_26.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_27.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_28.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_29.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_3.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_30.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_31.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_32.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_33.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_34.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_35.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_4.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_5.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_6.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_7.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_8.mesh_data",
	L"\\MeshData\\Boss Stage(Gargoyles)_child_9.mesh_data",
	L"\\MeshData\\Capsule.mesh_data",
	L"\\MeshData\\Capsule_child_0.mesh_data",
	L"\\MeshData\\Cube.mesh_data",
	L"\\MeshData\\Cube_child_0.mesh_data",
	L"\\MeshData\\gargoyles.mesh_data",
	L"\\MeshData\\gargoyles_child_0.mesh_data",
	L"\\MeshData\\gargoyles_child_1.mesh_data",
	L"\\MeshData\\gargoyles_child_10.mesh_data",
	L"\\MeshData\\gargoyles_child_11.mesh_data",
	L"\\MeshData\\gargoyles_child_12.mesh_data",
	L"\\MeshData\\gargoyles_child_13.mesh_data",
	L"\\MeshData\\gargoyles_child_14.mesh_data",
	L"\\MeshData\\gargoyles_child_15.mesh_data",
	L"\\MeshData\\gargoyles_child_16.mesh_data",
	L"\\MeshData\\gargoyles_child_17.mesh_data",
	L"\\MeshData\\gargoyles_child_18.mesh_data",
	L"\\MeshData\\gargoyles_child_19.mesh_data",
	L"\\MeshData\\gargoyles_child_2.mesh_data",
	L"\\MeshData\\gargoyles_child_20.mesh_data",
	L"\\MeshData\\gargoyles_child_3.mesh_data",
	L"\\MeshData\\gargoyles_child_4.mesh_data",
	L"\\MeshData\\gargoyles_child_5.mesh_data",
	L"\\MeshData\\gargoyles_child_6.mesh_data",
	L"\\MeshData\\gargoyles_child_7.mesh_data",
	L"\\MeshData\\gargoyles_child_8.mesh_data",
	L"\\MeshData\\gargoyles_child_9.mesh_data",
	L"\\MeshData\\Plane.mesh_data",
	L"\\MeshData\\Plane_child_0.mesh_data",
	L"\\MeshData\\Quad.mesh_data",
	L"\\MeshData\\Quad_child_0.mesh_data",
	L"\\MeshData\\Sphere.mesh_data",
	L"\\MeshData\\Sphere_child_0.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_0.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_1.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_2.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_3.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_4.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_5.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_6.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_7.mesh_data",
	L"\\MeshData\\Taurus_Demon_Fianl_child_8.mesh_data",
};

const wchar_t* EnumResourcePath(eResMeshData type)
{
	return eResMeshDataPath[static_cast<UINT>(type)];
}

