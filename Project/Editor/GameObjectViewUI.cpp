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

void GameObjectViewUI::popUpView(GameObject* gameObject)
{		
	const std::vector<GameObject*>& childObjects = gameObject->GetChildObjects();

	std::string itemName = std::string(gameObject->GetName().begin(), gameObject->GetName().end());
	UINT id = gameObject->GetID();
	itemName += "##";
	itemName += std::to_string(id);

	if (!childObjects.empty())
	{		
		if (ImGui::TreeNode(itemName.c_str()))
		{
			if (ImGui::IsItemClicked())
			{
				//ImGui::SetMouseCursor(0);
				mSelectedGameObject = gameObject;
			}

			for (GameObject* childObj : childObjects)
			{
				popUpView(childObj);
			}

			popEvent(gameObject);
			ImGui::TreePop();
		}
	}	
	else
	{
		ImGui::Bullet();
		if (ImGui::Selectable(itemName.c_str(), false))
		{
			//ImGui::SetMouseCursor(0);			
			mSelectedGameObject = gameObject;
		}

		popEvent(gameObject);
	}

	//popEvent(gameObject);
}

void GameObjectViewUI::popEvent(GameObject* gameObject)
{	
	std::string name = std::string(gameObject->GetName().begin(), gameObject->GetName().end());
	
	if (!ImGui::IsItemHovered())
	{
		return;
	}

	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::Button("Load"))
		{
		}
		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}	
	ImGui::SetItemTooltip(name.c_str());
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
