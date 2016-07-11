#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_DATECHECK.h"

void REQ_DATECHECK(Packet* pr, SockHandler* sk)
{
	AK_DATECHECK(pr, sk);
}