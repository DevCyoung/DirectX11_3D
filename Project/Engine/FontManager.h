#pragma once
#include "Singleton.h"

#include "FW1FontWrapper/Include/FW1FontWrapper.h"
#include "FW1FontWrapper/Include/FW1CompileSettings.h"
#include "Fmod/Include/fmod_common.h"

class FontManager
{
	friend class Engine;
	SINGLETON_DECLARE(FontManager);

public:	
	void DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb);	

private:
	IFW1Factory* mFW1Factory;
	IFW1FontWrapper* mFontWrapper;
};