#pragma once

#include "DispatcherInterface.h"
#include "cinder/Buffer.h"

class SessionInterface : public DispatcherInterface
{
public:

    static std::string		bufferToString( const ci::BufferRef& buffer );
	static ci::BufferRef	stringToBuffer( std::string& value );

	~SessionInterface();