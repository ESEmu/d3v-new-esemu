#pragma once
#include "..\..\..\PacketHandling\PacketBuilder.h"
#pragma warning( disable: 4996)

/*

00 00 00 00 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 
00 01 
00 00 00 26 00 EF 8B 00 00 00 
08 
12 BE 82 C8 48 86 8F F6 ---> HMAC
00 00 00 
08 
DA 74 22 B6 EE D3 F0 D5 ---> DES
00 00 00 01 
00 00 00 00 00 00 00 
00 01 02 02

*/

void AK_KEYEXCHANGE(PacketBuilder* pck, char* HMACKey, char* DESKey)
{
	/*
	pck->CreateBufForSend();
	pck->writeBuf("\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 24);
	pck->writeS(0x0001);
	pck->writeBuf("\x00\x00\x00\x26\x00\xEF\x8B\x00\x00\x00", 10);
	pck->writeC(0x08);
	pck->writeBuf("", 8); // HMAC
	pck->writeBuf("\x00\x00\x00", 3);
	pck->writeC(0x08);
	pck->writeBuf("", 8); // DES
	pck->writeBuf("\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x02", 15);
	pck->PackSend(NULL, NULL);
	*/
}