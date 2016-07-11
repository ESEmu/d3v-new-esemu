#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_SESSIONCHECK_ACK2(Packet* pr, SockHandler* sk)
{

	pr->GetPB()->Init(56);
	pr->GetPB()->WriteHeader(0x03, 0x9A);

	pr->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00", 8);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}

void AK_SESSIONCHECK_ACK3(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(100);
	pr->GetPB()->WriteHeader(0x03, 0x58);

	unsigned int length;
	unsigned char chr;

	pr->GetPR()->ReadInt(length);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(length);
	for (int i = 0; i < length; i++) {
		pr->GetPR()->ReadByte(chr);
		pr->GetPB()->Append<unsigned char>(chr);
	}

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}