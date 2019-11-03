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


TcpServer::~TcpServer()
{
	mAcceptEventHandler = nullptr;
	mCancelEventHandler = nullptr;
	cancel();
}

void TcpServer::accept( uint16_t port )
{
	if ( mAcceptor ) {
		mAcceptor.reset();
	}
	mAcceptor				= TcpAcceptorRef( new tcp::acceptor( mIoService, tcp::endpoint( tcp::v4(), port) ) );
	TcpSessionRef session	= TcpSession::create( mIoService );

    mAcceptor->async_accept( *session->mSocket, 
    mStrand.wrap( std::bind( &TcpServer::onAccept, shared_from_this(),
        session, std::placeholders::_1/*error*/ ) ) );
}

void TcpServer::cancel()
{
	if ( mAcceptor ) {
		asio::error_code err;
		mAcceptor->cancel( err );
		if ( err ) {
			if ( mErrorEventHandler != nullptr ) {
				mErrorEventHandler( err.message(), 0 );
			}
        } else {
			if ( mCancelEventHandler != nullptr ) {
				mCancelEventHandler();
			}
		}
	}
}

TcpAcceptorRef TcpServer::getAcceptor() const
{
	return mAcceptor;
}