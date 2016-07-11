#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_PINCODE_REQ(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(104);
	pr->GetPB()->WriteHeader(0x03, 0x10);

	pr->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF", 17);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}

void AK_CHARSTREAM_END(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(48);
	pr->GetPB()->WriteHeader(0x05, 0x70);

	pr->GetPB()->Append<unsigned int>(0);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}

void AK_CHARSTREAM_END_ACK(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(64);
	pr->GetPB()->WriteHeader(0x03, 0x10);

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<char>(0);
	pr->GetPB()->Append<unsigned int>(-1);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}