#pragma once

#define WIN32_LEAN_AND_MEAN
//DirectX
//#include <d3d11.h>
#include <d3d11_1.h>
#include <string>
#include <sstream>
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "glload/wgl_all.h"

#include "../Modules/Mesh/MeshModule.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

using namespace ci;
using namespace ci::app;
using namespace std;

typedef struct
{
	CURSORINFO		Ci;
	bool			CursorCaptured;
	HCURSOR			CursorIcon = LoadCursor(NULL, IDC_ARROW);
	POINT			WinPos;
	POINT			FinalPos;
}s_MouseInfo;