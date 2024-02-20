#pragma once
#include "Script.h"

namespace engine
{
	class CalComponent : public Script
	{
	public:
		CalComponent();
		virtual ~CalComponent();
		CalComponent(const CalComponent&) = delete;
		CalComponent& operator=(const CalComponent&) = delete;

	private:
		virtual void initialize() override;
		virtual void update() override;
		virtual void lateUpdate() override;
		virtual void render() override;
	};
}