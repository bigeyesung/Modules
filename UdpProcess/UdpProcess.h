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
