#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>  //get time
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/host_name.hpp>                //get PC name

#include "../Modules/DebugModule/DebugClass.h"

#pragma once
#pragma comment(lib, "IPHLPAPI.lib")
using namespace boost::posix_time;

class UDPBroadcastClient
{
private:
	std::string ServerIP;
	int totalclient;
	boost::asio::io_service io_service_;
	boost::asio::ip::udp::socket _socket;
	boost::array<char, 1024> buffer;
	boost::asio::ip::udp::endpoint sender_endpoint;

	int ReceiveNum;
public:
	UDPBroadcastClient(const int& listenport);
	~UDPBroadcastClient();
	void OpenSocket(int port);
	void CloseSocket();
	void Listen();
	void HandleReceive(const boost::system::error_code& error,std::size_t bytes_transferred);
	void handleSend(std::shared_ptr<std::string> message, const boost::system::error_code& ec, std::size_t bytes_transferred);
	void AsynUpdate();