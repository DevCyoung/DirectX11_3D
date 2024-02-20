#include "pch.h"
#include "AudioClip.h"
#include "String.h"

AudioClip::AudioClip()	
	: mSound(nullptr)
	, mChannel(nullptr)
	, mMinDistance(1.0f)
	, mMaxDistance(1000.0f)
	, mbLoop(false)
{

}

AudioClip::~AudioClip()
{
	//mSound->release();
	//mSound = nullptr;
}
//
HRESULT AudioClip::Load(const std::wstring& path)
{
	(void)path;
	//std::string cPath(path.begin(), path.end());

	std::string stringPath = helper::String::WStrToStr(path);


	if (!Fmod::CreateSound(stringPath, &mSound))
	{
		assert(false);
	}
		

	//mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
	
	

	return S_OK;
}


void AudioClip::Play()
{
	if (mbLoop)
		mSound->setMode(FMOD_LOOP_NORMAL);
	else
		mSound->setMode(FMOD_LOOP_OFF);

	//mSound->setMusicChannelVolume(mChannel, 0.5f);	
	//Sound->setMusicChannelVolume(0, 1000.f);
	//mSound->setMusicSpeed(100.f);
	//mChannel->setVolume(0.f);

	//mChannel->play
	//mChannel->setVolume(0.f);	

	Fmod::SoundPlay(mSound, &mChannel);

	//mChannel->setVolume(1.f);
}

void AudioClip::SetVolume(float volume)
{
	mChannel->setVolume(volume);
}

void AudioClip::SetPitch(float pitch)
{
	mChannel->setPitch(pitch);
}

float AudioClip::GetPitch() const
{
	float pitch = 0.f;
	mChannel->getPitch(&pitch);
	return pitch;
}

void AudioClip::SetSpeed(float speed)
{
	mChannel->setFrequency(speed);
}

void AudioClip::Stop()
{
	mChannel->stop();
}

void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
{
	FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
	FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

	mChannel->set3DAttributes(&fmodPos, &fmodVel);
}

