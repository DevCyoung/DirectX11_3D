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

	void AddAnimator3D(Animator3D* animator3D) { mAnimation3Ds.push_back(animator3D); }
	void Play(const std::wstring& animation);

	const std::vector<Animator3D*>& GetAnimation3Ds() { return mAnimation3Ds; };
	virtual void update();

	void SetBones(std::vector<tMTBone>* bones) { mBones = bones; }
	void SetClip(std::vector<tMTAnimClip>* clip) { m_pVecClip = clip; }

	std::vector<Animator3D*>	mAnimation3Ds;
	std::vector<tMTBone>*		mBones;
	std::vector<tMTAnimClip>*	m_pVecClip;

	CLONE(Animation3DController);
};

