#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_SESSIONCHECK3(Packet* pr, SockHandler* sk)
{	
	pr->GetPR()->Skip(5);

	pr->GetPB()->Init(60);
	pr->GetPB()->WriteHeader(0x00, 0x34);

	pr->GetPB()->Append<int>(0);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}