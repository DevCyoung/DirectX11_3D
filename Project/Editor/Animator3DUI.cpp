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

}
