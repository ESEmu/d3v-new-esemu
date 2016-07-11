#pragma once
#ifndef _TRANSTRUCTS_H_
#define _TRANSTRUCTS_H_

#include "..\DBHandler\DBHandler.h"

enum CHANNEL_LOAD
{
	LOAD_FREE,
	LOAD_NORMAL,
	LOAD_BUSY,
	LOAD_FULL
};

#pragma pack(1)
struct _CHANNEL_DETAILS
{
	char		 ID;
	char		 Name[42];
	unsigned int ConnectedPlayers;
	unsigned int MaxPlayers;
	time_t		 LastUpdate;
	int			 cs_ip;
	int			 cs_port;
	bool		 Status;
};
#pragma pack()

typedef struct THREAD_STRUCT
{
	HANDLE				ThreadHandle;
	SOCKET				Socket;
	DWORD				SocketRead;
	//DATABASE*			MySQLHandler;
	int					AccountID;
	char				AccountName[32];
	bool				SendChannelList;
	_CHANNEL_DETAILS*	ChannelsInfo;

} THREAD_STRUCT;

#endif