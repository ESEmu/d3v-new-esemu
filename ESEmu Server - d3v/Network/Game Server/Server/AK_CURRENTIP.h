#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"

void AK_CURRENTIP(Packet* pr, SockHandler* sk)
{
	printf("------- Writing server verify packet.\n");
	pr->GetPB()->Init(90);
	pr->GetPB()->WriteHeader(0x00, 0x38);

	pr->GetPB()->Append<int>(0x00);

	pr->GetPB()->WriteUniString((char*)sk->GetCFG()->getString(sk->GetCFG()->SERVER_IP).c_str(), strlen(sk->GetCFG()->getString(sk->GetCFG()->SERVER_IP).c_str()));

	pr->GetPB()->Append<short>(9300);
	pr->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00", 8);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}