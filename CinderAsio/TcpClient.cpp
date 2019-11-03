#include "TcpClient.h"

#include "cinder/Utilities.h"

using namespace ci;
using namespace std;
using asio::ip::tcp;

TcpClientRef TcpClient::create( asio::io_service& io )
{
	return TcpClientRef( new TcpClient( io ) )->shared_from_this();
}

TcpClient::TcpClient( asio::io_service& io )
	: ClientInterface( io ), mConnectEventHandler( nullptr )
{
}

TcpClient::~TcpClient()
{
	mConnectEventHandler = nullptr;
}

void TcpClient::connect( const string& host, uint16_t port )
{
	connect( host, toString( port ) );
}