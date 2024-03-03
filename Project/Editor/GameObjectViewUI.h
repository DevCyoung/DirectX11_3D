#pragma once
#include "PanelUI.h"

class GameObject;
class GameObjectViewUI : public PanelUI
{
public:
	GameObjectViewUI();
	~GameObjectViewUI();

private:
	// PanelUI을(를) 통해 상속됨
	void popUpView(GameObject* const gameObject);
	void popEvent(GameObject* const gameObject);
	virtual void update() final;
	void drawForm() override;

	GameObject* mSelectedGameObject;
};

