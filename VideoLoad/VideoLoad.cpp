#include "VideoLoad.h"

VideoLoad::VideoLoad()
{
	Video_Th = NULL;
}

VideoLoad::~VideoLoad()
{
	EndThread();

	for (int i = 0; i < m_VideoLoad.size(); i++)
	{
		for (int j = 0; j < m_VideoLoad[i].imageMat1.size(); j++)
		{
			m_VideoLoad[i].imageMat1[j].release();
		}
        for (int j = 0; j < m_VideoLoad[i].imageMat2.size(); j++)
		{
			m_VideoLoad[i].imageMat2[j].release();
		}
	}
}

void VideoLoad::init(const vector<string>& VideoPath, int OneBufferNum)
{
	bool tempB = true;
	string tempS = VideoPath[0];
	for (int i = 1; i < VideoPath.size(); i++)
	{
		if (tempS != VideoPath[i] && VideoPath[i] != "")
			tempB = false;
	}
	ReleaseVideo();

	if (tempB)
		m_VideoLoad.resize(1);
	else
		m_VideoLoad.resize(VideoPath.size());
	VideoTextureArray.resize(m_VideoLoad.size());
	PboArray.resize(m_VideoLoad.size());
	for (int i = 0; i < m_VideoLoad.size(); i++)
	{
		//m_VideoLoad[i].VideoCap.release();
		m_VideoLoad[i].VideoCap.open(VideoPath[i]);
		m_VideoLoad[i].currentFrame = 0;
		m_VideoLoad[i].keepLoading = true;
		m_VideoLoad[i].reloadImage = false;
	}
    CurrentLoadBuffer = -1;
	m_BufferNum = OneBufferNum;
	CurrentBindBuffer = 0;
	m_iPreviousFrameIdx = -1;
	m_iCurrentBindImgIdx = 0;
	m_iPrevBindBufIdx = 0;
	isReload = true;
}

void VideoLoad::InitThread()
{
	if (Video_Th == NULL)
		Video_Th = new thread(&VideoLoad::LoadingVideo, this);
}