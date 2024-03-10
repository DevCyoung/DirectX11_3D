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

	Vector3 pivotOffset = component->mPivotOffset;
	Vector3 camOffset = component->mCamOffset;

	ImGui::DragFloat3("pivotOffset", &pivotOffset.x);
	ImGui::DragFloat3("camOffset", &camOffset.x	);

	component->mPivotOffset = pivotOffset;
	component->mCamOffset = camOffset;
}
