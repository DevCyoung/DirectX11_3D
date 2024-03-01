# include "pch.h"
#include <Engine/Animator3D.h>
class RenderComponent;
void ComponentUI(Component* component);


void Animator3DUI(Animator3D* component)
{
	ComponentUI(component);

	const std::vector<tMTAnimClip>& clips =  *component->GetAnimationClip();
	static int item_current = 0;

	std::vector<std::wstring> clipNames;
	clipNames.reserve(clips.size());

	for (const tMTAnimClip& clip : clips)
	{		
		clipNames.push_back(clip.strAnimName);
	}

	if (ImGui::Combo("##Animation3DComboCLips", &item_current, clipNames))
	{
		component->SetClipID(item_current);
	}

	//Frame
	int curFrame = component->GetCurFrameIdx();
	ImGui::InputInt("cur frame : ", &curFrame);	


	int idx = item_current;
	if (idx < 0)
	{
		return;
	}
	int startFrame = component->GetStartFrame(idx);
	int endFrame = component->GetEndFrame(idx);

	if (ImGui::InputInt("starFrame", &startFrame))
	{
		 component->SetStartFrame(idx, startFrame);
	}
	if (ImGui::InputInt("endFrame", &endFrame))
	{
		component->SetEndFrame(idx, endFrame);
	}		

	//Bone
		//Mesh
	const std::vector<tMTBone>* bones  = component->GetBones();	

	if (ImGui::CollapsingHeader("BonData"))
	{
		for (int i = 0; i < bones->size(); ++i)
		{
			const tMTBone& bone = bones->at(i);
			std::string bonName = std::string(bone.strBoneName.begin(), bone.strBoneName.end());
			ImGui::Selectable(bonName.c_str());
			if (bone.vecKeyFrame.empty())
			{
				continue;
			}

			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::Button("Add Bone"))
				{

				}
			}

			tMTKeyFrame key = bone.vecKeyFrame[curFrame];
			ImGui::InputFloat3("T", &key.vTranslate.x);
			ImGui::InputFloat3("S", &key.vScale.x);
			ImGui::InputFloat4("Q", &key.qRot.x);

			
		}
	}
}
