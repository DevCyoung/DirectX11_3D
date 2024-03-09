# include "pch.h"
#include <Content/ThirdPersonOrbitCam.h>
class ScriptComponent;
void ScriptComponentUI(ScriptComponent* component);


void ThirdPersonOrbitCamUI(ThirdPersonOrbitCam* component)
{
	ScriptComponentUI(component);

	float angleH = component->mAngleH;
	float angleV = component->mAngleV;

	ImGui::InputFloat("Angle H", &angleH);
	ImGui::InputFloat("Angle V", &angleV);

	Vector3 pivotOffset = component->mSmoothPivotOffset;
	Vector3 camOffset = component->mSmoothCamOffset;

	ImGui::DragFloat3("pivotOffset", &pivotOffset.x);
	ImGui::DragFloat3("camOffset", &camOffset.x	);

	component->mSmoothPivotOffset = pivotOffset;
	component->mSmoothCamOffset = camOffset;
}
