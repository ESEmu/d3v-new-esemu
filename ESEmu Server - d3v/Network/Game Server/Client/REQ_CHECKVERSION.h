#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CHECKVERSION.h"

void REQ_CHECKVERSION(Packet* pr, SockHandler* sk)
{
	unsigned char VersionSize = NULL;
	pr->GetPR()->Skip(8);

	pr->GetPR()->ReadByte(VersionSize);
	std::string Version = pr->GetPR()->ReadUniString((unsigned int)VersionSize);

	if (strcmp(sk->GetCFG()->getString(sk->GetCFG()->CLIENT_VERSION).c_str(), Version.c_str()))
		printf("[+] Invalid client version connected (%s != %s).\n", Version.c_str(), sk->GetCFG()->getString(sk->GetCFG()->CLIENT_VERSION).c_str());

	AK_CHECKVERSION(pr, sk);
}