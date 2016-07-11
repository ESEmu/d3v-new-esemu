#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"


void AK_PINCODE_ACK(Packet* pr, SockHandler* sk, bool Valid)
{
	pr->GetPB()->Init(56);
	pr->GetPB()->WriteHeader(0x03, 0x35);
	unsigned int CurrentTrials = sk->GetCFG()->getNumber(sk->GetCFG()->MAX_PINCODE_TRIALS);

	if (Valid)
	{
		pr->GetPB()->Append<int>(0);
		pr->GetPB()->Append<int>(0);
	} else {
		pr->GetPB()->Append<int>(0x0358); // Wrong Code ID!
		pr->GetPB()->Append<int>(--CurrentTrials); // Remaining trials, must be fixed!
	}

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());

	AK_CHARSTREAM_END(pr, sk);
	AK_CHARSTREAM_END_ACK(pr, sk);
}