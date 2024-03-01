#pragma once
#include "PanelUI.h"

class GameObject;
class GameObjectViewUI : public PanelUI
{
public:
	GameObjectViewUI();
	~GameObjectViewUI();

private:
	// PanelUI��(��) ���� ��ӵ�
	void popUpView(GameObject* gameObject);
	virtual void update() final;
	void drawForm() override;

	GameObject* mSelectedGameObject;
};

