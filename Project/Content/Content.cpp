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
Content::Content()
{
	//LoadAllResourceFiles(gPathManager->GetResourcePath());
	Scene* testScene = new Scene;
	std::wstring relativePath = gPathManager->GetResourcePath();
	relativePath += L"\\Scene\\Editor\\main.scene";
	testScene->Load(relativePath);

	//main Camera
	//{
	//	const Vector2 screenSize = Vector2(1280, 720);
	//	GameObject* const mainCamera = CreateGameObject();
	//	mainCamera->SetName(L"mainCamera");
	//	mainCamera->AddComponent<Camera>();
	//	mainCamera->AddComponent<ThirdPersonOrbitCam>();
	//	mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -100.f);
	//
	//	mainCamera->GetComponent<Camera>()->TurnOnAllLayer();		 
	//	mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
	//	mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);		
	//	mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
	//	testScene->AddGameObject(mainCamera, eLayerType::Default);
	//
	//	//GameObject* tg = new GameObject(*mainCamera);
	//	//(void)tg;
	//}

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
	//{
	//	GameObject* obj = CreateGameObject();
	//	obj->AddComponent<Light3D>();
	//	obj->SetName(L"Light3D");
	//
	//	testScene->AddGameObject(obj, eLayerType::Light);
	//}
	
	////Hirearchy Test
	//{
	//	GameObject* parent = CreateGameObject();
	//	parent->SetName(L"parent");
	//
	//	{
	//		GameObject* obj = CreateGameObject();
	//		//obj->AddComponent<Light3D>();
	//		obj->SetName(L"Test");
	//		{
	//			GameObject* childObj = CreateGameObject();
	//			childObj->SetName(L"childObj1");
	//			obj->SetChild(childObj);
	//		}
	//
	//		{
	//			GameObject* childObj = CreateGameObject();
	//			childObj->SetName(L"childObj2");
	//			obj->SetChild(childObj);
	//		}
	//
	//		parent->SetChild(obj);
	//	}
	//
	//	{
	//		GameObject* obj = CreateGameObject();
	//		//obj->AddComponent<Light3D>();
	//		obj->SetName(L"Test");
	//		{
	//			GameObject* childObj = CreateGameObject();
	//			childObj->SetName(L"childObj1");
	//			obj->SetChild(childObj);
	//		}
	//
	//		{
	//			GameObject* childObj = CreateGameObject();
	//			childObj->SetName(L"childObj2");
	//			obj->SetChild(childObj);
	//		}
	//
	//		parent->SetChild(obj);
	//	}
	//
	//	testScene->AddGameObject(parent, eLayerType::Default);
	//
	//	//std::wstring resourcePath = gPathManager->GetResourcePath();
	//	//resourcePath = resourcePath + L"\\Prefab\\test.pf";
	//	//FILE* file = nullptr;
	//	//errno_t err = _wfopen_s(&file, resourcePath.c_str(), L"wb");
	//	//parent->Save(file);
	//	//fclose(file);
	//	//
	//	//file = nullptr;
	//	//err = _wfopen_s(&file, resourcePath.c_str(), L"rb");
	//	//GameObject* saveObj = CreateGameObjectNoTransform();
	//	//saveObj->Load(file);
	//	//fclose(file);
	//	//DELETE_POINTER(saveObj);
	//
	//}

	SceneManager::GetInstance()->LoadScene(testScene);
}

Content::~Content()
{
	//TimeManager::deleteInstance();
	//SoundManager::deleteInstance();
	//KatanaZeroSystem::deleteInstance();
	//FBXLoadManager::DeleteInstance();
}
