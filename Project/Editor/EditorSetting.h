#pragma once
#include "PanelUI.h"

class EditorSetting : public PanelUI
{
public:
	EditorSetting();
	virtual ~EditorSetting();

private:
	// PanelUI을(를) 통해 상속됨
	void drawForm() override;	
};

