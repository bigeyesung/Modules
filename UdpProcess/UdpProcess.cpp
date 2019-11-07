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