#include "DirectXWindowCapture.h"
DirectXWindowCapture::DirectXWindowCapture()
{
	DX_Texture = NULL;
	m_GdiSurface = NULL;
	m_D3dDevice = NULL;
	m_D3dContext = NULL;
	m_Hwnd = NULL;
    m_DX11Device_HANDLE = NULL;
	TextureWidth = -1;
	TextureHigh = -1;
	GL_Texture = 0;
	m_MouseInfo.Ci.cbSize = sizeof(CURSORINFO);

}

DirectXWindowCapture::~DirectXWindowCapture()
{
	if (DX_Texture)
	{
		DX_Texture->Release();
		DX_Texture = NULL;
	}
	if (m_GdiSurface)
	{
		m_GdiSurface->Release();
		m_GdiSurface = NULL;
	}
    	if (m_D3dDevice)
	{
		m_D3dDevice->Release();
		m_D3dDevice = NULL;
	}
	if (m_D3dContext)
	{
		m_D3dContext->Release();
		m_D3dContext = NULL;
	}
	if (GL_Texture)
	{
		glDeleteTextures(1, &GL_Texture);
		GL_Texture = 0;
	}

}

HRESULT DirectXWindowCapture::init()
{
	HRESULT hr = S_OK;
	hr = initDevice();
	if (FAILED(hr))
	{
		return hr;
	}

    return hr;
}

void DirectXWindowCapture::FindAllWindowTitle(vector<string>& WindowTitle)
{
	if (!AllWindow_HWND.empty())
		AllWindow_HWND.clear();
	// window HWND
	EnumWindows(FindWindowsHandle, reinterpret_cast<LPARAM>(&AllWindow_HWND));
	const DWORD TITLE_SIZE = 512;
	WCHAR f_WindowTitle[TITLE_SIZE];
	WCHAR f_WindowClass[TITLE_SIZE];
    if (!WindowTitle.empty())
		WindowTitle.clear();
	vector<string> s_WindowClass;

	for (int i = 0; i < AllWindow_HWND.size(); i++)
	{
		if (AllWindow_HWND[i] != NULL)
		{
			GetWindowTextW(AllWindow_HWND[i], f_WindowTitle, TITLE_SIZE); //Windows Title
			GetClassNameW(AllWindow_HWND[i], f_WindowClass, TITLE_SIZE);
			wstring title(&f_WindowTitle[0]);
			string tempS;
			tempS.assign(title.begin(), title.end());
			WindowTitle.push_back(tempS);
		}
	}

    for (int i = 0; i < WindowTitle.size(); i++)
	{
		istringstream in(WindowTitle[i]);
		string tempS, tempS1("");
		while (in >> tempS)
		{
			tempS1 = tempS1 + tempS + "_";
		}
		tempS1.pop_back();
		WindowTitle[i] = tempS1;
	}
}

BOOL DirectXWindowCapture::FindWindowsHandle(HWND hwnd, LPARAM lParam)
{
	const DWORD TITLE_SIZE = 512;
	WCHAR windowTitle[TITLE_SIZE];

	GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

	int length = ::GetWindowTextLength(hwnd);
    wstring title(&windowTitle[0]);
	if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager")
	{
		return TRUE;
	}
	if (!CheckWindowValid(hwnd))
	{
		return TRUE;
	}
    std::vector<HWND>& titles = *reinterpret_cast<std::vector<HWND>*>(lParam);
	titles.push_back(hwnd);

	return TRUE;
}

bool DirectXWindowCapture::CheckWindowValid(HWND hWnd)
{
	int CloakedVal;
	bool NotValid;

	HRESULT hRes = DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &CloakedVal, sizeof(CloakedVal));
	if (hRes != S_OK)
	{
		CloakedVal = 0;
	}
    NotValid = CloakedVal ? true : false;
	if (!NotValid)
	{

		DWORD styles, ex_styles;
		RECT  rect;
		if (IsIconic(hWnd))
			return false;
		GetClientRect(hWnd, &rect);
		styles = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
		ex_styles = (DWORD)GetWindowLongPtr(hWnd, GWL_EXSTYLE);
		if (ex_styles & WS_EX_TOOLWINDOW)
			return false;