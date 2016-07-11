#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_CHECKVERSION_ACK1(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(48);
	pr->GetPB()->WriteHeader(0x04, 0xB5);

	pr->GetPB()->Append<int>(0x4B);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}