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
    void					connectReadEventHandler( const std::function<void( ci::BufferRef )>& eventHandler );

    template< typename T, typename Y >
	inline void				connectReadCompleteEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectReadCompleteEventHandler( std::bind( eventHandler, eventHandlerObject ) );
	}
	void					connectReadCompleteEventHandler( const std::function<void ()>& eventHandler );


    template< typename T, typename Y >
	inline void				connectWriteEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectWriteEventHandler( std::bind( eventHandler, eventHandlerObject, std::placeholders::_1 ) );
	}
	void					connectWriteEventHandler( const std::function<void( size_t )>& eventHandler );

    template< typename T, typename Y >
	inline void				connectWriteToEventHandler(T eventHandler, Y* eventHandlerObject)
	{
		connectWriteToEventHandler(std::bind(eventHandler, eventHandlerObject, std::placeholders::_1));
	}
	void					connectWriteToEventHandler(const std::function<void(size_t)>& eventHandler);


    protected:
	SessionInterface( asio::io_service& io );

	virtual void			onRead( const asio::error_code& err, size_t bytesTransferred );
	virtual void			onWrite( const asio::error_code& err, size_t bytesTransferred );
	virtual void			onWriteTo(const asio::error_code& err, size_t bytesTransferred);

    size_t					mBufferSize;
	asio::streambuf			mRequest;
	asio::streambuf			mResponse;

    std::function<void ()>					mReadCompleteEventHandler;
	std::function<void( ci::BufferRef )>	mReadEventHandler;
    std::function<void( size_t )>			mWriteEventHandler;
	std::function<void(size_t)>				mWriteToEventHandler;
};