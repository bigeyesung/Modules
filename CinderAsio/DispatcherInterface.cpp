#include "DispatcherInterface.h"

DispatcherInterface::DispatcherInterface( asio::io_service& io )
	: mErrorEventHandler( nullptr ), mIoService( io ), mStrand( io )
{
}

DispatcherInterface::~DispatcherInterface()
{
	mErrorEventHandler = nullptr;
}

void DispatcherInterface::connectErrorEventHandler( const std::function<void( std::string, size_t )>& eventHandler )
{
	mErrorEventHandler = eventHandler;
}
