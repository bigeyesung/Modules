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

void OpenCV_Play::Close()
{
	if (m_VideoCap.isOpened())
	{
		m_isPlay = false;
		m_VideoCap.release();
		tempFrame.release();
        //destroyAllWindows();
		destroyWindow("Play Video");
		m_Reload = false;
		m_Pause = false;
	}
}

void OpenCV_Play::Play()
{
	if (m_VideoCap.isOpened())
	{
		if (m_Reload)//
		{
			m_VideoCap.set(CAP_PROP_POS_FRAMES, 0);
			m_Reload = false;
		}
        if (!m_Pause)//
		{
			m_VideoCap >> tempFrame;
		}
		if (tempFrame.empty())//
		{
			m_Reload = true;
			return;
		}
		imshow("Play Video", tempFrame);
	}

}