#include "pch.h"
#include "AudioListener.h"
#include "Transform.h"
#include "Fmod.h"


AudioListener::AudioListener()
	: Component(eComponentType::AudioListener)
{
}

AudioListener::~AudioListener()
{
}

void AudioListener::initialize()
{
}

void AudioListener::update()
{
}

void AudioListener::lateUpdate()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector3 pos = tr->GetWorldMatrix().Translation();
	Vector3 foward = tr->GetForward();
	Vector3 up = tr->GetUp();

	Vector3 vel = { 0.0f, 0.0f, 0.0f };
	//Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
}
