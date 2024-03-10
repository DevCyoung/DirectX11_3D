#include "pch.h"
#include "Animation3DController.h"
#include "Animator3D.h"
#include "TimeManager.h"
#include <Helper/FileHelper.h>
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
	if (!mbStop && !m_vecClipUpdateTime.empty())
	{
		m_vecClipUpdateTime[m_iCurClip] += gDeltaTime;
		int timelength = mAnimClips[m_iCurClip].iEndFrame - mAnimClips[m_iCurClip].iStartFrame;
		if (m_vecClipUpdateTime[m_iCurClip] >= (float)timelength / m_iFrameCount)
		{
			m_vecClipUpdateTime[m_iCurClip] = 0.f;
		}

		float startTime = (float)mAnimClips[m_iCurClip].iStartFrame / m_iFrameCount;
		m_dCurTime = startTime + m_vecClipUpdateTime[m_iCurClip];

		// 현재 프레임 인덱스 구하기
		double dFrameIdx = m_dCurTime * (double)m_iFrameCount;
		mFrameIdx = (int)(dFrameIdx);

		// 다음 프레임 인덱스
		if (mFrameIdx >= mAnimClips[m_iCurClip].iEndFrame)
		{
			mNextFrameIdx = mAnimClips[m_iCurClip].iStartFrame;	// 끝이면 현재 인덱스를 유지
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
	if (mAnimClips.size() <= 1)
	{
		return;
	}

	std::vector<tMTAnimClip>::iterator iter = mAnimClips.begin();

	for (; iter != mAnimClips.end(); ++iter)
	{
		if (iter->strAnimName == clipName)
		{
			mAnimClips.erase(iter);
		}
	}

	m_iCurClip = 0;
}

void Animation3DController::CreateClip(const std::wstring& clipName, int startFrame, int endFrame)
{
	std::vector<tMTAnimClip>::iterator iter = mAnimClips.begin();

	for (; iter != mAnimClips.end(); ++iter)
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
	mAnimClips.push_back(clip);
	SetAnimClip(mAnimClips);
}

void Animation3DController::lateUpdate()
{
}

void Animation3DController::SetAnimClip(std::vector<tMTAnimClip> _vecAnimClip)
{
	mAnimClips = _vecAnimClip;
	m_vecClipUpdateTime.resize(mAnimClips.size());
}

void Animation3DController::Save(FILE* const file)
{
	Component::Save(file);

	UINT animClipCount = static_cast<UINT>(mAnimClips.size());
	fwrite(&animClipCount, sizeof(animClipCount), 1, file);

	for (UINT i = 0; i < animClipCount; ++i)
	{
		const tMTAnimClip& clip = mAnimClips[i];
		SaveWString(clip.strAnimName, file);
		fwrite(&clip.iStartFrame, sizeof(clip.iStartFrame), 1, file);
		fwrite(&clip.iEndFrame, sizeof(clip.iEndFrame), 1, file);
		fwrite(&clip.iFrameLength, sizeof(clip.iFrameLength), 1, file);
		fwrite(&clip.dStartTime, sizeof(clip.dStartTime), 1, file);
		fwrite(&clip.dEndTime, sizeof(clip.dEndTime), 1, file);
		fwrite(&clip.dTimeLength, sizeof(clip.dTimeLength), 1, file);
		fwrite(&clip.fUpdateTime, sizeof(clip.fUpdateTime), 1, file);		
		fwrite(&clip.eMode, sizeof(clip.eMode), 1, file);
	}
}

void Animation3DController::Load(FILE* const file)
{
	Component::Load(file);

	UINT animClipCount = 0;
	fread(&animClipCount, sizeof(animClipCount), 1, file);

	mAnimClips.reserve(animClipCount);
	for (UINT i = 0; i < animClipCount; ++i)
	{
		tMTAnimClip clip = {};
		LoadWString(&clip.strAnimName, file);
		fread(&clip.iStartFrame, sizeof(clip.iStartFrame), 1, file);
		fread(&clip.iEndFrame, sizeof(clip.iEndFrame), 1, file);
		fread(&clip.iFrameLength, sizeof(clip.iFrameLength), 1, file);
		fread(&clip.dStartTime, sizeof(clip.dStartTime), 1, file);
		fread(&clip.dEndTime, sizeof(clip.dEndTime), 1, file);
		fread(&clip.dTimeLength, sizeof(clip.dTimeLength), 1, file);
		fread(&clip.fUpdateTime, sizeof(clip.fUpdateTime), 1, file);
		fread(&clip.eMode, sizeof(clip.eMode), 1, file);
		mAnimClips.push_back(clip);
	}

	m_vecClipUpdateTime.clear();
	m_vecClipUpdateTime.resize(animClipCount);
}