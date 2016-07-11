#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CHARDATA.h"
#include "..\Server\AK_CHARDATA_ACK1.h"
#include "..\Server\AK_CHARDATA_ACK2.h"
#include "..\Server\AK_PINCODE_REQ.h"

void REQ_CHARDATA(Packet* pr, SockHandler* sk)
{
	AK_CHARDATA(pr, sk);
	if (pr->GetDB()->IsPINCodeProtected(sk->getAccID()))
		AK_PINCODE_REQ(pr, sk);
	AK_CHARSTREAM_END(pr, sk);
	AK_CHARSTREAM_END_ACK(pr, sk);
}