#include "PboModule.h"
PboProcess::PboProcess()
{

}
PboProcess::~PboProcess()
{

}

void PboProcess::creat(int width, int high, GLenum format)
{
	m_Width = width;
	m_High = high;
	m_format = format;
	//GL_BGR 
	m_iDataSize = m_Width*m_High * 3;
	m_PboRef = ci::gl::Pbo::create(GL_PIXEL_UNPACK_BUFFER, m_iDataSize, 0, GL_STREAM_DRAW);
}

void PboProcess::update(int TextureID, Mat& Frame)
{
	//// bind the texture and PBO
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_PboRef->getId());