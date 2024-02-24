#include "pch.h"
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
#include "MeshData.h"

//Shlwapi.lib

void FBXLoader::LoadFBX(const std::wstring& relativePath)
{
	std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	filePath += relativePath;

	FBXLoadManager::GetInstance()->Load(filePath);
	//FbxInstantiate(relativePath);

	//CreateMeshFromFBX();
	//FBXLoader::FbxInstantiate(relativePath);
}

void FBXLoader::CreateMeshFromFBX()
{
}

Matrix GetMatrixFromFbxMatrix(FbxAMatrix& _mat)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[i][j] = (float)_mat.Get(i, j);
		}
	}
	return mat;
}

MeshData* FBXLoader::FbxInstantiate(const std::wstring& relativePath)
{
	std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	filePath += relativePath;
	FBXLoadManager* const fbxLoadManager = FBXLoadManager::GetInstance();
	fbxLoadManager->Load(filePath);

	Shader* const shader = gResourceManager->FindAndLoad<Shader>(L"Std3D");

	MeshData* retmeshData = new MeshData;
	const tContainer& container = fbxLoadManager->GetContainer(0);
	const UINT VERTEX_COUNT = (UINT)container.vecPos.size();


	std::vector<tVertex> vertexBuffer;
	std::vector<size_t> sizes;
	std::vector<UINT> indexBuffers;

	Assert(!container.vecPos.empty(), ASSERT_MSG_INVALID);
	Assert(!container.vecIdx.empty(), ASSERT_MSG_INVALID);

	//retMeshDatas.push_back(retmeshData);

	vertexBuffer.resize(VERTEX_COUNT);
	for (UINT j = 0; j < VERTEX_COUNT; ++j)
	{
		vertexBuffer[j].Position = container.vecPos[j];
		vertexBuffer[j].UV = container.vecUV[j];
		vertexBuffer[j].Color = Vector4(1.f, 0.f, 1.f, 1.f);
		vertexBuffer[j].Normal = container.vecNormal[j];
		vertexBuffer[j].Tangent = container.vecTangent[j];
		vertexBuffer[j].Binormal = container.vecBinormal[j];
		vertexBuffer[j].vWeights = container.vecWeights[j];
		vertexBuffer[j].vIndices = container.vecIndices[j];
	}

	indexBuffers.reserve(VERTEX_COUNT);
	for (const std::vector<UINT>& indexeBuffer : container.vecIdx)
	{
		for (UINT index : indexeBuffer)
		{
			indexBuffers.push_back(index);
		}
	}

	sizes.reserve(container.vecIdx.size());
	for (const std::vector<UINT>& indexeBuffer : container.vecIdx)
	{
		sizes.push_back(indexeBuffer.size());
	}

	Mesh* const mesh = new Mesh(vertexBuffer.data(),
		VERTEX_COUNT,
		sizeof(tVertex),
		indexBuffers.data(),
		sizes.data(),
		container.vecIdx.size(),
		sizeof(UINT));

	retmeshData->SetMesh(mesh);

	std::vector<Material*> materials;
	for (UINT j = 0; j < container.vecMtrl.size(); ++j)
	{
		//FIXME
		if (mesh->GetIndexBufferCount() <= j)
		{
			continue;
		}

		Material* material = new Material();
		material->SetShader(shader);

		const std::wstring& resourcePath = gPathManager->GetResourcePath();

		std::vector<std::wstring> paths;

		paths.push_back(container.vecMtrl[j].strDiff);
		paths.push_back(container.vecMtrl[j].strNormal);
		paths.push_back(container.vecMtrl[j].strSpec);
		paths.push_back(container.vecMtrl[j].strEmis);

		for (int k = 0; k < paths.size(); ++k)
		{
			if (paths[k].empty())
			{
				continue;
			}
			else if (paths[k].size() <= resourcePath.size())
			{
				continue;
			}

			std::wstring texRelativePath = paths[k].substr(resourcePath.size());
			if (std::wstring::npos == paths[k].find(resourcePath))
			{
				continue;
			}
			if (texRelativePath.empty())
			{
				continue;
			}

			LPCWSTR lpcwstr = paths[k].c_str();
			if (!PathFileExistsW(lpcwstr))
			{
				continue;
			}
			else if (!PathFileExistsW(paths[k].c_str()))
			{
				continue;
			}
			else
			{
				Texture* tex = gResourceManager->FindAndLoadOrNull<Texture>(texRelativePath);
				material->SetTexture(TEX_PARAM(TEX_0 + k), tex);
			}
		}

		materials.push_back(material);
	}
	retmeshData->SetMaterial(materials);

	if (!container.bAnimation)
	{
		FBXLoadManager::GetInstance()->Release();
		return retmeshData;
		//continue;
	}

	std::vector<tBone*>& vecBone = fbxLoadManager->GetBones();
	UINT iFrameCount = 0;
	for (UINT j = 0; j < vecBone.size(); ++j)
	{
		tMTBone bone = {};
		bone.iDepth = vecBone[j]->depth;
		bone.iParentIndx = vecBone[j]->parentIdx;
		bone.matBone = GetMatrixFromFbxMatrix(vecBone[j]->matBone);
		bone.matOffset = GetMatrixFromFbxMatrix(vecBone[j]->matOffset);
		bone.strBoneName = vecBone[j]->boneName;

		for (UINT k = 0; k < vecBone[j]->vecKeyFrame.size(); ++k)
		{
			tMTKeyFrame tKeyframe = {};
			tKeyframe.dTime = vecBone[j]->vecKeyFrame[k].dTime;
			tKeyframe.iFrame = k;
			tKeyframe.vTranslate.x = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetT().mData[0];
			tKeyframe.vTranslate.y = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetT().mData[1];
			tKeyframe.vTranslate.z = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetT().mData[2];

			tKeyframe.vScale.x = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetS().mData[0];
			tKeyframe.vScale.y = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetS().mData[1];
			tKeyframe.vScale.z = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetS().mData[2];

			tKeyframe.qRot.x = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetQ().mData[0];
			tKeyframe.qRot.y = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetQ().mData[1];
			tKeyframe.qRot.z = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetQ().mData[2];
			tKeyframe.qRot.w = (float)vecBone[j]->vecKeyFrame[k].matTransform.GetQ().mData[3];

			bone.vecKeyFrame.push_back(tKeyframe);
		}

		iFrameCount = max(iFrameCount, (UINT)bone.vecKeyFrame.size());

		mesh->m_vecBones.push_back(bone);
	}

	std::vector<tAnimClip*>& vecAnimClip = fbxLoadManager->GetAnimationClips();
	for (UINT j = 0; j < vecAnimClip.size(); ++j)
	{
		tMTAnimClip tClip = {};

		tClip.strAnimName = vecAnimClip[j]->strName;
		tClip.dStartTime = vecAnimClip[j]->tStartTime.GetSecondDouble();
		tClip.dEndTime = vecAnimClip[j]->tEndTime.GetSecondDouble();
		tClip.dTimeLength = tClip.dEndTime - tClip.dStartTime;

		tClip.iStartFrame = (int)vecAnimClip[j]->tStartTime.GetFrameCount(vecAnimClip[j]->eMode);
		tClip.iEndFrame = (int)vecAnimClip[j]->tEndTime.GetFrameCount(vecAnimClip[j]->eMode);
		tClip.iFrameLength = tClip.iEndFrame - tClip.iStartFrame;
		tClip.eMode = vecAnimClip[j]->eMode;

		mesh->m_vecAnimClip.push_back(tClip);
	}

	// Animation 이 있는 Mesh 경우 structuredbuffer 만들어두기
	if (mesh->IsAnimMesh())
	{
		// BoneOffet 행렬
		std::vector<Matrix> vecOffset;
		std::vector<tFrameTrans> vecFrameTrans;
		vecFrameTrans.resize((UINT)mesh->m_vecBones.size() * iFrameCount);

		for (size_t j = 0; j < mesh->m_vecBones.size(); ++j)
		{
			vecOffset.push_back(mesh->m_vecBones[j].matOffset);

			for (size_t k = 0; k < mesh->m_vecBones[k].vecKeyFrame.size(); ++k)
			{
				vecFrameTrans[(UINT)mesh->m_vecBones.size() * k + k]
					= tFrameTrans{ Vector4(mesh->m_vecBones[k].vecKeyFrame[k].vTranslate.x,
										   mesh->m_vecBones[k].vecKeyFrame[k].vTranslate.y,
										   mesh->m_vecBones[k].vecKeyFrame[k].vTranslate.z, 0.f),
								   Vector4(mesh->m_vecBones[k].vecKeyFrame[k].vScale.x,
										   mesh->m_vecBones[k].vecKeyFrame[k].vScale.y,
										   mesh->m_vecBones[k].vecKeyFrame[k].vScale.z, 0.f)
					, mesh->m_vecBones[k].vecKeyFrame[k].qRot };
			}
		}

		mesh->m_pBoneOffset = new StructuredBuffer(eSBType::BoneOffset,
			eSRVTpye::BoneOffset,
			sizeof(Matrix),
			(UINT)vecOffset.size(),
			vecOffset.data(),
			gGraphicDevice->UnSafe_GetDevice());

		mesh->m_pBoneFrameData = new StructuredBuffer(eSBType::BoneFrameData,
			eSRVTpye::BoneFrameData,
			sizeof(tFrameTrans),
			(UINT)vecOffset.size() * iFrameCount,
			vecFrameTrans.data(),
			gGraphicDevice->UnSafe_GetDevice());
	}

	FBXLoadManager::GetInstance()->Release();
	return retmeshData;
}
