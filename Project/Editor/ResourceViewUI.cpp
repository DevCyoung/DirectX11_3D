#include "pch.h"
#include "ResourceViewUI.h"
#include "ResourceUI.h"

#include <Engine/SceneManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/GameSystem.h>
#include <Engine/GameObject.h>
#include <Engine/Texture.h>
#include <Engine/EnumResource.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"

//엔진, 컨텐트 리소스만 보여줍니다. (폴더에있는 리소스는 FolderViewUI)
ResourceViewUI::ResourceViewUI()
{
}

ResourceViewUI::~ResourceViewUI()
{
}

std::string GetTypeName(eResourceType type)
{
	std::string result;
	switch (type)
	{
	case eResourceType::Texture:
		result = "Texture";
		break;
	case eResourceType::Mesh:
		result = "Mesh";
		break;
	case eResourceType::Material:
		result = "Material";
		break;
	case eResourceType::Shader:
		return "Sahder";
		break;
	case eResourceType::Animation:
		result = "Animation";
		break;
	case eResourceType::Font:
		break;
	case eResourceType::Sound:
		break;
	case eResourceType::Scene:
		break;
	case eResourceType::Prefab:
		break;
	case eResourceType::ComputeShader:
		result = "ComputeShader";
		break;
	case eResourceType::AudioClip:
		break;
	case eResourceType::End:
		break;
	case eResourceType::MeshData:
		result = "MeshData";
		break;
	case eResourceType::FBX:
		break;
	default:
		Assert(false, ASSERT_MSG_INVALID);
		break;
	}

	return result;
}

void ResourceViewUI::drawForm()
{
	ImGui::Begin("ResourceViewUI");

	for (UINT i = 0; i < static_cast<UINT>(eResourceType::End); ++i)
	{
		const ResourceManager::Dictionary& dictionary =
			ResourceManager::GetInstance()->GetDictionary(static_cast<eResourceType>(i));

		if (dictionary.empty())
		{
			continue;
		}

		ResourceManager::Dictionary::const_iterator citer = dictionary.cbegin();
		ResourceManager::Dictionary::const_iterator cend = dictionary.cend();

		std::string typeName = GetTypeName(static_cast<eResourceType>(i));		
		typeName += "##ResourceViewUI";		

		if (ImGui::CollapsingHeader((typeName).c_str()))
		{
			for (; citer != cend; ++citer)
			{
				std::string relativePath =
					StringHelper::WStrToStr(citer->second->GetRelativePathorName());
				if (relativePath.front() == '\\')
				{
					continue;
				}
				ImGui::Bullet();
				ImGui::Selectable(relativePath.c_str(), false);
				if (ImGui::IsItemClicked())
				{					
					PanelUI* inspectorUI =
						PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI");
					static_cast<InspectorUI*>(inspectorUI)->Register(citer->second);
				}

			}			
		}
	}

	ImGui::End();
}

void ResourceViewUI::update()
{

}
