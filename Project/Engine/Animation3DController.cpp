#include "pch.h"
#include "Animation3DController.h"
#include "Animator3D.h"
#include "TimeManager.h"
//WALK_A  134  223
//WALK_B  225  314
//Attack1  498  619

Animation3DController::Animation3DController()
	: Component(eComponentType::Animation3DController)
	, mbStop(false)
	, m_iFrameCount(30)
	, m_iCurClip(0)
	, mFrameIdx(0)
	, mNextFrameIdx(0)
	, m_dCurTime(0)
	, mRatio(0)	
	, m_vecClipUpdateTime()
{
}

Animation3DController::~Animation3DController()
{
}

void Animation3DController::Play(const std::wstring& animation)
{
	for (Animator3D* animator3D : mAnimation3Ds)
	{
		animator3D->Play(animation);
	}
}

void Animation3DController::Play(const std::wstring& animation, float ratio)
{
	//이전의 애니메이션과 블렌딩한다.
	for (Animator3D* animator3D : mAnimation3Ds)
	{
		animator3D->Play(animation, ratio);
	}
}

void Animation3DController::update()
{
	m_dCurTime = 0.f;

	// 현재 재생중인 Clip 의 시간을 진행한다.
	if (!mbStop)
	{
		m_vecClipUpdateTime[m_iCurClip] += gDeltaTime;
		int timelength = m_pVecClip->at(m_iCurClip).iEndFrame - m_pVecClip->at(m_iCurClip).iStartFrame;
		if (m_vecClipUpdateTime[m_iCurClip] >= (float)timelength / m_iFrameCount)
		{
			m_vecClipUpdateTime[m_iCurClip] = 0.f;
		}

		float startTime = (float)m_pVecClip->at(m_iCurClip).iStartFrame / m_iFrameCount;
		m_dCurTime = startTime + m_vecClipUpdateTime[m_iCurClip];

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
	}

	for (Animator3D* animator3D : mAnimation3Ds)
	{
		animator3D->setCurrentFrame(mFrameIdx, mNextFrameIdx, mRatio);
	}
}

void Animation3DController::RemoveClip(const std::wstring& clipName)
{
	if (m_pVecClip->size() <= 1)
	{
		return;
	}

	std::vector<tMTAnimClip>::iterator iter = m_pVecClip->begin();

	for (; iter != m_pVecClip->end(); ++iter)
	{
		if (iter->strAnimName == clipName)
		{
			m_pVecClip->erase(iter);
		}
	}

	m_iCurClip = 0;
}

void Animation3DController::CreateClip(const std::wstring& clipName, int startFrame, int endFrame)
{
	std::vector<tMTAnimClip>::iterator iter = m_pVecClip->begin();

	for (; iter != m_pVecClip->end(); ++iter)
	{
		if (iter->strAnimName == clipName)
		{			
			return;
		}
	}

	tMTAnimClip clip = {};
	clip.iStartFrame = startFrame;
	clip.iEndFrame = endFrame;
	clip.strAnimName = clipName;
	m_pVecClip->push_back(clip);
	SetAnimClip(m_pVecClip);
}


void Animation3DController::lateUpdate()
{
}

void Animation3DController::SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip)
{
	m_pVecClip = _vecAnimClip;
	m_vecClipUpdateTime.resize(m_pVecClip->size());
}
