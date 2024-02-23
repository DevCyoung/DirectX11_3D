#include "pch.h"
#include "EnumResourceTypeMeshData.h"

static constexpr const wchar_t* eResMeshDataPath[static_cast<UINT>(eResMeshData::End)]
{
	L"\\MeshData\\black.mesh_data",
	L"\\MeshData\\coba.mesh_data",
	L"\\MeshData\\hero.mesh_data",
	L"\\MeshData\\monster.mesh_data",
	L"\\MeshData\\Room.mesh_data",
	L"\\MeshData\\Spider_3.mesh_data",
};

const wchar_t* EnumResourcePath(eResMeshData type)
{
	return eResMeshDataPath[static_cast<UINT>(type)];
}

