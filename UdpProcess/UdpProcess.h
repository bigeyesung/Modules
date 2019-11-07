#pragma once

#include "..\Modules\CinderAsio\CinderAsio.h"

#include "cinder/app/App.h"
//#include "cinder/Font.h"
#include "cinder/gl/gl.h"
//#include "cinder/params/Params.h"

#include "..\Modules\CinderAsio\UdpClient.h"

typedef std::shared_ptr<asio::io_service> IOServiceRef;

using namespace std;

class ioserviceManager
{
public:
	ioserviceManager()
	{
		m_ioService = std::shared_ptr<asio::io_service>(new asio::io_service());
	}
    virtual ~ioserviceManager()
	{
		cinder::app::console() << "deconstruct ioservice" << std::endl;
		m_ioService->stop();
	}

	void updateIoService()
	{
		m_ioService->poll();
	}
protected:
	asio::io_service&	getIoService() { return *m_ioService; }
private:
	IOServiceRef m_ioService;
};

class UdpProcess : public ioserviceManager
{
public:
	UdpProcess();
	~UdpProcess();

	void init(bool broadcast, int32_t iPort, std::string strHost);
	void update();
    void setNumber(int value)
	{
		mReceive = to_string(value);
	}
	int getNumber()
	{
		return atoi(mReceive.c_str());
	}

private:
	UdpClientRef				mClient;
	std::string					mHost;
	int32_t						mPort;
	std::string					mRequest;
	UdpSessionRef				mSession;
	std::string                 mReceive;

