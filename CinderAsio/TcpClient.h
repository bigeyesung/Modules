#pragma once

#include "ClientInterface.h"
#include "TcpSession.h"

typedef std::shared_ptr<class TcpClient>			TcpClientRef;
typedef std::shared_ptr<asio::ip::tcp::resolver>	TcpResolverRef;

class TcpClient : public ClientInterface, public std::enable_shared_from_this<TcpClient>
{
public:
	static TcpClientRef	create( asio::io_service& io );
	~TcpClient();

    virtual void	connect( const std::string& host, uint16_t port );
	virtual void	connect( const std::string& host, const std::string& protocol );

	template< typename T, typename Y >
	inline void		connectConnectEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectConnectEventHandler( std::bind( eventHandler, eventHandlerObject, std::placeholders::_1 ) );
	}