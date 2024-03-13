#include "pch.h"
#include "PlayerMovement.h"
#include "Components.h"
#include <Engine\Animation3DController.h>
PlayerMovement::PlayerMovement()
    : ScriptComponent(eScriptComponentType::PlayerMovement)
    , mController(nullptr)
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::initialize()
{
    mController = GetComponent<Animation3DController>();
}

void PlayerMovement::update()
{
    if (gInput->GetKeyUp(eKeyCode::W))
    {
        mController->Play(L"Idle", 0.3f);
    }
    if (gInput->GetKeyDown(eKeyCode::W))
    {
        mController->Play(L"WALK_F", 0.3f);
    }
}

void PlayerMovement::lateUpdate()
{
}