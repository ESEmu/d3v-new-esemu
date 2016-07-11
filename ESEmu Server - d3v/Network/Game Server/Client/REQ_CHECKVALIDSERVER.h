#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CHECKVALIDSERVER.h"

void REQ_CHECKVALIDSERVER(Packet* pr, SockHandler* sk)
{
	AK_CHECKVALIDSERVER_ACK1(pr, sk);
	AK_CHECKVALIDSERVER_ACK2(pr, sk);
	AK_CHECKVALIDSERVER_ACK3(pr, sk);
}