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
    void SetBones(std::vector<tMTBone> _vecBones) { mBones = _vecBones; }
    StructuredBuffer* GetFinalBoneMat() { return mSBBoneFinalBuffer; }
    UINT GetBoneCount() { return static_cast<UINT>(mBones.size()); }

    void ClearData();
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;

    void Play(const std::wstring& animationName);
    void Play(const std::wstring& animationName, const float ratio);
    float GetRatio() { return mRatio; }
    void SetController(Animation3DController* const controller) { mController = controller; }
    Animation3DController* GetController() { return mController; }
    Matrix GetCurGrameBoneMatrix(int boneIdx);
    const std::vector<tMTBone>& GetBones() { return mBones; }

    virtual void Save(FILE* const file) override;
    virtual void Load(FILE* const file) override;
private:
    void setCurrentFrame(int frameIde, int nextFrameIdx, float ratio)
    {
        mFrameIdx = frameIde;
        mNextFrameIdx = nextFrameIdx;
        mRatio = ratio;
    }
public:
    std::vector<tMTBone>            mBones;        
    int							    mFrameIdx;              // Ŭ���� ���� ������
    int							    mNextFrameIdx;          // Ŭ���� ���� ������
    float						    mRatio;	                // ������ ���� ����    
    bool						    m_bFinalMatUpdate;      // ������� ���� ���࿩��

    Animation3DController*          mController;
    StructuredBuffer*               mSBBoneFinalBuffer;     // Ư�� �������� ���� ���
    Anim3DBuuferCopyCS*             mAnimMatrixCS;
};

