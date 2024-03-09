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
	float mSmooth;					//ī�޶� �����ӵ�
	float mHorizontalAimingSpeed;	//���� ȸ���ӵ�
	float mVertialAimingSpeed;		// ���� ȸ���ӵ�
	float mMaxVertialAngle;			//ī�޶��� ���� �ִ�	����
	float mMinVertialAngle;			//ī�޶��� ���� �ּ� ����
	float mRecoilAngleBounce;
	float mAngleH;					//���콺 �̵��� ���� ī�޶� �����̵� ��ġ
	float mAngleV;					//���콺 �̵��� ���� ī�޶� �����̵� ��ġ
	Vector3 mRelCameraPos;			//�÷��̾�κ��� ī�޶������ ����
	float mRelCameraPosMag;			//�÷��̾�κ��� ī�޶������ �Ÿ�
	Vector3 mSmoothPivotOffset;		//ī�޶� �Ǻ��� ������ ����
	Vector3 mSmoothCamOffset;		//ī�޶� ��ġ�� ������ ����
	Vector3 mTargetPivotOffset;		//ī�޶� �Ǻ��� ������ ����
	Vector3 mTargetCamOffset;		//ī�޶� ��ġ�� ������ ����
	float mDefaultFOV;				//�⺻ �þ߰�
	float mTargetFOV;				//Ÿ�� �þ߰�
	float mTargetMaxVertialAngle;	//ī�޶� ���� �ִ� ����
	float mRecoilAngle;				//��� �ݵ�����
	
};

