#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "ScriptComponent.h"
#include "EnumLayer.h"

GameObject::GameObject()
	: mEngineComponents{0, }
	, mScriptComponents()
	, mLayerType(eLayerType::Default)
	, mState(eState::Active)
	, mParent(nullptr)
	, mChildObjects()
	, mGameSystem(nullptr)
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	mem::del::DeleteVectorElements(&mScriptComponents);
	mem::del::DeletePointerArrayElements(&mEngineComponents);
	mem::del::DeleteVectorElements(&mChildObjects);
}

GameObject::GameObject(const GameObject& other)
	: mEngineComponents{0, }
	, mScriptComponents()
	, mLayerType(other.mLayerType)
	, mState(other.mState)
	, mParent(other.mParent)
	, mChildObjects()
	, mGameSystem(other.mGameSystem)
{
	//AddComponent<Transform>();

	for (const GameObject* obj : other.mChildObjects)
	{
		GameObject* copyObject = new GameObject(*obj);
		mChildObjects.push_back(copyObject);
	}

	for (UINT i = 0; i < static_cast<UINT>(eComponentType::End); i++)
	{
		if (other.mEngineComponents[i])
		{
			AddComponent(other.mEngineComponents[i]->Clone());			
		}
	}

	for (UINT i = 0; i < mScriptComponents.size(); i++)
	{
		AddComponent(other.mScriptComponents[i]->Clone());
	}
}

void GameObject::initialize()
{
	Assert(mGameSystem, ASSERT_MSG_NULL);

	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->initialize();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->initialize();
	}
}

void GameObject::update()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->update();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->update();
	}

	for (GameObject* childobj : mChildObjects)
	{
		childobj->update();
	}
}

void GameObject::fixedUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->fixedUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->fixedUpdate();
	}

	for (GameObject* childobj : mChildObjects)
	{
		childobj->fixedUpdate();
	}
}


void GameObject::lateUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->lateUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->lateUpdate();
	}

	for (GameObject* childobj : mChildObjects)
	{
		childobj->lateUpdate();
	}
}


void GameObject::lastUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->lastUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->lastUpdate();
	}

	for (GameObject* childobj : mChildObjects)
	{
		childobj->lastUpdate();
	}
}

GameObject* GameObject::FindChidOrNull(const std::wstring& name)
{
	GameObject* obj = nullptr;

	for (GameObject* child : mChildObjects)
	{
		if (child->GetName() == name)
		{
			obj = child;			
		}
		else
		{
			obj = obj->FindChidOrNull(name);
		}

		if (obj)
		{
			break;
		}
	}

	return obj;
}

GameObject* GameObject::FindChidOrNull(GameObject* childObj)
{
	GameObject* obj = nullptr;

	for (GameObject* child : mChildObjects)
	{
		if (child == childObj)
		{
			obj = child;
		}
		else
		{
			obj = child->FindChidOrNull(childObj);
		}

		if (obj)
		{
			break;
		}
	}

	return obj;
}

void GameObject::SetChild(GameObject* const childObj)
{	
	Assert(!FindChidOrNull(childObj), ASSERT_MSG_NOT_NULL);
	mChildObjects.push_back(childObj);
}

void GameObject::AddComponent(ScriptComponent* const scriptComponent)
{
	Assert(scriptComponent, ASSERT_MSG_NULL);
	Assert(!(scriptComponent->mOwner), ASSERT_MSG_NOT_NULL);
	Assert(!(GetComponentOrNull(scriptComponent->GetScriptType())), ASSERT_MSG_NOT_NULL);

	scriptComponent->mOwner = this;

	mScriptComponents.push_back(scriptComponent);
}

void GameObject::AddComponent(Component* const component)
{
	Assert(component, ASSERT_MSG_NULL);
	Assert(!(component->mOwner), ASSERT_MSG_NOT_NULL);

	component->mOwner = this;

	if (component->GetType() == eComponentType::ScriptComponent)
	{
		ScriptComponent* const scriptComponent = dynamic_cast<ScriptComponent*>(component);

		Assert(scriptComponent, ASSERT_MSG_NULL);

		AddComponent(scriptComponent);
	}
	else
	{
		Assert(!mEngineComponents[static_cast<UINT>(component->GetType())], ASSERT_MSG_NOT_NULL);

		mEngineComponents[static_cast<UINT>(component->GetType())] = component;
	}
}

Component* GameObject::GetComponentOrNull(const eComponentType componentType) const
{
	Assert(static_cast<UINT>(eComponentType::End) > static_cast<UINT>(componentType),
		ASSERT_MSG_INVALID);

	return mEngineComponents[static_cast<UINT>(componentType)];
}

ScriptComponent* GameObject::GetComponentOrNull(const eScriptComponentType scriptComponentType) const
{
	ScriptComponent* component = nullptr;

	for (ScriptComponent* const curScript : mScriptComponents)
	{
		if (curScript->GetScriptType() == scriptComponentType)
		{
			component = curScript;

			break;
		}
	}

	return component;

}

Component* GameObject::GetComponent(const eComponentType componentType) const
{
	Component* const component = GetComponentOrNull(componentType);

	Assert(component, ASSERT_MSG_NULL);

	return component;
}

ScriptComponent* GameObject::GetComponent(const eScriptComponentType scriptComponentType) const
{
	ScriptComponent* const scriptComponent = GetComponentOrNull(scriptComponentType);

	Assert(scriptComponent, ASSERT_MSG_NULL);

	return scriptComponent;
}
