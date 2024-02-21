#include "pch.h"
#include "MeshData.h"
#include "Mesh.h"
#include "Material.h"
#include "PathManager.h"

#include "FBXLoader.h"
#include "PathManager.h"
#include <FBXLoader/FBXLoadManager.h>
#include "StructVertex.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "EnumRenderType.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include <Shlwapi.h>
#include "StructuredBuffer.h"
#include "Animator3D.h"
#include "GameObject.h"
#include "PathManager.h"
#include  <Helper\FileHelper.h>
MeshData::MeshData()
    : Resource(eResourceType::MeshData)
    , mMesh(nullptr)
    , mMaterials()

{
}
MeshData::~MeshData()
{
    //DELETE_POINTER(mMesh);
    //for (Material* mat : mMaterials)
    //{
    //    DELETE_POINTER(mat);
    //}
    //
    //mMaterials.clear();
}

HRESULT MeshData::Load(const std::wstring& filePath)
{
    FILE* file = nullptr;
    errno_t err = _wfopen_s(&file, filePath.c_str(), L"rb");
    (void)err;

    //Assert(err, ASSERT_MSG_INVALID);
    Assert(file, ASSERT_MSG_NULL);

    std::wstring meshPath;
    LoadWString(&meshPath, file);
    mMesh = gResourceManager->FindAndLoadOrNull<Mesh>(meshPath);

    UINT size;
    fread(&size, sizeof(UINT), 1, file);


    for (UINT i = 0; i < size; ++i)
    {        
        std::wstring matPath;
        LoadWString(&matPath, file);
        Material* mat = gResourceManager->FindAndLoadOrNull<Material>(matPath);
        mMaterials.push_back(mat);
    }

    fclose(file);
    return E_NOTIMPL;
}

HRESULT MeshData::Save(const std::wstring& name)
{
    std::wstring meshDataPath = gPathManager->GetResourcePath();
    meshDataPath += L"\\MeshData\\";
    meshDataPath += name;
    meshDataPath += L".mesh_data";

    FILE* file = nullptr;
    errno_t err = _wfopen_s(&file, meshDataPath.c_str(), L"wb");
    (void)err;

    //Assert(err, ASSERT_MSG_INVALID);
    Assert(file, ASSERT_MSG_NULL);

    //SaveWString(meshDataPath, file);


    std::wstring meshPath = L"\\Mesh\\";    
    meshPath += name;
    meshPath += L".mesh";

    SaveWString(meshPath, file);

    if (mMesh)
    {
        mMesh->Save(meshPath);
    }
    
    UINT size = static_cast<UINT>(mMaterials.size());
    fwrite(&size, sizeof(UINT), 1, file);

    for (int i = 0; i < mMaterials.size(); ++i)
    {        
        std::wstring matPath = L"\\Material\\";
        matPath += name;
        matPath += L"_";
        matPath += std::to_wstring(i);
        matPath += L".mat";

        SaveWString(matPath, file);
        mMaterials[i]->Save(matPath);
    }    

    fclose(file);
    return E_NOTIMPL;
}

GameObject* MeshData::Instantiate()
{
    GameObject* obj = new GameObject();

    obj->AddComponent<MeshRenderer>();
    obj->GetComponent<MeshRenderer>()->SetMesh(mMesh);

    for (int i = 0; i < mMaterials.size(); ++i)
    {
        obj->GetComponent<MeshRenderer>()->SetMaterial(mMaterials[i], i);
    }
    
    if (mMesh->IsAnimMesh())
    {
        obj->AddComponent<Animator3D>();

        obj->GetComponent<Animator3D>()->SetBones(mMesh->GetBones());
        obj->GetComponent<Animator3D>()->SetAnimClip(mMesh->GetAnimClip());        
    }
	return obj;
}
