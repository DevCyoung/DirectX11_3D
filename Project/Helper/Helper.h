#pragma once

#include <assert.h>
#include <Windows.h>
#include <string>
#include <vector> 
#include <stack>
#include <list> 
#include <map> 
#include <queue>
#include <unordered_map> 
#include <bitset> 
#include <set> 
#include <functional> 
#include <cmath> 
#include <algorithm> 
#include <limits>
#include <memory> 
#include <filesystem> 
#include <wrl.h>
#include <commdlg.h>
#include <d3d11.h>

#include "DefineMacro.h"
#include "Singleton.h"
#include "Memory.h"
#include "DXMath.h"
#include "StringHelper.h"

#ifdef _DEBUG
#pragma comment(lib, "Helper/Debug/Helper_d")
#else
#pragma comment(lib, "Helper/Release/Helper")
#endif

using namespace engine::math;