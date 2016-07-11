#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\..\..\Common\Time.h"

void AK_DATECHECK(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(104);
	pr->GetPB()->WriteHeader(0x01, 0xFD);

	std::string timenow = Time::now();
	pr->GetPB()->WriteUniString((char*)timenow.c_str(), timenow.length());
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(Time::timestamp());

	pr->GetPB()->WriteBuffer("\x00\x00\x12\x53\xAD\x6A\x9B\x7B", 8);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}