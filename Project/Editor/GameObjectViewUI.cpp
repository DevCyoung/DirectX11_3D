#include "pch.h"
#include "GameObjectViewUI.h"
#include <Engine/SceneManager.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"

GameObjectViewUI::GameObjectViewUI()
	:mSelectedGameObject(nullptr)
{
}

GameObjectViewUI::~GameObjectViewUI()
{
}

void GameObjectViewUI::update()
{
}

void GameObjectViewUI::popUpView(GameObject* const gameObject)
{
	const std::vector<GameObject*>& childObjects = gameObject->GetChildObjects();

	std::string itemName = StringHelper::WStrToStr(gameObject->GetName());
	UINT id = gameObject->GetID();
	itemName += "##";
	itemName += std::to_string(id);

	if (childObjects.empty())
	{
		ImGui::Bullet();
		if (ImGui::Selectable(itemName.c_str(), false))
		{	
			mSelectedGameObject = gameObject;
		}
		popEvent(gameObject);
	}
	else
	{
		if (ImGui::TreeNodeEx(itemName.c_str()))
		{
			if (ImGui::IsItemClicked())
			{
				mSelectedGameObject = gameObject;
			}
			popEvent(gameObject);
			for (GameObject* childObj : childObjects)
			{
				popUpView(childObj);
			}
			ImGui::TreePop();
		}
	}
}

void GameObjectViewUI::popEvent(GameObject* const gameObject)
{
	std::string name = StringHelper::WStrToStr(gameObject->GetName());

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("GAMEOBJECT", &gameObject, sizeof(gameObject));
		ImGui::Text("%s", name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT");
		if (payload)
		{
			GameObject* resObject = *(GameObject**)payload->Data; 			
			gameObject->SetChild(resObject);			
		}		
		ImGui::EndDragDropTarget();
	}
	if (ImGui::BeginPopupContextItem())
	{
		ImGui::Text("%s", name.c_str());
		if (ImGui::Button("Remove"))
		{
			gCurrentScene->RegisterEventSetDestroy(gameObject);
			PanelUI* inspectorUI = PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI");
			GameObject* obj = nullptr;
			static_cast<InspectorUI*>(inspectorUI)->Register(obj);
		}
		if (ImGui::Button("Detatch"))
		{
			gameObject->SetParent(nullptr);
		}
		ImGui::EndPopup();
	}
}

void GameObjectViewUI::drawForm()
{
	mSelectedGameObject = nullptr;
	Scene* curScene = SceneManager::GetInstance()->GetCurrentScene();
	InspectorUI* inspectorUI =
		static_cast<InspectorUI*>(PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI"));
	ImGui::Begin("GameObjectViewUI");
	for (UINT i = 0; i < static_cast<UINT>(eLayerType::End); ++i)
	{
		Layer& layer = curScene->GetLayer(static_cast<eLayerType>(i));
		std::vector<GameObject*>& gameObjects = layer.GetGameObjects();
		for (GameObject* gameObject : gameObjects)
		{
			popUpView(gameObject);
		}
	}
	if (mSelectedGameObject)
	{
		inspectorUI->Register(mSelectedGameObject);
	}
	ImGui::End();
}
