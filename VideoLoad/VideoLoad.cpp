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