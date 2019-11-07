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