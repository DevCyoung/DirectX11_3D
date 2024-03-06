#include "pch.h"
#include "ThirdPersonOrbitCam.h"
#include <Engine/SceneManager.h>

ThirdPersonOrbitCam::ThirdPersonOrbitCam()
	: ScriptComponent(eScriptComponentType::ThirdPersonOrbitCam)
	, mPlayer(nullptr)
	, mCameraTransform(nullptr)
	, mMyCamera(nullptr)
	, mPivotOffset(0.0f, 1.0f, 0.0f)
	, mCamOffset(0.4f, 0.5f, -2.0f)
	, mSmooth(10.f)
	, mHorizontalAimingSpeed(6.0f)
	, mVertialAimingSpeed(6.0f)
	, mMaxVertialAngle(30.f)
	, mMinVertialAngle(-60.f)
	, mRecoilAngleBounce(5.0f)
	, mAngleH(0.f)
	, mAngleV(0.f)
	, mRelCameraPos(Vector3::Zero)
	, mRelCameraPosMag(0.f)
	, mSmoothPivotOffset(Vector3::Zero)
	, mSmoothCamOffset(Vector3::Zero)
	, mTargetPivotOffset(Vector3::Zero)
	, mTargetCamOffset(Vector3::Zero)
	, mDefaultFOV(0.f)
	, mTargetFOV(0.f)
	, mTargetMaxVertialAngle(0.f)
	, mRecoilAngle(0.f)
{
}

ThirdPersonOrbitCam::~ThirdPersonOrbitCam()
{
}

void ThirdPersonOrbitCam::initialize()
{
	mMyCamera = GetComponent<Camera>();
	mCameraTransform = GetComponent<Transform>();

	//Vector3 camPosition = mPlayer->GetPosition();
	//camPosition += Quaternion::Identity * mPivotOffset + Quaternion::Identity * mCamOffset;
	//
	////카메라의 플레이어간의 상대 벡터, 충돌체크에 사용하기 위함
	//mRelCameraPos = mCameraTransform->GetPosition() - mPlayer->GetPosition();
	//mRelCameraPosMag = mRelCameraPos.Length() - 0.5f;
	//
	////기본 셋팅
	//mSmoothPivotOffset = mPivotOffset;
}

void ThirdPersonOrbitCam::update()
{	
}

void ThirdPersonOrbitCam::lateUpdate()
{
}
