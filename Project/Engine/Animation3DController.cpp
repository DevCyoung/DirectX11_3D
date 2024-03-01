#include "pch.h"
#include "Animation3DController.h"
#include "Animator3D.h"
Animation3DController::Animation3DController()
	: Component(eComponentType::Animation3DController)
{
}

Animation3DController::~Animation3DController()
{
}

void Animation3DController::Play(const std::wstring& animation)
{
	for (Animator3D* animator3D : mAnimation3Ds)
	{
		animator3D->Play(animation);
	}
}

void Animation3DController::update()
{

}
