#pragma once
#ifndef _OPCODES_H_
#define _OPCODES_H_

// -------------------- LOGIN CORE
#define OPCODE_REQ_AUTH							0x0280
#define OPCODE_REQ_DATE							0x0546
#define OPCODE_REQ_KEEPALIVE					0xFFFF
#define OPCODE_REQ_BUG_KEEPALIVE				0xFFFD
#define OPCODE_REQ_SERVERLIST					0x052A
#define OPCODE_REQ_CHANNELLIST					0x003F
#define OPCODE_REQ_LOGIN_CLOSE					0x0244

// -------------------- GAME CORE
#define OPCODE_REQ_CHECKVERSION					0x001A
#define OPCODE_REQ_SESSIONCHECK					0x0357
//#define OPCODE_REQ_SESSIONCHECK2				0x048D
#define OPCODE_REQ_SESSIONCHECK3				0x0033
#define OPCODE_REQ_DATECHECK					0x01FC
#define OPCODE_REQ_CURRENTIP					0x0037
#define OPCODE_REQ_CHARDATA						0x0485
#define OPCODE_REQ_CHECKCHARNAME				0x048B
#define OPCODE_REQ_CREATECHAR					0x0489
#define OPCODE_REQ_CHECKVALIDSERVER				0x048D
#define OPCODE_REQ_AUTHTOKEN					0x001E
#define OPCODE_REQ_RESPONSEPINCODE				0x0334


#include "_Included_OPCodes.h"
#include "Packet Handler\Packet Handler.h"

#define OPCODE(P1, P2) { case P1: P2(pr, sk); break; }

#define PR pr->GetPR()
#define PB pr

#define TOSHORT(Value) ((Value[1] << 8) | Value[0]))

bool DeterminatePacket(Packet* pr, SockHandler* sk)
{
	unsigned short OPCode = NULL;
	PR->Skip(32);
	PR->ReadShort(OPCode);
	printf("OPCode: %02X.\n", OPCode);

	switch (OPCode)
	{
		OPCODE(OPCODE_REQ_AUTH,			REQ_AUTH);
		OPCODE(OPCODE_REQ_DATE,			REQ_DATE);
		OPCODE(OPCODE_REQ_KEEPALIVE,	REQ_KEEPALIVE);
		OPCODE(OPCODE_REQ_BUG_KEEPALIVE,REQ_KEEPALIVE);
		OPCODE(OPCODE_REQ_SERVERLIST,	REQ_SERVERLIST);
		OPCODE(OPCODE_REQ_CHANNELLIST,	REQ_CHANNELLIST);
		OPCODE(OPCODE_REQ_LOGIN_CLOSE,  REQ_LOGIN_CLOSE);
		OPCODE(OPCODE_REQ_CHARDATA,		REQ_CHARDATA);

	default:
		
		// TODO: Log unknown packet.
		//printf("[!] Packet not recognized!\n");
		//PDUMP(PR->GetBuffer(), PR->GetSize());
		return false;
		break;
	}
	return true;
}

bool DeterminateGPacket(Packet* pr, SockHandler* sk)
{
	unsigned short OPCode = NULL;
	PR->Skip(32);
	PR->ReadShort(OPCode);
	//PDUMP(PR->GetBuffer(), PR->GetSize());
	printf("OPCode: %02X.\n", OPCode);

	switch (OPCode)
	{

		OPCODE(OPCODE_REQ_CHECKVERSION,		REQ_CHECKVERSION);
		OPCODE(OPCODE_REQ_AUTH, 			REQ_AUTH);
		OPCODE(OPCODE_REQ_SESSIONCHECK,		REQ_SESSIONCHECK);
		//OPCODE(OPCODE_REQ_SESSIONCHECK2,	REQ_SESSIONCHECK2);
		OPCODE(OPCODE_REQ_DATECHECK,		REQ_DATECHECK);
		OPCODE(OPCODE_REQ_CURRENTIP,		REQ_CURRENTIP);
		OPCODE(OPCODE_REQ_CHECKCHARNAME,	REQ_CHECKCHARNAME);
		OPCODE(OPCODE_REQ_CREATECHAR,		REQ_CHARCREATE);
		OPCODE(OPCODE_REQ_AUTHTOKEN,		REQ_AUTHTOKEN);
		OPCODE(OPCODE_REQ_RESPONSEPINCODE,	REQ_CHECKPINCODE);
		OPCODE(OPCODE_REQ_CHECKVALIDSERVER, REQ_CHECKVALIDSERVER);


	default:

		// TODO: Log unknown packet.
		//printf("[!] Packet not recognized!\n");
		return false;
		break;
	}
	return true;
}

