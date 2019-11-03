#include "TcpServer.h"

#include "cinder/Utilities.h"

using namespace ci;
using namespace std;
using asio::ip::tcp;

TcpServerRef TcpServer::create( asio::io_service& io )
{
	return TcpServerRef( new TcpServer( io ) )->shared_from_this();
}

TcpServer::TcpServer( asio::io_service& io )
	: ServerInterface( io ), mAcceptEventHandler( nullptr ), mCancelEventHandler( nullptr )
{
}