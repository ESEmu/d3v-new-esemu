#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_SESSIONCHECK2(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(200);
	pr->GetPB()->WriteHeader(0x04, 0x8F);

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(sk->getAccID());
	pr->GetPB()->Append<int>(1);
	pr->GetPB()->Append<long long>(0);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}