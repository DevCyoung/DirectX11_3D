#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"
#include "EnumSRV.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Animator3D.h"
MeshRenderer::MeshRenderer()
	: RenderComponent(eComponentType::MeshRenderer)
{
	mMaterials.resize(sizeof(UINT));
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(const Camera* const camera)
{
	Assert(mMesh, ASSERT_MSG_NULL);
	//Assert(mMaterial, ASSERT_MSG_NULL);
	Assert(camera, ASSERT_MSG_NULL);
	
	tCBTransform CBTransform = {};
	{
		const Vector3& SCALE = Vector3(1, 1, 1.f);
		const Matrix& SCALE_MATRIX = Matrix::CreateScale(SCALE);

		const Matrix& WORD_MATRIX = GetComponent<Transform>()->GetWorldMatrix();
		CBTransform.World = SCALE_MATRIX * WORD_MATRIX;
		CBTransform.View = camera->GetView();
		CBTransform.Proj = camera->GetProjection();

		CBTransform.WV = CBTransform.World * CBTransform.View;
		CBTransform.WVP = CBTransform.WV * CBTransform.Proj;

		gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::PS);
	}
	//shader, Texture
	//GetMaterial()->UpdateData();

	Animator3D* const animator3D = GetComponentOrNull<Animator3D>();
	if (animator3D)
	{
		animator3D->UpdateData();

		for (UINT i = 0; i < mMaterials.size(); ++i)
		{
			if (nullptr == mMaterials[i])
			{
				continue;
			}

			UINT boneCount = animator3D->GetBoneCount();

			GetMaterial(i)->SetAnim3D(true); // Animation Mesh �˸���			
			GetMaterial(i)->SetBoneCount(boneCount);
		}
	}

	const UINT INDEX_COUNT = mMesh->GetIndexBufferCount();
	for (UINT i = 0; i < INDEX_COUNT; ++i)
	{
		GetMaterial(i)->UpdateData();
		gGraphicDevice->BindMesh(mMesh, i);
		gGraphicDevice->Draw(mMesh, i);
	}

	if (animator3D)
	{
		animator3D->ClearData();
	}

}
