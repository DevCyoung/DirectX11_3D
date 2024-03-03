#include "pch.h"
#include "Animator3D.h"
#include "StructuredBuffer.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Anim3DBuuferCopyCS.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "EnumShaderBindStage.h"
#include "GameObject.h"
#include "StructuredBuffer.h"
#include "TimeManager.h"
#include "Animation3DController.h"
#include "Transform.h"

Animator3D::Animator3D()
	: Component(eComponentType::Animator3D)
	, mBones(nullptr)	
	, m_vecClipUpdateTime()
	, m_vecFinalBoneMat()
	, mFrameIdx(0)
	, mNextFrameIdx(0)
	, mRatio(0)
	, m_bFinalMatUpdate(false)
	, mSBBoneFinalBuffer(nullptr)
	, mAnimMatrixCS(nullptr)
	, mController(nullptr)
{
	mAnimMatrixCS = 
		static_cast<Anim3DBuuferCopyCS*>(gResourceManager->Find<ComputeShader>(L"Animation3DCS"));
	mSBBoneFinalBuffer = new StructuredBuffer(16, 1, nullptr);
}

Animator3D::~Animator3D()
{
	DELETE_POINTER(mSBBoneFinalBuffer);
}

Animator3D::Animator3D(const Animator3D& other)
	: Component(eComponentType::Animator3D)
{
	(void)other;
}

void Animator3D::UpdateData()
{	
	if (true)
	{		
		Mesh* pMesh = GetComponent<MeshRenderer>()->GetMesh();
		
		const UINT BONE_COUNT = GetBoneCount();
		if (mSBBoneFinalBuffer->GetElementCount() != BONE_COUNT)
		{
			DELETE_POINTER(mSBBoneFinalBuffer);			
			mSBBoneFinalBuffer = new StructuredBuffer( sizeof(Matrix), BONE_COUNT, nullptr);
		}		
	
		mAnimMatrixCS->SetFrameDataBuffer(pMesh->GetBoneFrameDataBuffer());
		mAnimMatrixCS->SetOffsetMatBuffer(pMesh->GetBoneOffsetBuffer());
		mAnimMatrixCS->SetOutputBuffer(mSBBoneFinalBuffer);

		mAnimMatrixCS->SetBoneCount(BONE_COUNT);
		mAnimMatrixCS->SetFrameIndex(mFrameIdx);
		mAnimMatrixCS->SetNextFrameIdx(mNextFrameIdx);
		mAnimMatrixCS->SetFrameRatio(mRatio);
		mAnimMatrixCS->UpdateData();

		gGraphicDevice->BindCS(mAnimMatrixCS);
		gGraphicDevice->Distpatch(mAnimMatrixCS);

		mAnimMatrixCS->Clear();
		m_bFinalMatUpdate = true;
	}

	gGraphicDevice->BindSB(30, mSBBoneFinalBuffer, eShaderBindType::VS);	
}

void Animator3D::ClearData()
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	UINT recentNum = 30;

	gGraphicDevice->UnSafe_Context()->VSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->HSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->DSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->GSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->PSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->CSSetShaderResources(recentNum, 1, &pSRV);

	UINT iMtrlCount = GetComponent<MeshRenderer>()->GetMaterialCount();
	Material* pMtrl = nullptr;
	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		pMtrl = GetComponent<MeshRenderer>()->GetMaterial(i);
		if (nullptr == pMtrl)
		{
			continue;
		}			
		
		pMtrl->SetAnim3D(false); // Animation Mesh 알리기
		pMtrl->SetBoneCount(0);
	}
}

void Animator3D::update()
{
}

//FIXME ComputeShader연산 항상하는것 고치기
void Animator3D::lateUpdate()
{
	// 컴퓨트 쉐이더 연산여부
	m_bFinalMatUpdate = false;
}

void Animator3D::Play(const std::wstring& animationName)
{
	(void)animationName;
}

void Animator3D::Play(const std::wstring& animationName, const float ratio)
{
	(void)animationName;
	(void)ratio;
}

Matrix Animator3D::GetCurGrameBoneMatrix(int boneIdx)
{
	Matrix worldMatrix = GetComponent<Transform>()->GetWorldMatrix();
	float ratio = GetRatio();
	Assert(boneIdx < mBones->size(), ASSERT_MSG_INVALID);
	const tMTBone& bone = mBones->at(boneIdx);
	tMTKeyFrame key = bone.vecKeyFrame[mFrameIdx];
	tMTKeyFrame nextKey = bone.vecKeyFrame[(mFrameIdx + 1) % bone.vecKeyFrame.size()];
	
	Quaternion qRot = Quaternion::Lerp(Quaternion(key.qRot), Quaternion(nextKey.qRot), ratio);
	Vector3 pos = Vector3::Lerp(key.vTranslate, nextKey.vTranslate, ratio);
	Vector3 scale = Vector3::Lerp(key.vScale, nextKey.vScale, ratio);

	Matrix scaleMatrix = Matrix::CreateScale(scale);
	Matrix rotationMatrix = XMMatrixRotationQuaternion(qRot);
	Matrix transMatrix = Matrix::CreateTranslation(pos);	
	worldMatrix = scaleMatrix * rotationMatrix * transMatrix * worldMatrix;
	return worldMatrix;
}
