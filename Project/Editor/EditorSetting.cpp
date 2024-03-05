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
#include <Engine/Builder.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"

float EditorSetting::SkeletonScale = 1.f;

EditorSetting::EditorSetting()	
{
	SetTitle("Editor Setting");
}

EditorSetting::~EditorSetting()
{
}

GameObject* EditorSetting::CreateObject()
{
	GameObject* obj = CreateGameObject();
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

	//float mSkeletonScale = 1.f;

	if (ImGui::InputFloat("skeletonScale", &SkeletonScale, 0.01f, 5.f))
	{
	}

	if (ImGui::Button("Save Scene"))
	{
		OPENFILENAME ofn;       // ���� ���̾�α� ����ü
		TCHAR szFile[260];      // ������ ������ ��θ� ������ ����
		HWND hwnd = NULL;       // �θ� â�� �ڵ� (NULL�� �����ϸ� �� â�� �θ� ��)
		std::wstring path = gPathManager->GetResourcePath();
		path += L"\\Scene";
		// ���� ���̾�α� ����ü �ʱ�ȭ
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("Text Files (*.scene)\0*.TXT\0All Files (*.*)\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = path.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

		// ���� ���̾�α� ����
		if (GetSaveFileName(&ofn) == TRUE) {
			// ����ڰ� ������ �����ϰ� Ȯ���� ������ ��
			MessageBox(NULL, ofn.lpstrFile, TEXT("Selected File"), MB_OK);

			//FILE* file = nullptr;
			//errno_t err = _wfopen_s(&file, ofn.lpstrFile, L"wb");
			//(void)err;
			gCurrentScene->Save(ofn.lpstrFile);
			//gameObject->Save(file);
			//fclose(file);
		}
		else {
			// ����ڰ� ��Ҹ� ������ ��
			MessageBox(NULL, TEXT("No file selected!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		}
	}

	if (ImGui::Button("Load Scene"))
	{

		OPENFILENAME ofn;       // ���� ���̾�α� ����ü
		TCHAR szFile[260];      // ������ ������ ��θ� ������ ����
		HWND hwnd = NULL;       // �θ� â�� �ڵ� (NULL�� �����ϸ� �� â�� �θ� ��)
		std::wstring path = gPathManager->GetResourcePath();
		path += L"\\Scene";
		// ���� ���̾�α� ����ü �ʱ�ȭ
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = path.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// ���� ���̾�α� ����
		if (GetOpenFileName(&ofn) == TRUE) {
			// ����ڰ� ������ �����ϰ� Ȯ���� ������ ��
			MessageBox(NULL, ofn.lpstrFile, TEXT("Selected File"), MB_OK);

			//FILE* file = nullptr;
			//errno_t err = _wfopen_s(&file, ofn.lpstrFile, L"wb");
			//(void)err;
			//gCurrentScene->Save(ofn.lpstrFile);
			Scene* scene = new Scene();
			scene->Load(ofn.lpstrFile);
			SceneManager::GetInstance()->RegisterLoadScene(scene);			
			static_cast<InspectorUI*>(PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI"))->UnRegister();
			//gameObject->Save(file);
			//fclose(file);
		}
		else {
			// ����ڰ� ��Ҹ� ������ ��
			MessageBox(NULL, TEXT("No file selected!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		}
	}

	ImGui::End();
}
