#pragma once

#include "Resource.h"
#include "Fmod.h"

class AudioClip : public Resource
{
public:
	AudioClip();
	~AudioClip();

	//virtual HRESULT Load(const std::wstring& path) override;
	virtual HRESULT Load(const std::wstring& filePath) override;

	void Play();
	void SetVolume(float volume);
	void SetPitch(float pitch) ;
	float GetPitch() const;
	void SetSpeed(float speed);

	void Stop();
	void Set3DAttributes(const Vector3 pos, const Vector3 vel);
	void SetLoop(bool loop) { mbLoop = loop; }

private:
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;
	float mMinDistance;
	float mMaxDistance;
	bool mbLoop;	
};