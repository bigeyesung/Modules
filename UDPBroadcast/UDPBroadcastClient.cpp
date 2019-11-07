//#include "stdafx.h"
#include "UDPBroadcastClient.h"
//#include "QDebug"  //chenhsi add

using boost::asio::ip::udp;

UDPBroadcastClient::UDPBroadcastClient(const int& listenport) : _socket(io_service_, udp::endpoint(udp::v4(), listenport))
{
	// Client binds to any address on listenport (the same port on which
	// broadcast data is sent from server).
	ServerIP = "None";
	is_serverip = false;
	ReceiveNum = 0;
	//Listen();
}

UDPBroadcastClient::~UDPBroadcastClient()
{
	_socket.close();
	ipaddrs.clear();
}

void UDPBroadcastClient::OpenSocket(int port)
{
	if(!_socket.is_open())
		_socket= boost::asio::ip::udp::socket(io_service_, udp::endpoint(udp::v4(), port));
}

void UDPBroadcastClient::CloseSocket()
{
	_socket.close();
}

void UDPBroadcastClient::Listen()
{
	ServerIP = "None";
	buffer.assign(0);
	// Receive data.
		_socket.async_receive_from(
			boost::asio::buffer(buffer, buffer.size()), sender_endpoint,
			boost::bind(&UDPBroadcastClient::HandleReceive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
}

void UDPBroadcastClient::AsynUpdate()
{
	io_service_.poll();
}

void UDPBroadcastClient::HandleReceive(const boost::system::error_code& error,
	std::size_t bytes_transferred)
{
	printf("HandleReceive.\n");
	
	std::string transfercontent = std::string(buffer.begin(), buffer.begin() + bytes_transferred);
	std::cout << transfercontent << std::endl;
	DebugClass debugF;
	//std::string tempS;
	if (transfercontent == "Broadcast_message")
	{
		ServerIP = sender_endpoint.address().to_string();
		debugF.CinderConsoleNextLine(ServerIP);
		ReceiveNum++;
	}
    if (ServerIP != "None")
	 is_serverip = true;
	
	io_service_.reset();

	//Send confirmed mes to server
	//auto message = std::make_shared<std::string>(ServerIP + "@" + boost::asio::ip::host_name());
	//udp::resolver resolver(io_service_);
	//udp::resolver::query query(udp::v4(), ServerIP, "7029");
	//udp::resolver::iterator iter = resolver.resolve(query);
	//udp::endpoint remote_endpoint = *iter;

	//	_socket.async_send_to(boost::asio::buffer(*message), remote_endpoint,
	//		boost::bind(&UDPBroadcastClient::handleSend, this, message,
	//			boost::asio::placeholders::error,
	//			boost::asio::placeholders::bytes_transferred));





}

void UDPBroadcastClient::handleSend(std::shared_ptr<std::string> message, const boost::system::error_code & ec, std::size_t bytes_transferred)
{
	printf("send.\n");
}