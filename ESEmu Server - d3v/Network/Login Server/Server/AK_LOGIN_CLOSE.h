#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#pragma warning( disable: 4996)

void AK_LOGIN_CLOSE(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(50);
	pr->GetPB()->WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\xED\x84\xBF\xD4\x2E\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x02\x45\x00\x00\x00\x00\x01\x01", 40);
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}