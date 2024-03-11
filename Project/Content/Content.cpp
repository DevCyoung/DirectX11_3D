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
Content::Content()
{
	//LoadAllResourceFiles(gPathManager->GetResourcePath());
	Scene* testScene = new Scene;
	std::wstring relativePath = gPathManager->GetResourcePath();
	relativePath += L"\\Scene\\Editor\\main.scene";

#ifdef EDITOR_MODE
	testScene->TurnOffScript();
#endif
	testScene->Load(relativePath);
	SceneManager::GetInstance()->LoadScene(testScene);
}

Content::~Content()
{
	//TimeManager::deleteInstance();
	//SoundManager::deleteInstance();
	//KatanaZeroSystem::deleteInstance();
	//FBXLoadManager::DeleteInstance();
}
