#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\Server\AK_LOGIN_CLOSE.h"
#pragma warning( disable: 4996)

void REQ_LOGIN_CLOSE(Packet* pck, SockHandler* sk)
{
	AK_LOGIN_CLOSE(pck, sk);
}