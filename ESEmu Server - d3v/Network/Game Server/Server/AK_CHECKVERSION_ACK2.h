#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_CHECKVERSION_ACK2(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(56);
	pr->GetPB()->WriteHeader(0x04, 0xB6);

	pr->GetPB()->WriteBuffer("\x00\x00\x00\x02\x00\x00\x82\x0A\x00\x00\x00\x82\x14\x00", 14);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}