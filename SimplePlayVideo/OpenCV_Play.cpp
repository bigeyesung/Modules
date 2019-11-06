#include "OpenCV_Play.h"

OpenCV_Play::OpenCV_Play()
{
	m_Reload = false;
	m_Pause = false;
	m_isPlay = false;
}

OpenCV_Play::~OpenCV_Play()
{
	Close();
}