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

Content::Content()
{
	LoadAllResourceFiles(gPathManager->GetResourcePath());
	Scene* testScene = new Scene;

	//main Camera
	{
		const Vector2 screenSize = Vector2(1280, 720);
		GameObject* const mainCamera = new GameObject();
		mainCamera->SetName(L"mainCamera");
		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();
		mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);		
		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -100.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		//mainCamera->GetComponent<Transform>()->SetPosition(Vector3(772.f, 2250.f, -3690.f));
		testScene->AddGameObject(mainCamera, eLayerType::Default);
	}

	//MeshData Object
	{
		//MeshData* meshData = FBXLoader::FbxInstantiate(L"\\Fbx\\black.fbx");

		//GameObject* obj = meshData->Instantiate();
		//obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//obj->SetName(L"Dragon");
		//Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
		//obj->GetComponent<Transform>()->SetRotation(rotation);
		//obj->GetComponent<Transform>()->SetScale(50.f, 50.f, 50.f);
		//testScene->AddGameObject(obj, eLayerType::TileMap);
	}

	//Light3D
	{
		GameObject* obj = new GameObject();
		obj->AddComponent<Light3D>();
		obj->SetName(L"Light3D");

		testScene->AddGameObject(obj, eLayerType::Light);
	}

	//Hirearchy Test
	{
		GameObject* parent = new GameObject();
		parent->SetName(L"parent");

		{
			GameObject* obj = new GameObject();
			//obj->AddComponent<Light3D>();
			obj->SetName(L"Test");
			{
				GameObject* childObj = new GameObject();
				childObj->SetName(L"childObj1");
				obj->SetChild(childObj);
			}

			{
				GameObject* childObj = new GameObject();
				childObj->SetName(L"childObj2");
				obj->SetChild(childObj);
			}

			parent->SetChild(obj);
		}

		{
			GameObject* obj = new GameObject();
			//obj->AddComponent<Light3D>();
			obj->SetName(L"Test");
			{
				GameObject* childObj = new GameObject();
				childObj->SetName(L"childObj1");
				obj->SetChild(childObj);
			}

			{
				GameObject* childObj = new GameObject();
				childObj->SetName(L"childObj2");
				obj->SetChild(childObj);
			}

			parent->SetChild(obj);
		}

		testScene->AddGameObject(parent, eLayerType::Default);
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
