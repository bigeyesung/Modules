#pragma once

#include "DispatcherInterface.h"
#include "cinder/Buffer.h"

class SessionInterface : public DispatcherInterface
{
public:

    static std::string		bufferToString( const ci::BufferRef& buffer );
	static ci::BufferRef	stringToBuffer( std::string& value );

	~SessionInterface();

    virtual void			read() = 0;
	virtual void			write( const ci::BufferRef& buffer ) = 0;
	virtual void			writeTo(const ci::BufferRef& buffer) = 0;

	template< typename T, typename Y >
	inline void				connectReadEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectReadEventHandler( std::bind( eventHandler, eventHandlerObject, std::placeholders::_1 ) );
	}