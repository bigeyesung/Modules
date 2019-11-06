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
    void Play();
	void Pause(bool in) { m_Pause = in; }
	void Stop() { m_Reload = true; m_Pause = true; }

private:

	VideoCapture m_VideoCap;
	Mat tempFrame;
	bool m_Reload;
	bool m_Pause;
	bool m_isPlay;
};