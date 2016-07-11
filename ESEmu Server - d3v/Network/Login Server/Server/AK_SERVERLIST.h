#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#pragma warning( disable: 4996)

void AK_SERVERLIST(Packet* pr, SockHandler* sk)
{
	_SERVER_INFO SList[4];
	if (!pr->GetDB()->GetServerList(sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS), SList, sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS)))
	{
		printf("[!] No servers?!\n");
		return;
	}
	pr->GetPB()->Init(150 * sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS));
	pr->GetPB()->WriteHeader(0x5, 0x2C);

	std::cout << sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS) << "@@@@" << std::endl;
	pr->GetPB()->Append<int>(sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS));
	for (auto i = 0; i < sk->GetCFG()->getNumber(sk->GetCFG()->SERVER_LOGINS); i++)
	{
		pr->GetPB()->Append<int>(i);
		pr->GetPB()->Append<int>(i + 1);
		pr->GetPB()->Append<int>(i);
		std::cout << SList[i].ServerName << std::endl;
		pr->GetPB()->WriteUniString(SList[i].ServerName, strlen(SList[i].ServerName));
		std::cout << SList[i].IP << std::endl;
		pr->GetPB()->WriteUniString(SList[i].IP, strlen(SList[i].IP));

		pr->GetPB()->WriteBuffer("\x24\xB8\x24\xB9", 4);
		if (SList[i].ID != 1)
			pr->GetPB()->Append<unsigned char>(0);
		else
			pr->GetPB()->Append<unsigned char>(1);
	}

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}