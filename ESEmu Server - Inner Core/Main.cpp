#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>
#include <conio.h>
#include "ConfManager\ConfigReader.h"
#include "DBHandler\DBHandler.h"
#include "Network\TransitionStructs.h"
#include "Common\Common.h"
#pragma warning (disable: 4819)
#pragma comment (lib, "ws2_32.lib")
using namespace std;

WORD				wVersionRequested;
WSADATA				wsaData;
HANDLE				ThreadHandle;
CRITICAL_SECTION	gCriticalSection;
_CHANNEL_DETAILS	ChannelsInfo[12];
SOCKET				ListenerSock;

#ifdef _WIN32
LPDWORD RCThread = NULL;

void signalHandler(int signum)
{
	printf("Interrupt received, closing.\n");
	exit(signum);
}
#endif

#define INNER_BASE_CHECKERS		0x00
#define INNER_TYPE_PING			(INNER_BASE_CHECKERS + 0x01)
#define INNER_TYPE_PONG			(INNER_BASE_CHECKERS + INNER_TYPE_PING + 0x01)
#define INNER_TYPE_DISCONNECT	(INNER_BASE_CHECKERS + 0x09)

#define INNER_BASE_ERRORS		0x10
#define INNER_TYPE_NOT_AUTH		(INNER_BASE_ERRORS + 0x01)
#define INNER_TYPE_NO_CH		(INNER_BASE_ERRORS + 0x02)

#define PCK_BODY packet_buf[1]
#define PCK_ARG	 packet_buf[2]

#define MAX_BUFF 1024 * 3

bool Send(int Type, int id, SOCKET s, short CHID)
{
	char packet_buf[3];

	packet_buf[0] = id;
	switch (Type)
	{
	case INNER_TYPE_PING:
		PCK_BODY = INNER_TYPE_PING;
		break;
	case INNER_TYPE_PONG:
		PCK_BODY = INNER_TYPE_PONG;
		break;
	case INNER_TYPE_DISCONNECT:
		PCK_BODY = INNER_TYPE_DISCONNECT;
		break;
	case INNER_TYPE_NOT_AUTH:
		PCK_BODY = INNER_TYPE_NOT_AUTH;
		PCK_ARG  = CHID;
		break;
	case INNER_TYPE_NO_CH:
		PCK_BODY = INNER_TYPE_NO_CH;
		PCK_ARG  = CHID;
		break;
	default:
		break;
	}
	
	if (send(s, packet_buf, 2, NULL) == SOCKET_ERROR)
	{
		printf("[!] Error sending packet (%d): %d.", Type, WSAGetLastError());
		closesocket(s);
		return false;
	}
	return true;
}

