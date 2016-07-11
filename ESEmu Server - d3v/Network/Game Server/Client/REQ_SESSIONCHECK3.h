#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_SESSIONCHECK3.h"

void REQ_SESSIONCHECK3(Packet* pr, SockHandler* sk)
{
	AK_SESSIONCHECK3(pr, sk);
}