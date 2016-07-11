#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\Server\AK_DATE.h"
#pragma warning( disable: 4996)

void REQ_DATE(Packet* pck, SockHandler* sk)
{
	AK_DATE(pck, sk);
}