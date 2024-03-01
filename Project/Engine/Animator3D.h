#pragma once
#include "Component.h"
#include "FBXLoader.h"

REGISTER_COMPONENT_TYPE(Animator3D);

class StructuredBuffer;
class Mesh;
class Anim3DBuuferCopyCS;

class Animator3D : public Component
{
public:
	Animator3D();
	virtual ~Animator3D();
	Animator3D(const Animator3D& other);
	Animator3D& operator=(const Animator3D&) = delete;

    void UpdateData();

public:
    void SetBones(std::vector<tMTBone>*_vecBones) 
    { 
        mBones = _vecBones; 
        m_vecFinalBoneMat.resize(mBones->size()); 
    }
    StructuredBuffer* GetFinalBoneMat() { return mSBBoneFinalBuffer; }
    UINT GetBoneCount() { return static_cast<UINT>(mBones->size()); }

    int GetClipID() { return m_iCurClip; }
    void SetClipID(int clipID) { m_iCurClip = clipID; }

    void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }
    void SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip);
    const std::vector<tMTAnimClip>* GetAnimationClip() const { return m_pVecClip; }

    int GetStartFrame(int idx) { return m_pVecClip->at(idx).iStartFrame; }
    void SetStartFrame(int idx, int startFrame) { m_pVecClip->at(idx).iStartFrame = startFrame; }

    int GetEndFrame(int idx) { return m_pVecClip->at(idx).iEndFrame; }
    void SetEndFrame(int idx, int endFrame) { m_pVecClip->at(idx).iEndFrame = endFrame; }

    void ClearData();
    virtual void update() override;
    virtual void lateUpdate() override;

    void Play(const std::wstring& animationName);

public:
    std::vector<tMTBone>*           mBones;
    std::vector<tMTAnimClip>*       m_pVecClip;

    std::vector<float>				m_vecClipUpdateTime;
    std::vector<Matrix>				m_vecFinalBoneMat;      // �ؽ��Ŀ� ������ ���� �������
    int							    m_iFrameCount;          // 30
    int							    m_iCurClip;             // Ŭ�� �ε���	
    int							    mFrameIdx;            // Ŭ���� ���� ������
    int							    mNextFrameIdx;        // Ŭ���� ���� ������
    float						    mRatio;	            // ������ ���� ����
    double						    m_dCurTime;
    bool						    m_bFinalMatUpdate;      // ������� ���� ���࿩��

    StructuredBuffer*               mSBBoneFinalBuffer;  // Ư�� �������� ���� ���
    Anim3DBuuferCopyCS*             mAnimMatrixCS;
};

