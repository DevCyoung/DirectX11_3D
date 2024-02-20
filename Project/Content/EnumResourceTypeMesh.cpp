#include "pch.h"
#include "EnumResourceTypeMesh.h"

static constexpr const wchar_t* eResMeshPath[static_cast<UINT>(eResMesh::End)]
{
	L"\\Mesh\\dummy.mesh",
};

const wchar_t* EnumResourcePath(eResMesh type)
{
	return eResMeshPath[static_cast<UINT>(type)];
}

