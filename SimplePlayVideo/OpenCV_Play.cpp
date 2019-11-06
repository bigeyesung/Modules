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

void OpenCV_Play::LoadFile(string FilePath)
{
	m_VideoCap.release();
	m_VideoCap.open(FilePath);
	if (m_VideoCap.isOpened())
	{	m_isPlay = true;
		m_Reload = false;
		m_Pause = false;
	}
	else
	{
        m_isPlay = false;
		m_Reload = false;
		m_Pause = false;
	}
}