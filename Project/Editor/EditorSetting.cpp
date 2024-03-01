#include "pch.h"
#include "EditorSetting.h"
#include <Engine/GameObject.h>
#include <Engine/SceneManager.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
EditorSetting::EditorSetting()
{
	SetTitle("Editor Setting");
}

EditorSetting::~EditorSetting()
{
}

void EditorSetting::drawForm()
{
	ImGui::Begin("Editor Setting");		
	bool bWireFrame = gCurrentSceneRenderer->IsWireFrame();
	if (ImGui::Checkbox("Wire Frame", &bWireFrame))
	{
		if (bWireFrame)
		{
			gCurrentSceneRenderer->TurnOnWireFrame();
		}
		else
		{
			gCurrentSceneRenderer->TurnOffWireFrame();
		}
	}

	if (ImGui::Button("Create Object"))
	{
		GameObject* obj = new GameObject();
		gCurrentScene->RegisterEventAddGameObject(obj, eLayerType::Default);
	}

	ImGui::End();
}
