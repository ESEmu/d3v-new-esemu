#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\..\..\Common\Time.h"
#pragma warning( disable: 4996)

void AK_DATE(Packet* pr, SockHandler* sk)
{
	pr->GetPB()->Init(88);
	pr->GetPB()->WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\xE9\x31\x5E\xD5\xC9\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 32);
	pr->GetPB()->WriteOPCode(0x05, 0x45);
	pr->GetPB()->WriteBuffer("\x00\x00\x00\x2A\x00", 5);
	pr->GetPB()->WriteUniString((char*)Time::now().c_str(), 19);
	pr->GetPB()->WriteBuffer("\x01\x02\x03\x04\x05\x06\x06", 7);
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}