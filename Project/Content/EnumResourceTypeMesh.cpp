#include "pch.h"
#include "EnumResourceTypeMesh.h"

static constexpr const wchar_t* eResMeshPath[static_cast<UINT>(eResMesh::End)]
{
	L"\\Mesh\\black.mesh",
	L"\\Mesh\\coba.mesh",
	L"\\Mesh\\dummy.mesh",
	L"\\Mesh\\hero.mesh",
	L"\\Mesh\\monster.mesh",
	L"\\Mesh\\Room.mesh",
	L"\\Mesh\\Spider_3.mesh",
};

const wchar_t* EnumResourcePath(eResMesh type)
{
	return eResMeshPath[static_cast<UINT>(type)];
}

