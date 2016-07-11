#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "AK_CHECKVERSION_ACK1.h"
#include "AK_CHECKVERSION_ACK2.h"
#include "AK_CHECKVERSION_ACK3.h"


void AK_CHECKVERSION(Packet* pr, SockHandler* sk)
{
	AK_CHECKVERSION_ACK1(pr, sk);
	AK_CHECKVERSION_ACK2(pr, sk);
	AK_CHECKVERSION_ACK3(pr, sk);

	pr->GetPB()->Init(56);
	pr->GetPB()->WriteHeader(0x00, 0x1B);

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(0x2455);
	pr->GetPB()->Append<int>(8);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}