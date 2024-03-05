#include "pch.h"
#include "GameObjectViewUI.h"
#include <Engine/SceneManager.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"
#include <Engine/Engine.h>
#include <Engine/PathManager.h>
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
		if (ImGui::Button("Prefab"))
		{
			OPENFILENAME ofn;       // ���� ���̾�α� ����ü
			TCHAR szFile[260];      // ������ ������ ��θ� ������ ����
			HWND hwnd = NULL;       // �θ� â�� �ڵ� (NULL�� �����ϸ� �� â�� �θ� ��)
			std::wstring path = gPathManager->GetResourcePath();
			path += L"\\Prefab";
			// ���� ���̾�α� ����ü �ʱ�ȭ
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = TEXT("Text Files (*.pf)\0*.TXT\0All Files (*.*)\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = path.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

			// ���� ���̾�α� ����
			if (GetSaveFileName(&ofn) == TRUE) {
				// ����ڰ� ������ �����ϰ� Ȯ���� ������ ��
				MessageBox(NULL, ofn.lpstrFile, TEXT("Selected File"), MB_OK);

				FILE* file = nullptr;				
				errno_t err = _wfopen_s(&file, ofn.lpstrFile, L"wb");
				(void)err;
				gameObject->Save(file);
				fclose(file);
			}
			else {
				// ����ڰ� ��Ҹ� ������ ��
				MessageBox(NULL, TEXT("No file selected!"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}

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
