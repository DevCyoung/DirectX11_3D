#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "Components.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ThirdPersonOrbitCam);

class ThirdPersonOrbitCam : public ScriptComponent
{
public:
	ThirdPersonOrbitCam();
	virtual ~ThirdPersonOrbitCam();
	//CameraInputMoveMent(const CameraInputMoveMent&) = delete;
	ThirdPersonOrbitCam& operator=(const ThirdPersonOrbitCam&) = delete;	
	CLONE(ThirdPersonOrbitCam);

	//void SetPlayerTransform(Transform* playerTransform)


	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

public:
	Transform*	mPlayerTransform;
	Transform*	mCameraTransform;
	Camera*		mMyCamera;
	Vector3		mPivotOffset;
	Vector3		mCamOffset;
	float mSmooth;					//카메라 반응속도
	float mHorizontalAimingSpeed;	//수평 회전속도
	float mVertialAimingSpeed;		// 수직 회전속도
	float mMaxVertialAngle;			//카메라의 수직 최대	각도
	float mMinVertialAngle;			//카메라의 수직 최소 각도
	float mRecoilAngleBounce;
	float mAngleH;					//마우스 이동에 따른 카메라 수평이동 수치
	float mAngleV;					//마우스 이동에 따른 카메라 수직이동 수치
	Vector3 mRelCameraPos;			//플레이어로부터 카메라까지의 벡터
	float mRelCameraPosMag;			//플레이어로부터 카메라사이의 거리
	Vector3 mSmoothPivotOffset;		//카메라 피봇용 보간용 벡터
	Vector3 mSmoothCamOffset;		//카메라 위치용 보간용 벡터
	Vector3 mTargetPivotOffset;		//카메라 피봇용 보간용 벡터
	Vector3 mTargetCamOffset;		//카메라 위치용 보간용 벡터
	float mDefaultFOV;				//기본 시야값
	float mTargetFOV;				//타겟 시야값
	float mTargetMaxVertialAngle;	//카메라 수직 최대 각도
	float mRecoilAngle;				//사격 반동각도
	
};

