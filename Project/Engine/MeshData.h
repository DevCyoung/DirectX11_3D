#pragma once
#include "Resource.h"

class Mesh;
class Material;
class GameObject;
class MeshData : public Resource
{
public:
	MeshData();
	virtual ~MeshData();
	MeshData(const MeshData&) = delete;
	MeshData& operator=(const MeshData&) = delete;

	// Resource을(를) 통해 상속됨
	HRESULT Load(const std::wstring& filePath) override;
	HRESULT Save(const std::wstring& name) override;

	GameObject* Instantiate();

	void SetMesh(Mesh* mesh) { mMesh = mesh; }
	void SetMaterial(std::vector<Material*> materials) { mMaterials = materials;  }

private:
	Mesh* mMesh;
	std::vector<Material*>	mMaterials;
};

