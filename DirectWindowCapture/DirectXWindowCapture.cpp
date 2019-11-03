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
        if (styles & WS_CHILD)
			return false;
		if ((rect.bottom == 0 || rect.right == 0))
			return false;
	}
	return !NotValid;
}

HRESULT DirectXWindowCapture::initDevice()
{
	HRESULT hr = S_OK;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE		g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL	 g_featureLevel = D3D_FEATURE_LEVEL_11_0;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &m_D3dDevice, &g_featureLevel, &m_D3dContext);

        	if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &m_D3dDevice, &g_featureLevel, &m_D3dContext);
		}

		if (SUCCEEDED(hr))
			break;
	}

	return S_OK;
}

HRESULT DirectXWindowCapture::CreatTexture(ID3D11Device* Device, int width, int high)
{
	HRESULT hr = S_FALSE;

	if (width > 0 && high > 0)
	{
		if (width != TextureWidth || high != TextureHigh)
		{
			TextureWidth = width;
			TextureHigh = high;
			//if (DX_Texture) DX_Texture->Release();
			//if (m_GdiSurface) m_GdiSurface->Release();
			if (Device) Device->Release();
			DX_Texture = NULL;

            D3D11_TEXTURE2D_DESC TextureDesc;
			memset(&TextureDesc, 0, sizeof(TextureDesc));
			TextureDesc.Width = width;
			TextureDesc.Height = high;
			TextureDesc.MipLevels = 1;
			TextureDesc.ArraySize = 1;
			TextureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			TextureDesc.SampleDesc.Count = 1;
			TextureDesc.CPUAccessFlags = 0;
			TextureDesc.Usage = D3D11_USAGE_DEFAULT;
			TextureDesc.MiscFlags = D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
            hr = Device->CreateTexture2D(&TextureDesc, NULL, &DX_Texture);
			if (FAILED(hr))
				return hr;
			//���otexture Surface���
			hr = DX_Texture->QueryInterface(__uuidof(IDXGISurface1),
				(void**)&m_GdiSurface);
			return hr;
		}
	}
	return S_FALSE;	
}

void DirectXWindowCapture::UpdateHDC()
{
	if (m_Hwnd)
	{
		bool testB = false;
		HDC D3D_hdc = NULL;
		HDC Window_hdc = NULL;

		m_GdiSurface->GetDC(true, &D3D_hdc);
		Window_hdc = GetDC(m_Hwnd);
        BitBlt(D3D_hdc, 0, 0, TextureWidth, TextureHigh, Window_hdc, 0, 0, SRCCOPY);
		memset(&m_MouseInfo.Ci, 0, sizeof(CURSORINFO));
		m_MouseInfo.Ci.cbSize = sizeof(CURSORINFO);
		m_MouseInfo.CursorCaptured = GetCursorInfo(&m_MouseInfo.Ci);
        if (m_MouseInfo.CursorCaptured)
		{
			m_MouseInfo.WinPos.x = 0;
			m_MouseInfo.WinPos.y = 0;
			if (m_Hwnd)
				ClientToScreen(m_Hwnd, &m_MouseInfo.WinPos);

			m_MouseInfo.FinalPos.x = m_MouseInfo.Ci.ptScreenPos.x - m_MouseInfo.WinPos.x;//�����y��
			m_MouseInfo.FinalPos.y = m_MouseInfo.Ci.ptScreenPos.y - m_MouseInfo.WinPos.y;

			DrawIcon(D3D_hdc, m_MouseInfo.FinalPos.x, m_MouseInfo.FinalPos.y, m_MouseInfo.CursorIcon);
		}
		else
		{
			console() << "Stop Draw Mouse" << endl;
		}
		ReleaseDC(NULL, Window_hdc);
		m_GdiSurface->ReleaseDC(nullptr);
	}
}

void DirectXWindowCapture::LockDX()
{
	wglDXLockObjectsNV(m_DX11Device_HANDLE, 1, &m_GLSharedTexture_HANDLE);
}

void DirectXWindowCapture::UnLockDX()
{
	wglDXUnlockObjectsNV(m_DX11Device_HANDLE, 1, &m_GLSharedTexture_HANDLE);
}