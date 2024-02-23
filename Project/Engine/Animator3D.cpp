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

Animator3D::Animator3D()
	: Component(eComponentType::Animator3D)
	, mBones(nullptr)
	, m_pVecClip(nullptr)
	, m_vecClipUpdateTime()
	, m_vecFinalBoneMat()
	, m_iFrameCount(30)
	, m_dCurTime(0)
	, m_iCurClip(0)
	, mFrameIdx(0)
	, mNextFrameIdx(0)
	, mRatio(0)
	, m_bFinalMatUpdate(false)
	, mSBBoneFinalBuffer(nullptr)
	, mAnimMatrixCS(nullptr)
{
	mAnimMatrixCS = 
		static_cast<Anim3DBuuferCopyCS*>(gResourceManager->Find<ComputeShader>(L"Animation3DCS"));
	Assert(mAnimMatrixCS, ASSERT_MSG_NULL);

	mSBBoneFinalBuffer =
		new StructuredBuffer(16, 1, nullptr);
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

void Animator3D::SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip)
{
	m_pVecClip = _vecAnimClip;
	m_vecClipUpdateTime.resize(m_pVecClip->size());

	// 테스트 코드
	//static float fTime = 0.f;
	//fTime += 1.f;
	//m_vecClipUpdateTime[0] = fTime;

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

void Animator3D::lateUpdate()
{
	m_dCurTime = 0.f;
	// 현재 재생중인 Clip 의 시간을 진행한다.
	m_vecClipUpdateTime[m_iCurClip] += gDeltaTime;

	if (m_vecClipUpdateTime[m_iCurClip] >= m_pVecClip->at(m_iCurClip).dTimeLength)
	{
		m_vecClipUpdateTime[m_iCurClip] = 0.f;
	}

	m_dCurTime = m_pVecClip->at(m_iCurClip).dStartTime + m_vecClipUpdateTime[m_iCurClip];

	// 현재 프레임 인덱스 구하기
	double dFrameIdx = m_dCurTime * (double)m_iFrameCount;
	mFrameIdx = (int)(dFrameIdx);


	// 다음 프레임 인덱스
	if (mFrameIdx >= m_pVecClip->at(m_iCurClip).iFrameLength - 1)
	{
		mNextFrameIdx = mFrameIdx;	// 끝이면 현재 인덱스를 유지
	}		
	else
	{
		mNextFrameIdx = mFrameIdx + 1;
	}
		

	// 프레임간의 시간에 따른 비율을 구해준다.
	mRatio = (float)(dFrameIdx - (double)mFrameIdx);

	// 컴퓨트 쉐이더 연산여부
	m_bFinalMatUpdate = false;
}
