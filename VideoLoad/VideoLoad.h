#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "cinder/gl/gl.h"
#include <cinder\app\AppBase.h>

#include "../Modules/PboModule/PboModule.h"

using namespace ci::app;
using namespace ci;

using namespace std;
using namespace cv;

typedef struct
{
	cv::VideoCapture VideoCap;
	
	vector<cv::Mat> imageMat1, imageMat2;

	long unsigned TotalFrame;
    long unsigned currentFrame;
	bool keepLoading;
	bool reloadImage;

}VideoLoadData;

class VideoLoad
{
public:
	VideoLoad();
	~VideoLoad();
	
	void init(const vector<string>& VideoPath, int OneBufferNum = 10);
	bool LoadVideoFirst();

    void InitThread();

	void EndThread();

	void ReleaseVideo();

	void LoadingVideo();


	void ReloadVideo();

	void BindVideoTexture(int frameIdx);

	void UnbindVideoTexture();
	
	int GetLoadVideoNum() { return m_VideoLoad.size(); }
private:

	vector<VideoLoadData> m_VideoLoad;
	int m_BufferNum;	
	int CurrentLoadBuffer;
	int CurrentBindBuffer;

	int m_iPreviousFrameIdx;
	int m_iCurrentBindImgIdx;
	int m_iPrevBindBufIdx;

	thread* Video_Th;
	bool VideoThreadStat;

	bool isReload;