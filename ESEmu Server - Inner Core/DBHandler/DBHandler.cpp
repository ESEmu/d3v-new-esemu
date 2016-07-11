#pragma warning(disable : 4251)
#include "DBHandler.h"
#include "..\ConfManager\ConfigReader.h"
//#include "../Common/Time.h"
#include <conio.h>
#pragma warning (disable: 4996)

DATABASE::DATABASE(ConfigManager* CManager)
{
	error = false;
	this->mysql = mysql_init(NULL);
	this->db = mysql_real_connect(this->mysql,
		CManager->getString(CManager->DB_HOST).c_str(),
		CManager->getString(CManager->DB_USER).c_str(),
		CManager->getString(CManager->DB_PASSWORD).c_str(),
		CManager->getString(CManager->DB_DATABASE).c_str(),
		CManager->getNumber(CManager->DB_PORT),
		NULL, 0);
	if (this->db != NULL)
	{
		error = false;
	} else {
		error = true;
		printf("[!] Can't connect to the MySQL Server!\n");
		_getch();
		return;
	}
	mysql_autocommit(this->db, 1);
}

DATABASE::~DATABASE()
{
	mysql_close(this->mysql);
}

bool DATABASE::IsError()
{
	return error;
}

int DATABASE::GetChannelList(short int MaxLoad, OUT _CHANNEL_INFO CHList[], OUT int CHAmount)
{
	#define ROW_CH_ID	0
	#define ROW_CH_NAME	1
	#define ROW_CH_IP	2
	#define ROW_CH_PORT	3
	#define ROW_CH_MAXP	4

	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];
	/*
	sprintf(Query, "SELECT COUNT(*) FROM Channels;");

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to count number of channels in database (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the Count result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);

	if (atoi(Row[0]) != CHAmount)
	{
		printf("[+] Channels number mismatch between database and configuration, adjusting.\n");
		CHAmount = atoi(Row[0]);
		if (atoi(Row[0]) > 18)
		{
			printf("[+] Maximum Channels exceeded., adjusting.\n");
			CHAmount = 18;
		}
	}
	*/

	sprintf(Query, "SELECT * FROM Channels;");
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the channels list (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the List result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);

	for (int Index = 0; Index <= MaxLoad; Index++)
	{
		CHList[Index].ID = atoi(Row[ROW_CH_ID]);
		strcpy(CHList[Index].ChannelName, Row[ROW_CH_NAME]);
		strcpy(CHList[Index].IP, Row[ROW_CH_IP]);
		CHList[Index].Port = atoi(Row[ROW_CH_PORT]);
		CHList[Index].MaxPlayers = atoi(Row[ROW_CH_MAXP]);
	}

	return 1;
}