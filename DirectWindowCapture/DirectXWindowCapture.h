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

class DirectXWindowCapture
{
public:
	DirectXWindowCapture();
	~DirectXWindowCapture();

	HRESULT init();

    void FindAllWindowTitle(vector<string>& WindowTitle);
	bool SelectWindow(int TitleIndex);
	void InitGLDX_ShareTexture(int BindIndex = 0);
    s_MouseInfo GetMouseInfo() { return m_MouseInfo; }
	//
	HWND GetCaptureHwnd() { return m_Hwnd; }
	vec2 GetWindowRect() { return vec2(TextureWidth, TextureHigh); }
	void UpdateHDC();
	void LockDX();
	void UnLockDX();

private:
	//d3d init
	HRESULT initDevice();
	HRESULT CreatTexture(ID3D11Device* Device, int width, int high);
	static BOOL CALLBACK FindWindowsHandle(HWND hwnd, LPARAM lParam);
	static bool CheckWindowValid(HWND hWnd);