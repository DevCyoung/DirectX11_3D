#include "pch.h"
#include "ThirdPersonOrbitCam.h"
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>

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

	Vector3 camPosition = mCameraTransform->GetPosition();
	camPosition += Quaternion::Identity * mPivotOffset + Quaternion::Identity * mCamOffset;
	camPosition = Vector3::One * Quaternion::Identity;
	Quaternion q = Quaternion::CreateFromYawPitchRoll(Vector3(0.f, 3.14f, 0.f));
	q = helper::math::QuaternionEuler(0.f, 3.14f, 0.f);
	q = helper::math::QuaternionEuler(30.f, 90.f, 30.f);
	
	(void)q;
	

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
	Vector2 mouseDir = gInput->GetMouseDir();
	mouseDir.Normalize();

	mAngleH += mouseDir.x * gDeltaTime * 100.f;
	mAngleV += mouseDir.y * gDeltaTime * 100.f;
	
	Quaternion camYRotation = helper::math::QuaternionEuler(0.0f, mAngleH, 0.0f);
	Quaternion aimRotation = helper::math::QuaternionEuler(-mAngleV, mAngleH, 0.0f);

	//rotation 강제계산
	Matrix rotation = XMMatrixRotationQuaternion(aimRotation);
	//카메라 회전적용
	mCameraTransform->CalculateTransform(rotation);
	mMyCamera->CalculateCamera();
}
