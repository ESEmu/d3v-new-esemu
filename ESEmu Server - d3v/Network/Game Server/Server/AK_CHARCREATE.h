#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_CHARCREATE(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(456);
	pr->GetPB()->WriteHeader(0x00, 0x25);



	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}