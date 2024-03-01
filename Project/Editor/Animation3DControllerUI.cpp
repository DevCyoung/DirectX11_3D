# include "pch.h"
#include <Engine/Animation3DController.h>
#include <Engine/Animator3D.h>
class Component;
void ComponentUI(Component* component);


void Animation3DControllerUI(Animation3DController* component)
{
	ComponentUI(component);

	const std::vector<Animator3D*>& animation3Ds = component->GetAnimation3Ds();
	if (!animation3Ds.empty())
	{
		const std::vector<tMTAnimClip>& clips = *animation3Ds[0]->GetAnimationClip();
		static int item_current = 0;

		std::vector<std::wstring> clipNames;
		clipNames.reserve(clips.size());

		for (const tMTAnimClip& clip : clips)
		{
			clipNames.push_back(clip.strAnimName);
		}

		if (ImGui::Combo("##Animation3DComboCLips", &item_current, clipNames))
		{
			//component->SetClipID(item_current);
		}

		int idx = item_current;

		if (idx < 0)
		{
			return;
		}

		int startFrame = animation3Ds[0]->GetStartFrame(idx);
		int endFrame = animation3Ds[0]->GetEndFrame(idx);

		if (ImGui::InputInt("starFrame", &startFrame))
		{
			//component->SetStartFrame(idx, startFrame);
		}
		if (ImGui::InputInt("endFrame", &endFrame))
		{
			//component->SetEndFrame(idx, endFrame);
		}
	}
}
