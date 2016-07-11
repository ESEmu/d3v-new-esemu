#include "AntiDDoS.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma warning (disable: 4996)

#include <boost\thread.hpp>

#ifdef _WIN32
	#define COMMAND_EMPTY "netsh advfirewall firewall add rule name=\"IP Block\" dir=in interface=any action=block remoteip=/32"
	#define COMMAND_EDITABLE "netsh advfirewall firewall add rule name=\"IP Block\" dir=in interface=any action=block remoteip=%s/32"
#else
	#define COMMAND_EMPTY "iptables -A INPUT -s  -j DROP"
	#define COMMAND_EDITABLE "iptables -A INPUT -s %s -j DROP"
#endif

#define MAX_CONNECTION_TRIALS	10
#define CHECKER_TIMEOUT			5	

void Worker_ClearSessions(AntiDDOS* Instance)
{
	while (true)
	{
		Instance->WorkProxy();
		Sleep((DWORD)CHECKER_TIMEOUT * 1000);
	}
}

void AntiDDOS::WorkProxy()
{
	for (list<_SESSION_INFO*>::iterator SessionChecker = this->m_ActiveSessios.begin(); SessionChecker != this->m_ActiveSessios.end(); SessionChecker++)
	{
		if ((*SessionChecker)->ConnectionAttempts > MAX_CONNECTION_TRIALS)
		{
			this->AddBanByIP((*SessionChecker)->IP);
			this->m_ActiveSessios.erase(SessionChecker);
		}
		if ((*SessionChecker)->IsActive = false)
			this->m_ActiveSessios.erase(SessionChecker);
	}
}

void AntiDDOS::SetActive(const char* IP)
{
	for (list<_SESSION_INFO*>::iterator ActivitySetter = this->m_ActiveSessios.begin(); ActivitySetter != this->m_ActiveSessios.end(); ActivitySetter++)
	{
		if (!strcmp((*ActivitySetter)->IP, IP))
		{
			(*ActivitySetter)->IsActive = true;
			break;
		}
	}
}

void AntiDDOS::SetInactive(const char* IP)
{
	for (list<_SESSION_INFO*>::iterator ActivitySetter = this->m_ActiveSessios.begin(); ActivitySetter != this->m_ActiveSessios.end(); ActivitySetter++)
	{
		if (!strcmp((*ActivitySetter)->IP, IP))
		{
			(*ActivitySetter)->IsActive = false;
			break;
		}
	}
}

void AntiDDOS::Init()
{
	this->i_BIP = this->m_BannedIPs.begin();
	this->i_AS	= this->m_ActiveSessios.begin();

	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)AntiDDOS::Worker_ClearSessions, NULL, NULL, NULL);
	boost::thread Worker(Worker_ClearSessions, this);
	Worker.join();
}

#ifndef _WIN32
bool AntiDDOS::CheckPrivileges()
{
	if (geteuid() != 0)
	{
		return false;
	}
}
#endif

void AntiDDOS::AddBanByIP(const char* IP)
{
	if (strlen(IP) > 40)
		return;
	char *Command = (char*)malloc(strlen(COMMAND_EMPTY) + strlen(IP));
	memset(Command, 0x00, strlen(COMMAND_EMPTY) + strlen(IP));

	printf("[+] ADDoS: %s is being banned for DDoS.\n", IP);

	sprintf(Command, COMMAND_EDITABLE, IP);

	::system(Command);
}

bool AntiDDOS::CheckBan(const char* IP)
{
	if (strlen(IP) > 40)
		return true;

	this->i_BIP = this->m_BannedIPs.begin();
	while (this->i_BIP != this->m_BannedIPs.end())
	{
		if (!strcmp((*this->i_BIP)->IP, IP))
			return true;
	}
	// Not existing ban, new session then.
	_SESSION_INFO* NewSession = new (_SESSION_INFO);
	NewSession->IP = (char*)malloc(strlen(IP));
	memset(NewSession, 0x00, strlen(IP));

	this->i_AS = this->m_ActiveSessios.begin();
	while (this->i_AS != this->m_ActiveSessios.end())
	{
		if (!strcmp((*this->i_AS)->IP, IP))
		{
			(*this->i_AS)->ConnectionAttempts++;
		} else {
			NewSession->IP = (char*)IP;
			NewSession->PacketsRecved = NULL;
			NewSession->PacketsSent = NULL;
			NewSession->ConnectionAttempts = 1;
			NewSession->IsPermanent = 0;
			this->m_BannedIPs.push_back(NewSession);
		}
	}

	return false;
}