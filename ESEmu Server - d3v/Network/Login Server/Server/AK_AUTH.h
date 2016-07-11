#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\..\Common\Random.h";
#include "..\..\SockHandler.h"
#pragma warning( disable: 4996)

/* 00 00 01 01 00 00 00 01 40 00 00 76 E2 D4 46 73 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 
   02 81 
   00 00 00 1C 
   00 00 
   00 
   05 7C | 02 FD | 02 FE
   00 
   00 00 00 00 A5 00 
   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
   00 01 02 03 04 04 
   */

#define REASON_NONE		0
#define REASON_BAD_DATA	1
#define REASON_BANNED	2

void AK_AUTH(Packet* pck, SockHandler* sk, bool succesful, char* Username, int account_id, short Reason)
{	
	if (!succesful)
	{
		switch (Reason)
		{
		case REASON_BAD_DATA:
			// 02 FD
			pck->GetPB()->Init(80);
			pck->GetPB()->WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\x9D\xC9\x86\x9F\x67\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 32);
			pck->GetPB()->WriteOPCode(0x02, 0x81);
			pck->GetPB()->WriteBuffer("\x00\x00\x00\x20\x00\x00\x00", 7);
			pck->GetPB()->WriteBuffer("\x02\xFE", 2);
			pck->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x08", 37);
			SEND;
			break;
		case REASON_BANNED:
			// 05 7C
			pck->GetPB()->Init(80);
			pck->GetPB()->WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\x9D\xC9\x86\x9F\x67\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 32);
			pck->GetPB()->WriteOPCode(0x02, 0x81);
			pck->GetPB()->WriteBuffer("\x00\x00\x00\x20\x00\x00\x00", 7);
			pck->GetPB()->WriteBuffer("\x05\x7C", 2);
			pck->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x08", 37);
			SEND;
			break;
		}
		//pck->Disconnect();
		return;
	}

	std::string Usr(Username);
	sk->setAccName(Usr);
	sk->setAccID((unsigned long long)account_id);

	pck->GetPB()->Init(150);
	pck->GetPB()->WriteHeader(0x02, 0x81);
	pck->GetPB()->Append<long long>(0);
	pck->GetPB()->Append<int>(account_id);
	
	std::string serial = Random::numeric(10);
	std::string serial2 = std::to_string(account_id + 1000000);
	if (Username != "")
		pck->GetDB()->UpdateLoginSerial((char *)serial.c_str(), Username);
	else
		pck->GetDB()->UpdateLoginSerial((char *)serial.c_str(), account_id);

	pck->GetPB()->WriteUniString((char*)serial.c_str(), serial.length());
	pck->GetPB()->Append<int>(0);
	pck->GetPB()->WriteUniString((char*)serial2.c_str(), serial2.length());
	pck->GetPB()->Append<long long>(0);
	pck->GetPB()->WriteEnd();
	SEND;
	
}