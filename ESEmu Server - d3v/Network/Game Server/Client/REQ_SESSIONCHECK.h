#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_SESSIONCHECK.h"

void REQ_SESSIONCHECK(Packet* pr, SockHandler* sk)
{
	AK_SESSIONCHECK(pr, sk);
}