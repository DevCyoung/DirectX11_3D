#pragma once
#include "PanelUI.h"

class EditorSetting : public PanelUI
{
public:
	EditorSetting();
	virtual ~EditorSetting();

private:
	// PanelUI��(��) ���� ��ӵ�
	void drawForm() override;	
};

