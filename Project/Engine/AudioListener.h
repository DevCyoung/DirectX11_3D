#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(AudioListener);

class AudioListener : public Component
{
public:
	AudioListener();
	virtual ~AudioListener();
	AudioListener(const AudioListener&) = delete;
	AudioListener& operator=(const AudioListener&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
