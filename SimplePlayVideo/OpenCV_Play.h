#pragma once
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class OpenCV_Play
{
public:
	OpenCV_Play();
	~OpenCV_Play();

    bool GetStatus() { return m_isPlay; }
	//bool SetStatus(bool in) { m_isPlay = in; }

	void LoadFile(string FilePath);
	void Close();