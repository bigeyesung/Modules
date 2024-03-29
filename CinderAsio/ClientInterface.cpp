#include "ClientInterface.h"

ClientInterface::ClientInterface( asio::io_service& io )
	: DispatcherInterface( io ), mResolveEventHandler( nullptr )
{
}

ClientInterface::~ClientInterface()
{
	mResolveEventHandler = nullptr;
}

void ClientInterface::connectResolveEventHandler( const std::function<void ()>& eventHandler )
{
	mResolveEventHandler = eventHandler;
}