DWORD WINAPI WinSockThread(LPVOID Param)
{
	int serve = 0;
	int retVal;
	bool connected = true;
	int packet_len;
	char packet_buf[MAX_BUFF];
	//THREAD_SEND* stc = (THREAD_SEND*)Param;
	//stc->id = -1;
	bool send_info = false;
	int step = 0;
	/*
	while (connected)
	{
		if ((packet_len = recv(stc->socket, packet_buf, PACKET_LEN, 0)) != SOCKET_ERROR)// 0)
		{
			switch (packet_buf[0])
			{
			case 1:
			{
				serve = 1;
				////////////////////////////////////////////////////////////////////////
				/// From login server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] LoginServer connection.\n", inet_ntoa(stc->from));
					if (!SendOK(stc->id, stc->socket))
						return 0;
					break;
				case 0x21:
					packet_buf[0] = 0x22;
					step = 0;
					for (int i = 0; i < 12; i++)
					{
						//						if (stc->gs_info[i].id != -1)
						//					{
						gs_info[i].cs_ip = cs_info[i].ip;
						gs_info[i].cs_port = cs_info[i].port;
						++step;
						//						}
					}

					packet_buf[1] = 12;// (uint8)step;
					step = 2;
					for (int i = 0; i < 12; i++)
					{
						//						if (stc->gs_info[i].id != -1)
						//					{
						memcpy(packet_buf + step, &gs_info[i], sizeof(GAMESERVER_INFO));
						step += sizeof(GAMESERVER_INFO);
						//						}
					}
					retVal = send(stc->socket, packet_buf, step, NULL);
					if (retVal == SOCKET_ERROR) {
						log::Error(fg, "InnerThread: Disconnect.\n", WSAGetLastError());
						closesocket(s);
						return 0;
					}
					else
					{
						log::Info(fg, "InnerThread: Login Server update information.\n");
					}
					break;
				}
				break;
			}
			case 2:
			{
				serve = 2;
				////////////////////////////////////////////////////////////////////////
				/// From character server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] Character Server (%d) connection.\n", inet_ntoa(stc->from), packet_buf[2]);
					stc->id = packet_buf[2];
					if (!SendOK(stc->id, stc->socket))
						return 0;
					break;

				case 0x13:
					if (!send_info)
						log::Info(fg, "InnerThread: [%s] Character Server (%d) send info.\n", inet_ntoa(stc->from), stc->id);
					stc->cs_info[stc->id].id = stc->id;
					memcpy(&stc->cs_info[stc->id], packet_buf + 2, sizeof(CHARACTERSERVER_INFO));
					if (!SendOK(stc->id, stc->socket))
						return 0;
					send_info = true;
					break;
				default:
					if (stc->id != -1)
						log::Info(fg, "InnerThread: [%s] Character Server (%d) Unknown package.\n", inet_ntoa(stc->from), stc->id);
					else
						log::Info(fg, "InnerThread: [%s] Character Server Unknown package.\n", inet_ntoa(stc->from));
					break;
				}
				break;
			}
			case 3:
			{
				serve = 3;
				////////////////////////////////////////////////////////////////////////
				/// From game server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] Game Server (%d) connection.\n", inet_ntoa(stc->from), packet_buf[2]);
					stc->id = packet_buf[2];
					if (!SendOK(stc->id, stc->socket))
						return 0;
					break;

				case 0x13:
					//					if (!send_info)
					log::Info(fg, "InnerThread: [%s] Game Server (%d) send info.\n", inet_ntoa(stc->from), stc->id);
					stc->gs_info[stc->id].id = stc->id;
					memcpy(&stc->gs_info[stc->id], packet_buf + 3, sizeof(GAMESERVER_INFO));
					if (!SendOK(stc->id, stc->socket))
						return 0;
					send_info = true;
					break;

				default:
					if (stc->id != -1)
						log::Info(fg, "InnerThread: [%s] Game Server (%d) Unknown package.\n", inet_ntoa(stc->from), stc->id);
					else
						log::Info(fg, "InnerThread: [%s] Game Server Unknown package.\n", inet_ntoa(stc->from));
					break;

				}
				break;
			}
			default:
				log::Warn(fg, "InnerThread: [%s] Unknown connection.\n", inet_ntoa(stc->from));
				connected = false;
			}
		}
		else
		{
			int nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && nError != 0)
			{
				switch (serve)
				{
				case 1:
					log::Error(fg, "InnerThread: [%s] Login Server disconnect.\n", inet_ntoa(stc->from));
					break;
				case 2:
					log::Error(fg, "InnerThread: [%s] Character Server disconnect.\n", inet_ntoa(stc->from));
					break;
				case 3:
					log::Error(fg, "InnerThread: [%s] Game Server disconnect.\n", inet_ntoa(stc->from));
					stc->gs_info[stc->id].id = -1;
					break;
				}
				closesocket(stc->socket);
				return 0;
			}
		}

		Sleep(100);
	}

	if (stc->socket != NULL)
		closesocket(stc->socket);

	log::Info(fg, "InnerThread: [%s] Disconnect.\n", inet_ntoa(stc->from));

	delete(stc);
	return 0;
	*/
	return 0;
}

int main(int argc, char* argv[])
{
	int err;
	u_long iMode = 1;
	const char on = 1;
	sockaddr_in	from;
	SOCKET s;
	SOCKET sock_accept;
	struct sockaddr_in sin;
	ListenerSock = NULL;
	short LastID = NULL;
	ConfigManager *CM = new ConfigManager();

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	printf(CREDITS_BANNER);
	if (!CM->load())
	{
		printf("[!] Unable to load ICSettings.lua!\n");
		exit(0);
	}
	printf("Connecting to the Database (%s:%d).\n", CM->getString(CM->DB_HOST).c_str(), CM->getNumber(CM->DB_PORT));

	_CHANNEL_INFO CHList[20];

	DATABASE* DB = new DATABASE(CM);
	if (DB->IsError())
	{
		printf("[!] Can't connect to the MySQL Server!\n");
		exit(0);
	}

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
	//signal(SIGINT, signalHandler);
	SetConsoleTitle("ESEmu Project - Inner Core [ ARCHER ]");
	// TODO: Create Inner Thread Server Communication
#endif
	printf("Starting %s Inner Core on %s:%d.\n", CM->getString(CM->SERVER_NAME).c_str(), CM->getString(CM->SERVER_IP).c_str(), CM->getNumber(CM->SERVER_PORT));
	InitializeCriticalSection(&gCriticalSection);

	s = socket(AF_INET, SOCK_STREAM, NULL);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(CM->getNumber(CM->SERVER_PORT));
	sin.sin_addr.s_addr = inet_addr(CM->getString(CM->SERVER_IP).c_str());

	bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);

	int fromlen;

	while (true)
	{

		fromlen = sizeof(from);
		sock_accept = accept(s, (struct sockaddr*)&from, &fromlen);
		if (sock_accept != INVALID_SOCKET)
		{
			THREAD_STRUCT* th_struct = new THREAD_STRUCT;
			th_struct->Socket = sock_accept;
			//th_struct->fg = fg;
			th_struct->MySQLHandler = DB;
			th_struct->ChannelsInfo = ChannelsInfo;
			th_struct->ThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockThread, th_struct, NULL, &th_struct->SocketRead);
		}

		Sleep(100);
	}
	WSACleanup();
	_getch();
}