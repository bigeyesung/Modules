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