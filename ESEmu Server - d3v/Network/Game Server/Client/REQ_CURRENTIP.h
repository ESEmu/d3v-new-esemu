#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CURRENTIP.h"

void REQ_CURRENTIP(Packet* pr, SockHandler* sk)
{
	AK_CURRENTIP(pr, sk);
}