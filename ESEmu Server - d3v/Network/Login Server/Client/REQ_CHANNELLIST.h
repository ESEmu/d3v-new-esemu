#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\Server\AK_CHANNELLIST.h"
#include "..\Server\AK_CHANNELLIST_ACK.h"
#pragma warning( disable: 4996)

void REQ_CHANNELLIST(Packet* pck, SockHandler* sk)
{
	AK_CHANNELLIST_ACK(pck, sk);
	AK_CHANNELLIST(pck, sk);
}