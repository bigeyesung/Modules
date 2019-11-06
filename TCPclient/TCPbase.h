#pragma once
//boost
#include <boost\asio.hpp>
#include <string>
#include <sstream>
#define Bufsize 10000000	//Point

using namespace std;
using namespace boost::asio;
typedef std::shared_ptr<ip::tcp::socket>	pTcpServerRef;
typedef boost::asio::io_service				tIOService;
typedef std::shared_ptr<tIOService>			tIOServiceRef;
