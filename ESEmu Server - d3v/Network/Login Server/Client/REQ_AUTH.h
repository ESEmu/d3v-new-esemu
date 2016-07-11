/*
00 00 04 02 00 00 00 01 00 00 00 00 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF - Protocol Wrapper
02 80 - OP Code
00 00 00 26 - Unknown
00 01 - Is First Login
00 00 00 0A - Username Size
70 00 72 00 6F 00 76 00 61 - Username
00 - Pad
00 00 00 0A - Password Size
70 00 72 00 6F 00 76 00 61 - Password
00 00 00 00 00 00 00 00 00 00 01 02 02
*/
#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "../Server/AK_AUTH.h"

typedef struct _REQ_LOGIN
{
	int IsFirstLogin;
	int UsernameSize;
	char* Username;
	int PasswordSize;
	char* Password;
} _REQ_LOGIN;

void REQ_AUTH(Packet* pr, SockHandler* sk)
{
	unsigned char t_IsFirstLogin= NULL;
	unsigned int t_UserSz		= NULL;
	std::string t_Username		= "";
	unsigned int t_PswSize		= NULL;
	std::string t_Psw			= "";

	_REQ_LOGIN Packet;
	pr->GetPR()->Skip(5);
	pr->GetPR()->ReadByte(t_IsFirstLogin);
	pr->GetPR()->ReadInt(t_UserSz);
	t_Username	= pr->GetPR()->ReadUniString(t_UserSz);
	pr->GetPR()->ReadInt(t_PswSize);
	t_Psw		= pr->GetPR()->ReadUniString(t_PswSize);

	if (t_Username.size() < 4 || t_Psw.size() < 4)
	{
		printf("[!] Invalid credentials (%s)[%d][%d].\n", t_Username.c_str(), t_Username.size(), t_Psw.size());
		AK_AUTH(pr, sk, false, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_BAD_DATA);
	} else {
		
		if (t_IsFirstLogin == 0x01) {
			if (!pr->GetDB()->CheckAccount((char*)t_Username.c_str(), (char*)t_Psw.c_str()))
			{
				printf("[!] Invalid credentials (%s:%s).\n", t_Username.c_str(), t_Psw.c_str());
				AK_AUTH(pr, sk, false, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_BAD_DATA);
			}
			else 
			{
				if (pr->GetDB()->CheckAccountBan((char*)t_Username.c_str()))
					AK_AUTH(pr, sk, false, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_BANNED);
				else
				{
					printf("> Successfull login (%s).\n", (char*)sk->GetIP().c_str());
					pr->GetDB()->UpdateUser((char*)t_Username.c_str(), (char*)sk->GetIP().c_str());
					AK_AUTH(pr, sk, true, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_NONE);
				}
			}
		}
		else {
			
			if (!pr->GetDB()->CheckSerial(atoi(t_Username.c_str()) - 1000000, (char*)t_Psw.c_str()))
			{
				printf("[!] Invalid credentials (%s:%s).\n", t_Username.c_str(), t_Psw.c_str());
				//AK_AUTH(pr, sk, false, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_BAD_DATA);
				return;
			}
			else
			{
				if (pr->GetDB()->CheckAccountBan((char*)t_Username.c_str())) {
					//AK_AUTH(pr, sk, false, (char *)t_Username.c_str(), pr->GetDB()->GetAccountID((char *)t_Username.c_str()), REASON_BANNED);
					return;
				}
				else
				{
					printf("> Successfull login 2 by token (%s).\n", (char*)sk->GetIP().c_str());
					AK_AUTH(pr, sk, true, "", atoi(t_Username.c_str()) - 1000000, REASON_NONE);
				}
			}
			
		}
	}
	
}