bool TESTDeterminatePacket(Packet* pr, SockHandler* sk)
{
	unsigned short OPCode = NULL;
	PR->Skip(32);
	PR->ReadShort(OPCode);
	//PDUMP(PR->GetBuffer(), PR->GetSize());
	printf("OPCode: %02X.\n", OPCode);

	switch (OPCode)
	{
		OPCODE(OPCODE_REQ_AUTH, REQ_AUTH);
		OPCODE(OPCODE_REQ_DATE, REQ_DATE);
		OPCODE(OPCODE_REQ_KEEPALIVE, REQ_KEEPALIVE);
		OPCODE(OPCODE_REQ_BUG_KEEPALIVE, REQ_KEEPALIVE);
		OPCODE(OPCODE_REQ_SERVERLIST, REQ_SERVERLIST);
		OPCODE(OPCODE_REQ_CHANNELLIST, REQ_CHANNELLIST);
		OPCODE(OPCODE_REQ_LOGIN_CLOSE, REQ_LOGIN_CLOSE);

		OPCODE(OPCODE_REQ_CHARDATA, REQ_CHARDATA);
		OPCODE(OPCODE_REQ_CHECKCHARNAME, REQ_CHECKCHARNAME);
		OPCODE(OPCODE_REQ_CREATECHAR, REQ_CHARCREATE);
		OPCODE(OPCODE_REQ_CHECKVERSION, REQ_CHECKVERSION);
		OPCODE(OPCODE_REQ_SESSIONCHECK, REQ_SESSIONCHECK);
		//OPCODE(OPCODE_REQ_SESSIONCHECK2, REQ_SESSIONCHECK2);
		OPCODE(OPCODE_REQ_SESSIONCHECK3, REQ_SESSIONCHECK3);
		OPCODE(OPCODE_REQ_DATECHECK, REQ_DATECHECK);
		OPCODE(OPCODE_REQ_CURRENTIP, REQ_CURRENTIP);
		OPCODE(OPCODE_REQ_AUTHTOKEN, REQ_AUTHTOKEN);
		OPCODE(OPCODE_REQ_RESPONSEPINCODE, REQ_CHECKPINCODE);
		OPCODE(OPCODE_REQ_CHECKVALIDSERVER, REQ_CHECKVALIDSERVER);
		OPCODE(0x4B1, PDUMP(pr->GetPR()->GetBuffer(), pr->GetPR()->GetSize()));
		OPCODE(0x54D, break;);
		OPCODE(0xFDFD, break;);

		default:

			printf("-------- PACKET NOT RECOGNIZED --------\n");
			PDUMP(pr->GetPR()->GetBuffer(), pr->GetPR()->GetSize());
			printf("---------------------------------------\n");
			return false;
			break;
	}
	return true;
}

unsigned char* DHPacket(unsigned char* Buffer)
{
	PacketBuilder* pr = new(PacketBuilder);
	PB->Init(72);
	PB->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 24);
	PB->WriteOPCode(0x00, 0x01);
	PB->WriteBuffer("\x00\x00\x00\x26\x00\x0F\x32\x00\x00\x00", 10);
	PB->Append<char>(0x08);
	PB->WriteBuffer("\xC0\xD3\xBD\xC3\xB7\xCE\xB8\xB8", 8);
	PB->WriteBuffer("\x00\x00\x00", 3);
	PB->Append<char>(0x08);
	PB->WriteBuffer("\xC7\xD8\xC4\xBF\xB5\xE9\xC0\xFD", 8);
	PB->WriteBuffer("\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x02", 15);

	PB->CopyBuffer(Buffer);

	return Buffer;
}

#endif _OPCODES_H_


