# include "pch.h"
#include <Engine/MeshRenderer.h>
#include "MaterialUI.h"
#include <Engine/Material.h>
#include <Engine\Mesh.h>

class RenderComponent;
void RenderComponentUI(RenderComponent* component);


void MeshRendererUI(MeshRenderer* component)
{
	RenderComponentUI(component);

	ImGui::Separator();

	//Material
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
	ImGui::Separator();
	//Mesh
	Mesh* mesh = component->GetMesh();
	std::vector<tMTBone>* bones = mesh->GetBones();

	//if (ImGui::CollapsingHeader("BonData"))
	//{
	//	for (int i = 0; i < bones->size(); ++i)
	//	{
	//		const tMTBone& bone = bones->at(i);
	//		std::string bonName = std::string(bone.strBoneName.begin(), bone.strBoneName.end());
	//		if (ImGui::TreeNode(bonName.c_str()))
	//		{				
	//			ImGui::TreePop();
	//		}

	//	}
	//}
}
	