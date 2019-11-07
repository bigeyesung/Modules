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