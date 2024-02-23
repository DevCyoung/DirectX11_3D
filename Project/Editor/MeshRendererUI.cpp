# include "pch.h"
#include <Engine/MeshRenderer.h>
#include "MaterialUI.h"
#include <Engine\Material.h>
class RenderComponent;
void RenderComponentUI(RenderComponent* component);


void MeshRendererUI(MeshRenderer* component)
{
	RenderComponentUI(component);

	for (int i = 0; i < component->GetMaterialCount(); ++i)
	{
		Material* material = component->GetMaterial(i);
		std::string name = StringHelper::WStrToStr(material->GetRelativePathorName());

		if (name.length() <= 1)
		{
			name = "NONE";
		}

		name += "##";
		name += std::to_string(component->GetID());
		name += "_";
		name += std::to_string(i);

		if (ImGui::CollapsingHeader(name.c_str()))
		{
			MaterialUI(component->GetMaterial(i));
		}		
	}
}
	