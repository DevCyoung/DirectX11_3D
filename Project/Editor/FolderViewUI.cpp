#include "pch.h"
#include "FolderViewUI.h"
#include <Engine\PathManager.h>
#include <Engine\Texture.h>
#include <Engine\ResourceManager.h>
#include <Engine\EnumResource.h>
#include <Engine\Material.h>

#include "PanelUIManager.h"
#include "InspectorUI.h"

namespace fs = std::filesystem;

static std::vector<std::wstring> GetDirectoryNames(const std::wstring& path)
{
	std::vector<std::wstring> result;
	result.reserve(10);
	for (const auto& entry : fs::directory_iterator(path))
	{
		std::wstring path2 = entry.path();
		if (entry.is_directory())
		{
			result.push_back(path2);
		}
	}
	return result;
}


static eResourceType GetResTypeByExt(const std::wstring& _relativepath)
{
	wchar_t szExt[50] = {};
	_wsplitpath_s(_relativepath.c_str(), 0, 0, 0, 0, 0, 0, szExt, 50);
	std::wstring strExt = szExt;
	
	if (L".pref" == strExt)
		return eResourceType::Prefab;
	else if (L".mesh" == strExt)
		return eResourceType::Mesh;
	else if (L".mat" == strExt)
		return eResourceType::Material;
	else if (L".png" == strExt || L".jpg" == strExt
		|| L".jpeg" == strExt || L".bmp" == strExt
		|| L".tga" == strExt || L".dds" == strExt)
		return eResourceType::Texture;
	else if (L".mp3" == strExt || L".wav" == strExt || L".oga" == strExt)
		return eResourceType::Sound;
	else if (L".mesh_data" == strExt)
		return eResourceType::MeshData;
	else if (L".anim" == strExt)
		return eResourceType::MeshData;
	else if (L".font" == strExt)
		return eResourceType::Font;
	else if (L".scene" == strExt)
		return eResourceType::Scene;
	else if (L".hlsl" == strExt || L".fxh" == strExt)
		return eResourceType::Shader;
	else
		return eResourceType::End;
}

static std::vector<std::wstring> GetFileNames(const std::wstring& path)
{
	std::vector<std::wstring> result;

	result.reserve(10);
	for (const auto& entry : fs::directory_iterator(path))
	{
		std::wstring path2 = entry.path();
		if (entry.is_regular_file())
		{
			result.push_back(path2);
		}
	}

	return result;
}

FolderViewUI::FolderViewUI()
	: mCD()
{
	SetTitle("FolderViewUI");
	mCD.push(gPathManager->GetResourcePath());
}

FolderViewUI::~FolderViewUI()
{
}

void FolderViewUI::Pop()
{
	if (mCD.size() <= 1)
	{
		return;
	}

	mCD.pop();
}

void FolderViewUI::Enter(const std::string& enter)
{
}

void FolderViewUI::update()
{
}


