#include "pch.h"
#include "GameObjectViewUI.h"
#include <Engine/SceneManager.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"
GameObjectViewUI::GameObjectViewUI()
{
}

GameObjectViewUI::~GameObjectViewUI()
{
}

void GameObjectViewUI::update()
{	
}

static void popUpView(GameObject* gameObject, InspectorUI* inspectorUI)
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
				ImGui::SetMouseCursor(0);
				inspectorUI->Register(gameObject);
			}			
			for (GameObject* childObj : childObjects)
			{
				popUpView(childObj, inspectorUI);
			}
			ImGui::TreePop();
		}
	}	
	else
	{
		ImGui::Bullet();
		if (ImGui::Selectable(itemName.c_str(), false))
		{
			ImGui::SetMouseCursor(0);
			inspectorUI->Register(gameObject);
		}

		/*if (ImGui::IsItemClicked())
		{
			ImGui::SetMouseCursor(0);
			inspectorUI->Register(gameObject);
		}*/
	}


}

void GameObjectViewUI::drawForm()
{
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
			popUpView(gameObject, inspectorUI);
			//std::string itemName = StringHelper::WStrToStr(gameObject->GetName());
			//ImGui::Bullet();
			//ImGui::Selectable(itemName.c_str(), false);
			//if (ImGui::IsItemClicked())
			//{
			//	ImGui::SetMouseCursor(0);
			//	inspectorUI->Register(gameObject);
			//}
		}

	}

	//ImGui::Text("Hello world!");
	ImGui::End();
}
