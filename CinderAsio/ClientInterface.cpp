#include "ClientInterface.h"

ClientInterface::ClientInterface( asio::io_service& io )
	: DispatcherInterface( io ), mResolveEventHandler( nullptr )
{
}