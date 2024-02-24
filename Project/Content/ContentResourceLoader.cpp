#include "pch.h"
#include "ContentResourceLoader.h"
#include "ResourceManager.h"
#include <filesystem>

namespace fs = std::filesystem;

eResourceType GetResTypeByExtension(const std::wstring& relativePath)
{
	constexpr int EXTENSION_SIZE = 50;
	wchar_t szExt[EXTENSION_SIZE] = {};
	_wsplitpath_s(relativePath.c_str(), 0, 0, 0, 0, 0, 0, szExt, EXTENSION_SIZE);

	std::wstring strExt = szExt;

	if (L".png" == strExt || L".jpg" == strExt ||
		L".jpeg" == strExt || L".bmp" == strExt ||
		L".tga" == strExt || L".dds" == strExt)
	{
		return eResourceType::Texture;
	}
	else if (L".mdat" == strExt)
	{
		return eResourceType::End;
	}
	else if (L".pref" == strExt)
	{
		return eResourceType::Prefab;
	}
	else if (L".mesh" == strExt)
	{
		return eResourceType::Mesh;
	}
	else if (L".mtrl" == strExt)
	{
		return eResourceType::Material;
	}
	else if (L".mp3" == strExt || L".wav" == strExt || L".oga" == strExt)
	{
		return eResourceType::Sound;
	}
	else if (L".mesh_data" == strExt)
	{
		return eResourceType::MeshData;
	}
	else
	{
		return eResourceType::End;
	}
}

void LoadAllResourceFiles(const std::wstring& resourcePath)
{
	for (const auto& entry : fs::directory_iterator(resourcePath))
	{
		if (fs::is_regular_file(entry.path()))
		{
			std::wstring path2 = entry.path();

			std::wstring len = gPathManager->GetResourcePath();
			path2 = path2.substr(len.length());
			eResourceType type = GetResTypeByExtension(path2);

			switch (type)
			{
			case eResourceType::Texture:
				gResourceManager->Load<Texture>(path2);
				break;
			case eResourceType::Mesh:
				//gResourceManager->Load<Mesh>(path2);
				break;
			case eResourceType::MeshData:
				gResourceManager->Load<MeshData>(path2);
				break;
			case eResourceType::Material:
				gResourceManager->Load<Material>(path2);
				break;
			case eResourceType::Shader:
				break;
			case eResourceType::Animation:
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
				break;
			case eResourceType::AudioClip:
				break;
			case eResourceType::End:
				break;
			default:
				break;
			}			
		}
		else if (fs::is_directory(entry.path()))
		{
			LoadAllResourceFiles(entry.path().wstring());
		}
	}
}
