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

    // copy pixels from PBO to texture object
	// Use offset instead of ponter.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_High, m_format, GL_UNSIGNED_BYTE, 0);

	// bind PBO to update pixel values
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_PboRef->getId());

    glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_iDataSize, 0, GL_STREAM_DRAW_ARB);
	//m_PboPtr = (GLubyte*)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_iDataSize, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	m_PboPtr = (GLubyte*)glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB); ;// (GLubyte*)m_PboRef->map(GL_WRITE_ONLY);
	if (m_PboPtr)
	{
		//console() << "update" << std::endl;
		memcpy(m_PboPtr, (GLubyte*)Frame.data, m_iDataSize);