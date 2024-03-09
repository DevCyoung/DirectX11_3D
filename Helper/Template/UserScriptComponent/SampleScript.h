#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE($safeitemname$);

class $safeitemname$ : public ScriptComponent
{
public:
	$safeitemname$();
	virtual ~$safeitemname$();
	$safeitemname$(const $safeitemname$&) = delete;
	$safeitemname$& operator=(const $safeitemname$&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
};
