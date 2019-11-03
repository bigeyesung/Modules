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