#include "pch.h"
#include "AudioSource.h"
#include "Transform.h"


AudioSource::AudioSource()
	: Component(eComponentType::AudioSource)
	, mAudioClip(nullptr)
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::Play()
{
	mAudioClip->Play();
}

void AudioSource::Stop()
{
	mAudioClip->Stop();
}

void AudioSource::SetLoop(bool loop)
{
	mAudioClip->SetLoop(loop);
}

void AudioSource::initialize()
{
}

void AudioSource::update()
{
}

void AudioSource::lateUpdate()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector3 pos = tr->GetWorldMatrix().Translation();
	Vector3 foward = tr->GetForward();

	//mAudioClip->Set3DAttributes(pos, foward);
}
