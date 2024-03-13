#include "pch.h"
#include "Content.h"
#include <Engine/Engine.h> 
#include <Engine/EngineMath.h>
#include <Engine/SceneManager.h>
#include <Engine/TimeManager.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/GameObject.h>
#include <Engine/Camera.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/MeshRenderer.h>
#include <Engine/Light3D.h>
#include <Engine/Transform.h>

#include "SoundManager.h"
#include "CameraInputMoveMent.h"
#include "ContentResourceLoader.h"
#include "ResourceManager.h"
#include <Engine\Builder.h>
#include "Components.h"
#include "ThirdPersonOrbitCam.h"
#include <Engine\BuildSetting.h>
#include "Shlwapi.h"
Content::Content()
{
	//LoadAllResourceFiles(gPathManager->GetResourcePath());
	Scene* testScene = new Scene;
	std::wstring relativePath = gPathManager->GetResourcePath();
	relativePath += L"\\Scene\\Editor\\main.scene";

#ifdef EDITOR_MODE
	testScene->TurnOffScript();
#endif	
	if (PathFileExistsW(relativePath.c_str()))
	{
		testScene->Load(relativePath);
	}
	else
	{
		testScene->SetBackgroundColor(Vector4(0.5f, 0.5f, 0.5f, 1.f));		

		//main Camera
		{
			const Vector2 screenSize = Vector2(GAME_RENDER_TARGET_WIDTH, GAME_RENDER_TARGET_HEIGHT);
			GameObject* const mainCamera = CreateGameObject();
			mainCamera->SetName(L"Main Camera");
			mainCamera->AddComponent<Camera>();
			//mainCamera->AddComponent<ThirdPersonOrbitCam>();
			mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -100.f);

			mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
			mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
			mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);
			mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);

			testScene->AddGameObject(mainCamera, eLayerType::Camera);
		}

		//light
		{
			GameObject* obj = CreateGameObject();
			obj->AddComponent<Light3D>();
			obj->SetName(L"Global Light3D");
			testScene->AddGameObject(obj, eLayerType::Light);
		}
	}
	SceneManager::GetInstance()->LoadScene(testScene);
}

Content::~Content()
{
	//TimeManager::deleteInstance();
	//SoundManager::deleteInstance();
	//KatanaZeroSystem::deleteInstance();
	//FBXLoadManager::DeleteInstance();
}
