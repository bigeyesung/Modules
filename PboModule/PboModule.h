#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <opencv2\opencv.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cv;

class PboProcess
{
public:
	PboProcess();
	~PboProcess();

    void creat(int width, int high, GLenum format = GL_BGR);
	
	void update(int TextureID, Mat& Frame);