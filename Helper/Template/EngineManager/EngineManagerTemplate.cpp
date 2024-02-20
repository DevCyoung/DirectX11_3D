#include "pch.h"
#include "$safeitemname$.h"

$safeitemname$::$safeitemname$()
{		
}

$safeitemname$::~$safeitemname$()
{
}

void $safeitemname$::initialize()
{
	assert(!sInstance);
	sInstance = new $safeitemname$();
}

