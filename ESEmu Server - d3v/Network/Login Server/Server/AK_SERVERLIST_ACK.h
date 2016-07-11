#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#pragma warning( disable: 4996)

void AK_SERVERLIST_ACK(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(60);
	pr->GetPB()->WriteHeader(0x05, 0x2B);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}