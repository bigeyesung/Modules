#include "TCPbase.h"
TCPbase::TCPbase()
{
	Buf = new char[Bufsize];
	m_ioService = std::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
}
TCPbase::~TCPbase()
{
	delete[] Buf;
}