void FolderViewUI::drawForm()
{
	static float wrap_width = 70.f;
	static float icon_width = 70.0f;
	ImVec2 renderTargetSize = ImVec2(icon_width, icon_width);

	ImGui::Begin("FolderViewUI");	
	ImGui::Text(StringHelper::WStrToStr(mCD.top()).c_str());
	if (ImGui::Button("Revert"))
	{
		if (mCD.size() > 1)
		{
			mCD.pop();
		}
	}
	ImGui::Separator();

	const std::wstring& curPath = mCD.top();
	std::vector<std::wstring> directorys = GetDirectoryNames(curPath);	
	const std::wstring& resourcePath = gPathManager->GetResourcePath();

	static InspectorUI* inspectorUI =
		static_cast<InspectorUI*>(PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI"));
#pragma region UI_TEXTURE
	static Texture* folderTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\folder.png");

	static Texture* meshTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* shaderTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\HlslUI.png");

	static Texture* animationTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* fontTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* soundTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* sceneTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* preFabTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* computeShdaerTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* audioClipTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* dummyTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* materialTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");

	static Texture* meshDataTex =
		gResourceManager->Find<Texture>(L"\\Texture\\ImGUI\\MaterialUI.jpg");
#pragma endregion
	

	int idx = 0;
	ImGui::SliderFloat("Icon width##FolderViewUI", &icon_width, -20, 100, "%.0f");
	ImGui::SliderFloat("Wrap width##FolderViewUI", &wrap_width, -20, 100, "%.0f");

	for (std::wstring& directory : directorys)
	{
		ImGui::BeginGroup();
		std::string directoryID = "##";
		directoryID += StringHelper::WStrToStr(directory);
		if (ImGui::ImageButton(directoryID.c_str(), folderTex->GetSRV(), renderTargetSize))
		{
			mCD.push(directory);
		}
		std::wstring name = StringHelper::GetDirectoryNameFromPath(directory);
		std::string strName = StringHelper::WStrToStr(name);
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
		ImGui::Text(strName.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndGroup();
		if (idx == 0 || idx % 7 != 0)
		{
			ImGui::SameLine();
		}
		else
		{
			idx = -1;
		}
		++idx;
	}

	std::vector<std::wstring> files = GetFileNames(curPath);
	for (std::wstring file : files)
	{
		std::wstring name = StringHelper::GetFileNameFromPath(file);
		std::string strName = StringHelper::WStrToStr(name);
		eResourceType type = GetResTypeByExt(file);
		std::wstring relativePath = file.substr(resourcePath.size());
		ImGui::BeginGroup();

		switch (type)
		{
		case eResourceType::Texture:
		{
			Texture* tex = gResourceManager->Find<Texture>(relativePath);
			if (ImGui::ImageButton(strName.c_str(), tex->GetSRV(), renderTargetSize))
			{
				inspectorUI->Register(tex);
			}
		}

		break;
		case eResourceType::Mesh:
		{
			if (ImGui::ImageButton(strName.c_str(), meshTex->GetSRV(), renderTargetSize))
			{
				//Mesh* mat = gResourceManager->Find<Mesh>(relativePath);
				//inspectorUI->Register(mat);
			}
		}
		break;
			break;
		case eResourceType::Material:
		{			
			if (ImGui::ImageButton(strName.c_str(), materialTex->GetSRV(), renderTargetSize))
			{
				Material* mat = gResourceManager->Find<Material>(relativePath);
				inspectorUI->Register(mat);
			}
		}
			break;
		case eResourceType::Shader:
		{
			if (ImGui::ImageButton(strName.c_str(), shaderTex->GetSRV(), renderTargetSize))
			{
				//Shader* shader = gResourceManager->Find<Shader>(relativePath);
				//inspectorUI->Register(shader);
			}
		}
			break;
		case eResourceType::Animation:
		{
			if (ImGui::ImageButton(strName.c_str(), animationTex->GetSRV(), renderTargetSize))
			{
				//Animation* anim = gResourceManager->Find<Animation>(relativePath);
				//inspectorUI->Register(anim);
			}
		}
			break;
		case eResourceType::Font:
		{
			if (ImGui::ImageButton(strName.c_str(), fontTex->GetSRV(), renderTargetSize))
			{
				//Font* font = gResourceManager->Find<Font>(relativePath);
				//inspectorUI->Register(font);
			}
		}
			break;
		case eResourceType::Sound:
		{
			if (ImGui::ImageButton(strName.c_str(), soundTex->GetSRV(), renderTargetSize))
			{
				//Sound* sound = gResourceManager->Find<Sound>(relativePath);
				//inspectorUI->Register(sound);
			}
		}
			break;
		case eResourceType::Scene:
		{
			if (ImGui::ImageButton(strName.c_str(), sceneTex->GetSRV(), renderTargetSize))
			{
				//Scene* scene = gResourceManager->Find<Scene>(relativePath);
				//inspectorUI->Register(scene);
			}
		}
			break;
		case eResourceType::Prefab:
		{
			if (ImGui::ImageButton(strName.c_str(), preFabTex->GetSRV(), renderTargetSize))
			{
				//Prefab* prefab = gResourceManager->Find<Prefab>(relativePath);
				//inspectorUI->Register(prefab);
			}
		}
			break;
		case eResourceType::ComputeShader:
		{
			if (ImGui::ImageButton(strName.c_str(), computeShdaerTex->GetSRV(), renderTargetSize))
			{
				//ComputeShader* csahder = gResourceManager->Find<ComputeShader>(relativePath);
				//inspectorUI->Register(csahder);
			}
		}
			break;
		case eResourceType::AudioClip:
		{
			if (ImGui::ImageButton(strName.c_str(), audioClipTex->GetSRV(), renderTargetSize))
			{
				//AudioClip* audioClip = gResourceManager->Find<AudioClip>(relativePath);
				//inspectorUI->Register(audioClip);
			}
		}
			break;
		case eResourceType::MeshData:
		{
			if (ImGui::ImageButton(strName.c_str(), meshDataTex->GetSRV(), renderTargetSize))
			{
				//MeshData* meshData = gResourceManager->Find<MeshData>(relativePath);
				//inspectorUI->Register(meshData);
			}
		}
			break;
		default:
			break;
		}
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
		ImGui::Text(strName.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndGroup();
		if (idx == 0 || idx % 7 != 0)
		{
			ImGui::SameLine();
		}
		else
		{
			idx = -1;
		}
		++idx;
	}
	ImGui::End();
}