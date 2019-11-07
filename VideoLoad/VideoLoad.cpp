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

void VideoLoad::EndThread()
{
	VideoThreadStat = false;
	if (Video_Th != NULL)
	{
		Video_Th->join();
		delete Video_Th;
		Video_Th = NULL;
	}
}

void VideoLoad::ReleaseVideo()
{
	for (int i = 0; i < m_VideoLoad.size(); i++)
	{
		m_VideoLoad[i].VideoCap.release();
	}
	m_VideoLoad.clear();
}

bool VideoLoad::LoadVideoFirst()
{
	if (Video_Th == NULL)
	{
		int FailedIndex = -1;
		for (int k = 0; k < m_VideoLoad.size(); k++)
		{
			if (!m_VideoLoad[k].VideoCap.isOpened())
			//if (!m_VideoLoad[k].mediaCapture->isOpened())
			{
				console() << "Video Open Failed" << endl;
				FailedIndex = k;
				break;
				//return false;
			}
            m_VideoLoad[k].TotalFrame = m_VideoLoad[k].VideoCap.get(CV_CAP_PROP_FRAME_COUNT);
			//m_VideoLoad[k].TotalFrame = m_VideoLoad[k].mediaCapture->getFrameCount();
			if (!m_VideoLoad[k].imageMat1.empty())
				m_VideoLoad[k].imageMat1.clear();
			for (int i = 0; i < m_BufferNum; i++)
			{
				cv::Mat tempFrame;				
				if (m_VideoLoad[k].VideoCap.read(tempFrame))
				{
					m_VideoLoad[k].imageMat1.push_back(tempFrame);
					m_VideoLoad[k].currentFrame++;
				}
			}
			if (!m_VideoLoad[k].imageMat2.empty())
				m_VideoLoad[k].imageMat2.clear();
            for (int i = 0; i < m_BufferNum; i++)
			{
				cv::Mat tempFrame;				
				if (m_VideoLoad[k].VideoCap.read(tempFrame))
				{
					m_VideoLoad[k].imageMat2.push_back(tempFrame);
					m_VideoLoad[k].currentFrame++;
				}
			}
			//if (VideoTextureArray[k] == NULL)
			{
				VideoTextureArray[k] = gl::Texture::create((unsigned char*)m_VideoLoad[k].imageMat1[0].data, GL_BGR,
					m_VideoLoad[k].imageMat1[0].cols, m_VideoLoad[k].imageMat1[0].rows);
				if(m_VideoLoad.size() == 1)
					VideoTextureArray[k]->bind(0);
				else
					VideoTextureArray[k]->bind(k + 1);
				//pbo creat
				PboArray[k].creat(m_VideoLoad[k].imageMat1[0].cols, m_VideoLoad[k].imageMat1[0].rows);
			}
		}
	if (FailedIndex > 0)
		{
			m_VideoLoad.resize(FailedIndex);
		}
		else if (FailedIndex == 0)
		{
			m_VideoLoad.clear();
		}
		return true;
	}
	else
	{
		//Video_Th = new thread(&VideoLoad::LoadingVideo, this);
		return false;
	}
}

void VideoLoad::LoadingVideo()
{
	VideoThreadStat = true;
	while (VideoThreadStat)
	{
		switch (CurrentLoadBuffer)
		{
		case 0:
		{
			for (int i = 0; i < m_VideoLoad.size(); i++)
			{
				for (int LIj = 0; LIj < m_BufferNum; LIj++)
				{
					if (m_VideoLoad[i].currentFrame >= m_VideoLoad[i].TotalFrame)
					{
						console() << "Buffer1 end: " << m_VideoLoad[0].currentFrame << endl;
						m_VideoLoad[i].VideoCap.set(CAP_PROP_POS_FRAMES, 0);
						//m_VideoLoad[i].mediaCapture->reset();
						m_VideoLoad[i].currentFrame = 0;
						m_VideoLoad[i].keepLoading = false;
						m_VideoLoad[i].reloadImage = true;
						//m_bKeepLoading = false;
						//m_bReload = true;
						LIj = m_BufferNum;
					}
                    if (m_VideoLoad[i].keepLoading)
					{
						//�T�O����s�e��
						m_VideoLoad[i].imageMat1[LIj].release();
						do
						{
							m_VideoLoad[i].VideoCap.read(m_VideoLoad[i].imageMat1[LIj]);
						} while (m_VideoLoad[i].imageMat1[LIj].empty());

						//while (!m_VideoLoad[i].VideoCap.read(m_VideoLoad[i].imageMat1[LIj]))
						//{
						//	//LIj = m_BufferNum;
						//}
						//else
						{
							m_VideoLoad[i].currentFrame++;
							//console() << "Buffer1 load: " << m_VideoLoad[i].currentFrame << endl;
						}					
					}
				}
			}
			CurrentLoadBuffer = -1;
		}
		break;