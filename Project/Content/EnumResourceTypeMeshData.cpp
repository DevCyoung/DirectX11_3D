#include "pch.h"
#include "EnumResourceTypeMeshData.h"

static constexpr const wchar_t* eResMeshDataPath[static_cast<UINT>(eResMeshData::End)]
{
	L"\\MeshData\\black.mesh_data",
};

const wchar_t* EnumResourcePath(eResMeshData type)
{
	return eResMeshDataPath[static_cast<UINT>(type)];
}

