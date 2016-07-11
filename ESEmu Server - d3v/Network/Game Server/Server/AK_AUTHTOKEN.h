#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\..\..\Common\Time.h"

void AK_AUTHTOKEN(Packet* pr, SockHandler* sk, std::string Token1)
{
	std::string EventADURI = "http://ad.nexon.com/NetInsight/html/nexon/elsword.nexon.com/ending@middle";
	std::string UnknownIP = "121.6.197.184";

	pr->GetPB()->Init(700);
	pr->GetPB()->WriteHeader(0x00, 0x1F);

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<int>(sk->getAccID());

	std::string serial = Random::numeric(10);
	std::string serial2 = std::to_string(sk->getAccID() + 1000000);
	
	pr->GetDB()->UpdateLoginSerial((char *)serial.c_str(), sk->getAccID());

	pr->GetPB()->WriteUniString((char*)serial2.c_str(), serial.length());
	pr->GetPB()->WriteUniString((char*)serial2.c_str(), serial2.length());

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<short>(1);

	pr->GetPB()->WriteUniString((char*)Time::now().c_str(), Time::andnow().length());

	pr->GetPB()->WriteUniString("Reason", 6);

	pr->GetPB()->Append<short>(0x0100);

	pr->GetPB()->WriteUniString((char *)serial.c_str(), serial.length());

	pr->GetPB()->WriteUniString((char*)Time::now().c_str(), Time::andnow().length()); // Starting event date
	pr->GetPB()->WriteUniString((char*)Time::now().c_str(), Time::andnow().length()); // Ending event date

	pr->GetPB()->Append<unsigned char>(0);
	pr->GetPB()->WriteUniString((char*)EventADURI.c_str(), EventADURI.length());

	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<short>(0);
	pr->GetPB()->Append<short>(0x3B4E);
	pr->GetPB()->Append<unsigned char>(0xF7);

	pr->GetPB()->WriteUniString((char*)UnknownIP.c_str(), UnknownIP.length());
	pr->GetPB()->Append<int>(0);
	pr->GetPB()->Append<unsigned char>(0);

	pr->GetPB()->WriteEnd();
	sk->Send((unsigned char*)pr->GetPB()->GetBuffer(), pr->GetPB()->GetSize());
}