#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_PINCODE_ACK.h"

void REQ_CHECKPINCODE(Packet* pr, SockHandler* sk)
{
	unsigned int PINSize = NULL;
	pr->GetPR()->ReadInt(PINSize);
	string GivenPIN = pr->GetPR()->ReadUniString(PINSize);
	string PIN = pr->GetDB()->GetPINCode(sk->getAccID());

	if (!strcmp(GivenPIN.c_str(), PIN.c_str()))
		AK_PINCODE_ACK(pr, sk, true);
	else
		AK_PINCODE_ACK(pr, sk, false);
}