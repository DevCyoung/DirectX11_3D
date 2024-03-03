#pragma once
#include "Component.h"
#include "Animator3D.h"
REGISTER_COMPONENT_TYPE(Animation3DController);

//class Animator3D;

class Animation3DController : public Component
{
public:
	Animation3DController();
	virtual ~Animation3DController();
	//Animation3DController(const Animation3DController&);
	Animation3DController& operator=(const Animation3DController&) = delete;

	void AddAnimator3D(Animator3D* animator3D)
	{
		animator3D->SetController(this);
		mAnimation3Ds.push_back(animator3D);
	}

	void Play(const std::wstring& animation);
	void Play(const std::wstring& animation, float ratio);

	const std::vector<Animator3D*>& GetAnimation3Ds() { return mAnimation3Ds; };
	virtual void update();
	virtual void lateUpdate();

	void SetBones(std::vector<tMTBone>* bones) { mBones = bones; }
	void SetClips(std::vector<tMTAnimClip>* clip) { m_pVecClip = clip; }
	void SetClip(int clipIdx) { m_iCurClip = clipIdx; }
	void Stop(bool stop) { mbStop = stop; }
	bool IsStop() { return mbStop; }
	int GetCurFrameIdx() { return mFrameIdx; }
	void SetCurFrameIde(int frameIdx) { mFrameIdx = frameIdx; }
	void SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip);

	void RemoveClip(const std::wstring& clipName);
	void CreateClip(const std::wstring& clipName, int startFrame, int endFrame);

	std::vector<tMTAnimClip>* GetAnimationClip() { return m_pVecClip; }

	std::vector<Animator3D*>	mAnimation3Ds;
	std::vector<tMTBone>*		mBones;
	std::vector<tMTAnimClip>*	m_pVecClip;

	bool						mbStop;
	int							m_iFrameCount;
	int							m_iCurClip;
	int							mFrameIdx;
	int							mNextFrameIdx;
	float						m_dCurTime;
	float						mRatio;	
	std::vector<float>			m_vecClipUpdateTime;


	CLONE(Animation3DController);
};

