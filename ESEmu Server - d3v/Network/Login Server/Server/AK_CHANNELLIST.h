#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#pragma warning( disable: 4996)

void AK_CHANNELLIST(Packet* pr, SockHandler* sk)
{
	_CHANNEL_INFO CHList[20];
	memset(CHList, 0x00, sizeof(_CHANNEL_INFO) * 20);
	if (!pr->GetDB()->GetChannelList(sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS), CHList, sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS)))
	{
		printf("[!] No channels?!\n");
		return;
	}

	pr->GetPB()->Init(150 * sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS));
	printf("Channels: %d (Memory Bytes: %d).\n", sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS), 150 * sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS));
	pr->GetPB()->WriteHeader(0x00, 0x41);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS));

	for (auto i = 0; i <= sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS) - 1; i++)
	{
		// Channel Enumeration (IDs & List IDs)
		pr->GetPB()->Append<int>(i + 1);
		pr->GetPB()->Append<int>(4 + (i * 2));
		pr->GetPB()->Append<int>(i + 1);

		// Name properties
		pr->GetPB()->WriteUniString(CHList[i].ChannelName, strlen(CHList[i].ChannelName));
		pr->GetPB()->Append<int>(0);

		// IP Properties
		pr->GetPB()->WriteUniString(CHList[i].IP, strlen(CHList[i].IP));
		printf("Appending Channel %d (%s -> %s).\n", i, CHList[i].ChannelName, CHList[i].IP);

		pr->GetPB()->WriteBuffer("\x24\x54\x24\x55", 4);
		pr->GetPB()->Append<int>(CHList[i].MaxPlayers);
		pr->GetPB()->Append<int>(0xCA);

		pr->GetPB()->WriteBuffer("\x00\x00\x00\x00\x00\x00\x00\x00\x01", 9);
	}

	for (auto k = 0; k < sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS) - 1; k++)
	{
		printf("Appending properties %d.\n", k);
		pr->GetPB()->Append<int>(sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_CHANNELS));
		pr->GetPB()->Append<int>(k + 1);

		pr->GetPB()->Append<char>(0x01);

		pr->GetPB()->Append<int>(0x01);
		pr->GetPB()->Append<int>(CHList[k].LevelLimit);

		pr->GetPB()->Append<int>(0x0A);
		pr->GetPB()->Append<int>(0);
	}
	printf("Sending.\n");
	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}