#pragma once
#include "PanelUI.h"
class GameObject;
class EditorSetting : public PanelUI
{
public:
	EditorSetting();
	virtual ~EditorSetting();
	static GameObject* CreateObject();

private:
	// PanelUI��(��) ���� ��ӵ�
	
	void drawForm() override;	
};

