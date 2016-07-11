#pragma once
#ifndef _ANTIDDOS_H_
#define _ANTIDDOS_H_

#include <iostream>
#include <list>
using namespace std;

class AntiDDOS
{
public:

	struct _SESSION_INFO
	{
		char* IP;
		unsigned long long PacketsSent;			// Unused for now.
		unsigned long long PacketsRecved;		// Unused for now.
		unsigned long long ConnectionAttempts;	// Counts the number of connections achieved since the last ESEmu reboot.
		char IsPermanent;
		bool IsActive;
	};

private:

	list<_SESSION_INFO*>::iterator	i_BIP;
	list<_SESSION_INFO*>::iterator	i_AS;
	list<_SESSION_INFO*>			m_BannedIPs;
	list<_SESSION_INFO*>			m_ActiveSessios;

public:

#ifndef _WIN32
	bool CheckPrivileges();
#endif

	void Init();
	void AddBanByIP(const char* IP);
	bool CheckBan(const char* IP);
	//void Worker_ClearSessions();
	void SetActive(const char* IP);
	void SetInactive(const char* IP);
	void WorkProxy();

};

#endif