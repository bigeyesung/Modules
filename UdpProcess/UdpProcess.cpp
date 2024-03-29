#include "UdpProcess.h"

UdpProcess::UdpProcess()
{
	mReceive = "-1";
}

UdpProcess::~UdpProcess()
{
}

void UdpProcess::init(bool broadcast, int32_t iPort, std::string strHost)
{
	// Initialize a client by passing a boost::asio::io_service to it.
	// ci::App already has one that it polls on update, so we'll use that.
	// You can use your own io_service, but you will have to manage it 
	// manually (i.e., call poll(), poll_one(), run(), etc).
	//m_ioService = shared_ptr<asio::io_service>(new asio::io_service());
	mClient = UdpClient::create(ioserviceManager::getIoService());

    mPort = iPort;
	mHost = strHost;

	// Add callbacks to work with the client asynchronously.
	// Note that you can use lambdas.
	mClient->connectErrorEventHandler(&UdpProcess::onError, this);
	if (!broadcast)
	{
    	mClient->connectConnectEventHandler( &UdpProcess::onConnect, this );
		//mClient->connectResolveEventHandler( [ & ]() 
		//{
		//	mText.push_back( "Endpoint resolved" );
		//} );
		mClient->connectResolveEventHandler(&UdpProcess::onResolve, this);

		//Connect to certain server
		//mText.push_back("Connecting to: " + mHost + ":" + to_string(mPort));
		mClient->connect(mHost, (uint16_t)mPort);
	}
	else
	{
		//Receive Broadcast message
		onConnectBroadcast(mPort);
	}
	
}

void UdpProcess::update()
{
	ioserviceManager::updateIoService();
}

void UdpProcess::onConnect( UdpSessionRef session )
{
	//mText.push_back( "Connected" );
	//ci::app::console() << "Connected" << std::endl;

	// Get the session from the argument and set callbacks.
	// Note that you can use lambdas.
    mSession = session;
	mSession->connectErrorEventHandler( &UdpProcess::onError, this );
	mSession->connectWriteEventHandler( &UdpProcess::onWrite, this );
	mSession->connectReadCompleteEventHandler(&UdpProcess::onReadComplete, this);
	mSession->connectReadEventHandler(&UdpProcess::onRead, this);

	//write();
	mSession->read();
}

void UdpProcess::onError( string err, size_t bytesTransferred )
{
	string text = "Error";
	if ( !err.empty() ) {
		text += ": " + err;
	}
	 //mText.push_back( text );
	//ci::app::console() << text.c_str() << std::endl;
}

void UdpProcess::onWrite( size_t bytesTransferred )
{
	string writeMsg = to_string(bytesTransferred) + " bytes written";
	//mText.push_back( to_string( bytesTransferred ) + " bytes written" );
	ci::app::console() << writeMsg.c_str() << std::endl;
}

void UdpProcess::onResolve()
{
	//mText.push_back("Endpoint resolved");
	ci::app::console() << "Endpoint resolved" << std::endl;

}

void UdpProcess::onRead(ci::BufferRef buffer)
{
	//mText.push_back(to_string(int(buffer->getSize())) + " bytes read");

	// Data is packaged as a ci::Buffer. This allows 
	// you to send any kind of data. Because it's more common to
	// work with strings, the session object has static convenience 
	// methods for converting between std::string and ci::Buffer.
	mReceive.clear();
	mReceive = UdpSession::bufferToString(buffer);
    //ci::app::console() << mReceive.c_str() << std::endl;
	//mText.push_back(response);

	// Continue reading.
	mSession->read();
}

void UdpProcess::onReadComplete()
{
	//mText.push_back("Read complete");
	//ci::app::console() << "Read complete" << std::endl;

	// Continue reading new responses.
	mSession->read();
}

void UdpProcess::onConnectBroadcast(int32_t iPort)
{
	mClient->connectB((uint16_t)iPort);
	mSession = mClient->getSession();
	mSession->connectErrorEventHandler(&UdpProcess::onError, this);
	mSession->connectWriteEventHandler(&UdpProcess::onWrite, this);
	mSession->connectReadCompleteEventHandler(&UdpProcess::onReadComplete, this);
	mSession->connectReadEventHandler(&UdpProcess::onRead, this);

	mSession->read();
}

void UdpProcess::write()
{
	// This sample is meant to work with only one session at a time.
	if ( mSession && mSession->getSocket()->is_open() ) {
		// Write data is packaged as a ci::Buffer. This allows 
		// you to send any kind of data. Because it's more common to
		// work with strings, the session object has static convenience 
		// methods for converting between std::string and ci::Buffer.
		mSession->write( UdpSession::stringToBuffer( mRequest ) );

    }
	//else {
	//	// Before we can write, we need to establish a connection 
	//	// and create a session. Check out the onConnect method.
	//	mText.push_back( "Connecting to: " + mHost + ":" + toString( mPort ) );
	//	mClient->connect( mHost, (uint16_t)mPort );
	//}
}