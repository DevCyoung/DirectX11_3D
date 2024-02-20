#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE($safeitemname$);

class $safeitemname$ : public Component
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
	virtual void render() override final;

};
