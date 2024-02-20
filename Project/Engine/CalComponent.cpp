#include "pch.h"
#include "CalComponent.h"
#include "ScriptComponentType.h"

#include "GameObject.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "TestComponent.h"

#include "TimeManager.h"

namespace engine
{
	CalComponent::CalComponent()
		: Script(eScriptType::CalComponent)
	{		
	}

	CalComponent::~CalComponent()
	{
	}

	void CalComponent::initialize()
	{
	}
	void CalComponent::update()
	{
		Transform* const trans = GetOwner()->GetComponent<Transform>();
		Vector3 vec = trans->GetPosition();
		vec.x += 0.5f * gDeltaTime;
		trans->SetPosition(vec);
	}
	void CalComponent::lateUpdate()
	{
	}
	void CalComponent::render()
	{
	}
}