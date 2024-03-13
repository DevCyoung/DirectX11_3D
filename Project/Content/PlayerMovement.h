#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PlayerMovement);

class Animation3DController;

class PlayerMovement : public ScriptComponent
{
public:
	PlayerMovement();
	virtual ~PlayerMovement();
	PlayerMovement(const PlayerMovement&) = delete;
	PlayerMovement& operator=(const PlayerMovement&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	Animation3DController* mController;
};
