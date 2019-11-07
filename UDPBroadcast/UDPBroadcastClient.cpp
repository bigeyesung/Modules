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