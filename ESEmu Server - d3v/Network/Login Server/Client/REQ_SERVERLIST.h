#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\Server\AK_SERVERLIST.h"
#include "..\Server\AK_SERVERLIST_ACK.h"
#pragma warning( disable: 4996)

void REQ_SERVERLIST(Packet* pck, SockHandler* sk)
{
	AK_SERVERLIST_ACK(pck, sk);
	AK_SERVERLIST(pck, sk);
}