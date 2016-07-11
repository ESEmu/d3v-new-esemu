#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\Server\AK_KEEPALIVE.h"

void REQ_KEEPALIVE(Packet* pr, SockHandler* sk)
{
	AK_KEEPALIVE(pr, sk);
}