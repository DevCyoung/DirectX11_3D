#include "pch.h"
#include "ThirdPersonOrbitCam.h"
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>

ThirdPersonOrbitCam::ThirdPersonOrbitCam()
	: ScriptComponent(eScriptComponentType::ThirdPersonOrbitCam)
	, mPlayerTransform(nullptr)
	, mCameraTransform(nullptr)
	, mMyCamera(nullptr)
	, mPivotOffset(0.0f, 100.0f, -130.0f)
	, mCamOffset(10.0f, 43.0f, -91.0f)
	, mSmooth(10.f)
	, mHorizontalAimingSpeed(150.0f)
	, mVertialAimingSpeed(150.0f)
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

	GameObject* playerObj = gCurrentScene->FindGameObjectOrNull(L"Player");
	if (playerObj)
	{
		mPlayerTransform = playerObj->GetComponent<Transform>();

		//카메라 기본포지션 셋팅
		Vector3 camPosition = mPlayerTransform->GetPosition();
		camPosition += Quaternion::Identity * mPivotOffset + Quaternion::Identity * mCamOffset;
		mPlayerTransform->SetPosition(camPosition);
	}

	////카메라의 플레이어간의 상대 벡터, 충돌체크에 사용하기 위함
	//mRelCameraPos = mCameraTransform->GetPosition() - mPlayer->GetPosition();
	//mRelCameraPosMag = mRelCameraPos.Length() - 0.5f;
	//
	//기본 셋팅
	//mSmoothPivotOffset = mPivotOffset;

	mSmoothPivotOffset = mPivotOffset;
	mSmoothCamOffset = mCamOffset;	
}

void ThirdPersonOrbitCam::update()
{
}

void ThirdPersonOrbitCam::lateUpdate()
{
	Vector2 mouseDir = gInput->GetMouseDir();
	mouseDir.Normalize();

	mAngleH += mouseDir.x * gDeltaTime * mHorizontalAimingSpeed;
	mAngleV += mouseDir.y * gDeltaTime * mVertialAimingSpeed;
	mAngleV = std::clamp(mAngleV, mMinVertialAngle, mMaxVertialAngle);
	mAngleV = std::lerp(mAngleV, mAngleV + mRecoilAngle, 10.f * gDeltaTime);

	Quaternion camYRotation = helper::math::QuaternionEuler(0.0f, mAngleH, 0.0f);
	Quaternion aimRotation = helper::math::QuaternionEuler(-mAngleV, mAngleH, 0.0f); //vertial 은 반대이다.
	Matrix aimRotationMatrix = XMMatrixRotationQuaternion(aimRotation);
	Matrix camYRotationMatrix = XMMatrixRotationQuaternion(camYRotation);
	//Vector3 p1 = XMVector3TransformCoord(mSmoothPivotOffset, camYRotationMatrix);
	//Vector3 p2 = XMVector3TransformCoord(mSmoothCamOffset, aimRotationMatrix);
	Vector3 p1 = XMVector3TransformCoord(mPivotOffset, camYRotationMatrix);
	Vector3 p2 = XMVector3TransformCoord(mCamOffset, aimRotationMatrix);

	Vector3 cameraPosition = mPlayerTransform->GetPosition();
	cameraPosition += p1 + p2;
	mCameraTransform->SetPosition(cameraPosition);
	mCameraTransform->CalculateTransform();
	gCurrentSceneRenderer->GetDebugRenderer2D()->DrawCube3D(mCameraTransform->GetWorldMatrix(), 0.f);
	mCameraTransform->CalculateTransform(aimRotationMatrix);
	mMyCamera->CalculateCamera();
}

void ThirdPersonOrbitCam::Save(FILE* file)
{
	fwrite(&mPivotOffset, sizeof(mPivotOffset), 1, file);
	fwrite(&mCamOffset, sizeof(mCamOffset), 1, file);
}

void ThirdPersonOrbitCam::Load(FILE* file)
{
	(void)file;
	fread(&mPivotOffset, sizeof(mPivotOffset), 1, file);
	fread(&mCamOffset, sizeof(mCamOffset), 1, file);
}
