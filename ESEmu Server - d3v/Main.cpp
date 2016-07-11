#include <iostream>
#include "Common\Credits.h"
#ifndef BOOST_NETWORK
	#define WIN32_LEAN_AND_MEAN
	//#include <winsock.h>
	#include <Windows.h>
	#include <winsock.h>
	//#include <ws2tcpip.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <signal.h>
#include "ConfManager\ConfigReader.h"
#include "DBHandler\DBHandler.h"
#include "Network\SockHandler.h"
#include "Thread Manager\Thread Manager.h"
#include "Network\TransitionStructs.h"
#include "LUAEngine\LUASystem.h"
#pragma warning (disable: 4819) 
#pragma comment (lib, "ws2_32.lib")

#define SERVER_TYPE_LOGIN 1
#define SERVER_TYPE_GAME  2

WORD				wVersionRequested;
WSADATA				wsaData;
HANDLE				ThreadHandle;
CRITICAL_SECTION	gCriticalSection;
SOCKET				ListenerSock;

#ifdef _WIN32
LPDWORD RCThread = NULL;

void signalHandler(int signum)
{
	printf("Interrupt received, closing.\n");
	exit(signum);
}
#endif

int main(int argc, char* argv[])
{
	short LastID = NULL;
	ConfigManager *CM = new ConfigManager();
	LUASystem	  *LS = new LUASystem();
	ThreadManager *TM = new ThreadManager();

	printf(CREDITS_BANNER);

	if (argc != 2)
		return;

	if (!CM->load((short)(atoi(argv[1]))))
	{
		printf("[!] Unable to load LCSettings.lua!\n");
		exit(0);
	}
#ifdef BOOST_NETWORK
	printf("/!\\ - This compiled version is using BOOST Asio Network Library.\n\n");
#else
	printf("/!\\ - This compiled version is using Winsock 1.1 Network Classes.\n\n");
#endif
	printf("Planned Client Version: %s\n", CM->getString(CM->CLIENT_VERSION).c_str());
	printf("Connecting to the Database (%s:%d).\n", CM->getString(CM->DB_HOST).c_str(), CM->getNumber(CM->DB_PORT));
	
	_CHANNEL_INFO CHList[20];
	_SERVER_INFO  SList[4];

	DATABASE* DB = new DATABASE(CM);
	if (DB->IsError())
	{
		printf("[!] Can't connect to the MySQL Server!\n");
		exit(0);
	}

	printf("\n[------------- SERVERS --------------]\n\n");

	if (CM->getNumber(CM->SERVER_LOGINS) > 3)
	{
		printf("[!] Maximum Servers exceeded (3).\n");
		exit(0);
	}

	printf("Getting information of %d Servers.\n", CM->getNumber(CM->SERVER_LOGINS));
	if (!DB->GetServerList(CM->getNumber(CM->SERVER_LOGINS), SList, CM->getNumber(CM->SERVER_LOGINS)))
	{
		printf("[!] Unable to get Servers list.\n");
		exit(0);
	}

	for (short i = 0; i < CM->getNumber(CM->SERVER_LOGINS); i++)
	{
		if (LastID == SList[i].ID)
			break;
		LastID = SList[i].ID;
		printf("[%d] %s (%s:9400)\n", SList[i].ID, SList[i].ServerName, SList[i].IP);
	}
	LastID = NULL;

	printf("\n[------------- CHANNELS -------------]\n\n");

	if (CM->getNumber(CM->SERVER_CHANNELS) > 18)
	{
		printf("[!] Maximum Channels exceeded (18).\n");
		exit(0);
	}

	printf("Getting information of %d Channels.\n", CM->getNumber(CM->SERVER_CHANNELS));
	if (!DB->GetChannelList(CM->getNumber(CM->SERVER_CHANNELS), CHList, CM->getNumber(CM->SERVER_CHANNELS)))
	{
		printf("[!] Unable to get Channels list.\n");
		exit(0);
	}

	for (short i = 0; i < CM->getNumber(CM->SERVER_CHANNELS); i++)
	{
		if (LastID == CHList[i].ID)
			break;
		LastID = CHList[i].ID;
		printf("[%d] %s (%s:%d) (Max. Players %d)\n", CHList[i].ID, CHList[i].ChannelName, CHList[i].IP, CHList[i].Port, CHList[i].MaxPlayers);
	}
	printf("\n[------------------------------------]\n\n");
	
#ifdef _WIN32
	signal(SIGINT, signalHandler);
	if ((short)(atoi(argv[1])) == 1)
		SetConsoleTitle("ESEmu Project - Login Core [ FIRE ]");
	else
		SetConsoleTitle("ESEmu Project - Game Core [ FIRE ]");
	// TODO: Create Inner Thread Server Communication
#endif

	if (!LS->Init())
	{
		printf("[!] LUA System unable to initialize.\n");
		exit(1);
	}
	LS->LoadClassPath(CLASSPATH_COMMANDS);
	LS->LoadClassPath(CLASSPATH_EVENTS);

	if (CM->getNumber(CM->SERVER_TYPE) == SERVER_TYPE_LOGIN)
	{
		printf("Starting %s Login Core on %s:%d.\n\n", CM->getString(CM->SERVER_NAME).c_str(), CM->getString(CM->SERVER_IP).c_str(), CM->getNumber(CM->SERVER_PORT));
		InitializeCriticalSection(&gCriticalSection);

		if (!TM->Initialize(CM->getNumber(CM->WORKER_THREADS), CM))
		{
			printf("[!] Unable to initialize Thread Manager.\n");
			exit(0);
		}
		
		for (auto i = 1; i < CM->getNumber(CM->WORKER_THREADS) + 1; i++)
		{
			if (!TM->Spawn(i, SERVER_TYPE_LOGIN))
				printf("[!] -> Worker %d didn't spawn, skipping.\n", i);
		}
		
		LeaveCriticalSection(&gCriticalSection);

	} else if (CM->getNumber(CM->SERVER_TYPE) == SERVER_TYPE_GAME) {
		printf("Loading providers...\n");
		LUAProviders::Init();

		printf("Starting %s Game Core on %s:%d.\n\n", CM->getString(CM->SERVER_NAME).c_str(), CM->getString(CM->SERVER_IP).c_str(), CM->getNumber(CM->SERVER_PORT));
		InitializeCriticalSection(&gCriticalSection);

		if (!TM->Initialize(CM->getNumber(CM->WORKER_THREADS), CM))
		{
			printf("[!] Unable to initialize Thread Manager.\n");
			exit(0);
		}

		for (auto i = 1; i < CM->getNumber(CM->WORKER_THREADS) + 1; i++)
		{
			if (!TM->Spawn(i, SERVER_TYPE_GAME))
				printf("[!] -> Worker %d didn't spawn, skipping.\n", i);
		}

		LeaveCriticalSection(&gCriticalSection);

	} else {
		printf("Uknown Core Type (%d) for %s (IP: %s), quitting.\n", CM->getNumber(CM->SERVER_TYPE), CM->getString(CM->SERVER_NAME).c_str(), CM->getString(CM->SERVER_IP).c_str());
	}
	_getch();
}