#include "DispatcherInterface.h"

DispatcherInterface::DispatcherInterface( asio::io_service& io )
	: mErrorEventHandler( nullptr ), mIoService( io ), mStrand( io )
{
}

DispatcherInterface::~DispatcherInterface()
{
	mErrorEventHandler = nullptr;
}