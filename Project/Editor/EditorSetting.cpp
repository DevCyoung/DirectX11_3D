#include "pch.h"
#include "EditorSetting.h"
#include <Engine/GameObject.h>
#include <Engine/SceneManager.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/ResourceManager.h>
#include <Content/Components.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>

EditorSetting::EditorSetting()
{
	SetTitle("Editor Setting");
}

EditorSetting::~EditorSetting()
{
}

GameObject* EditorSetting::CreateObject()
{
	GameObject* obj = new GameObject();
	obj->AddComponent<MeshRenderer>();
	obj->GetComponent<MeshRenderer>()->SetMesh(gResourceManager->Find<Mesh>(L"Cube"));
	obj->GetComponent<MeshRenderer>()->SetMaterial(gResourceManager->Find<Material>(L"Std3DMat"), 0);
	return obj;
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
		GameObject* obj = CreateObject();
		gCurrentScene->RegisterEventAddGameObject(obj, eLayerType::Default);
	}

	ImGui::End();
}
