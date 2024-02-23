#include "imgui_helper.h"
#include "imgui.h"

namespace ImGui
{
	bool Combo(const char* label, int* current_item, const std::vector<std::wstring>& vec)
	{
		std::vector<std::string> stringNames;
		std::vector<const char*> ccps;

		for (const std::wstring& name : vec)
		{
			std::string str(name.cbegin(), name.cend());
			stringNames.push_back(str);
		}

		for (const std::string& name : stringNames)
		{
			ccps.push_back(name.c_str());
		}

		return ImGui::Combo(label, current_item, ccps.data(), ccps.size());
	}

	bool Combo(const char* label, int* current_item, const std::vector<std::string>& vec)
	{
		std::vector<const char*> ccps;

		for (const std::string& name : vec)
		{
			ccps.push_back(name.c_str());
		}

		return ImGui::Combo(label, current_item, ccps.data(), ccps.size());
	}
}