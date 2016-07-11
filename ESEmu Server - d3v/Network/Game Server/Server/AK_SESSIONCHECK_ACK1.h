#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_SESSIONCHECK_ACK1(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(72);
	pr->GetPB()->WriteHeader(0x01, 0xA4);

	pr->GetPB()->WriteBuffer("\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 29);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}