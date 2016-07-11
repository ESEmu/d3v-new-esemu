#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_AUTHTOKEN.h"

void REQ_AUTHTOKEN(Packet* pr, SockHandler* sk)
{
	unsigned int TokenSize = NULL;
	std::string Token = "";
	unsigned int Token2Size = NULL;
	std::string Token2 = "";
	unsigned int Token3Size = NULL;
	std::string Token3 = "";

	pr->GetPR()->Skip(6);

	pr->GetPR()->ReadInt(TokenSize);
	Token = pr->GetPR()->ReadUniString(TokenSize);
	std::cout << "Token: " << Token << std::endl;
	int AccID = atoi((char *)Token.c_str()) - 1000000;
	std::cout << "AccID: " << AccID << std::endl;
	sk->setAccID(AccID);

	pr->GetPR()->ReadInt(Token2Size);
	Token2 = pr->GetPR()->ReadUniString(Token2Size);

	if (!pr->GetDB()->CheckSerial(AccID, (char *)Token2.c_str())) {
		// Illegal connection. Disconnect or something?
		sk->getSocket().close();
		return;
	}

	pr->GetPR()->Skip(4);

	//pr->GetPR()->ReadInt(Token3Size);
	//Token3 = pr->GetPR()->ReadUniString(Token3Size);

	AK_AUTHTOKEN(pr, sk, Token);
}