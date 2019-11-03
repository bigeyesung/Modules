#pragma once

#include "DispatcherInterface.h"
class ClientInterface : public DispatcherInterface
{
    public:
	~ClientInterface();

	virtual void		connect( const std::string& host, uint16_t port ) = 0;
	virtual void		connect( const std::string& host, const std::string& protocol ) = 0;
