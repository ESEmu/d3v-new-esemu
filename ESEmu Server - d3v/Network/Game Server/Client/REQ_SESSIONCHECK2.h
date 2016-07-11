#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_SESSIONCHECK2.h"

void REQ_SESSIONCHECK2(Packet* pr, SockHandler* sk)
{
	AK_SESSIONCHECK2(pr, sk);
}