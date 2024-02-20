#pragma once
#include "Component.h"
#include "AudioClip.h"

REGISTER_COMPONENT_TYPE(AudioSource);

class AudioSource : public Component
{
public:
	AudioSource();
	virtual ~AudioSource();
	AudioSource(const AudioSource&) = delete;
	AudioSource& operator=(const AudioSource&) = delete;

	void Play();
	void Stop();
	void SetLoop(bool loop);

	void SetClip(AudioClip* clip) { mAudioClip = clip; }
	AudioClip* GetClip() const { return mAudioClip; }

private:
	AudioClip* mAudioClip;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
