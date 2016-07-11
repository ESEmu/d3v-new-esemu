#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CHARCREATE.h"

void REQ_CHARCREATE(Packet* pr, SockHandler* sk)
{
	unsigned int NameSize = NULL;
	unsigned int Something = NULL;
	pr->GetPR()->Skip(5);
	pr->GetPR()->ReadInt(NameSize);
	std::string Name = pr->GetPR()->ReadUniString(NameSize);
	pr->GetPR()->ReadInt(Something);

	AK_CHARCREATE(pr, sk);
}