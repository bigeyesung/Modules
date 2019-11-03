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