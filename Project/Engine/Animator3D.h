#pragma once
#include "Component.h"
#include "FBXLoader.h"

REGISTER_COMPONENT_TYPE(Animator3D);

class StructuredBuffer;
class Mesh;
class Anim3DBuuferCopyCS;
class Animation3DController;

class Animator3D : public Component
{

public:
    friend class Animation3DController;
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

    //void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }    
    ////const std::vector<tMTAnimClip>* GetAnimationClip() const { return m_pVecClip; }
    //
    //int GetStartFrame(int idx) { return m_pVecClip->at(idx).iStartFrame; }
    //void SetStartFrame(int idx, int startFrame) { m_pVecClip->at(idx).iStartFrame = startFrame; }
    //
    //int GetEndFrame(int idx) { return m_pVecClip->at(idx).iEndFrame; }
    //void SetEndFrame(int idx, int endFrame) { m_pVecClip->at(idx).iEndFrame = endFrame; }

    void ClearData();
    virtual void update() override;
    virtual void lateUpdate() override;

    void Play(const std::wstring& animationName);
    void Play(const std::wstring& animationName, const float ratio);

    float GetRatio() { return mRatio; }

    //int GetCurFrameIdx() { return mFrameIdx; }
    void SetController(Animation3DController* const controller) { mController = controller; }
    Animation3DController* GetController() { return mController; }
    Matrix GetCurGrameBoneMatrix(int boneIdx);
    const std::vector<tMTBone>* GetBones() { return mBones; }

private:
    void setCurrentFrame(int frameIde, int nextFrameIdx, float ratio)
    {
        mFrameIdx = frameIde;
        mNextFrameIdx = nextFrameIdx;
        mRatio = ratio;
    }
public:
    std::vector<tMTBone>*           mBones;
    //std::vector<tMTAnimClip>*       m_pVecClip;

    std::vector<float>				m_vecClipUpdateTime;
    std::vector<Matrix>				m_vecFinalBoneMat;      // �ؽ��Ŀ� ������ ���� �������
    //int							    m_iFrameCount;          // 30
    //int							    m_iCurClip;             // Ŭ�� �ε���	
    int							    mFrameIdx;              // Ŭ���� ���� ������
    int							    mNextFrameIdx;          // Ŭ���� ���� ������
    float						    mRatio;	                // ������ ���� ����
    //double						    m_dCurTime;
    bool						    m_bFinalMatUpdate;      // ������� ���� ���࿩��

    StructuredBuffer*               mSBBoneFinalBuffer;     // Ư�� �������� ���� ���
    Anim3DBuuferCopyCS*             mAnimMatrixCS;

    Animation3DController*          mController;
};

