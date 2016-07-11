#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_CHECKCHARNAME(Packet* pr, SockHandler* sk, bool Accepted, std::string Name)
{
	pr->GetPB()->Init(72);
	pr->GetPB()->WriteEmptyHeader(0x04, 0x8C);

	if (!Accepted)
		pr->GetPB()->WriteBuffer("\x00\x00\x00\x1A\x00\x00\x00\x01\x4A\x00\x00\x00\x00\x00\x00\x00\x00", 17);
	else
		pr->GetPB()->WriteBuffer("\x00\x00\x00\x24\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 17);

	pr->GetPB()->Append<int>(Name.length());
	pr->GetPB()->WriteUniString((char*)Name.c_str(), Name.length());

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}