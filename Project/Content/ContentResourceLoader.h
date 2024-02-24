#pragma once
#include <Engine\EnumResource.h>

eResourceType GetResTypeByExtension(const std::wstring& relativePath);
void LoadAllResourceFiles(const std::wstring& resourcePath);