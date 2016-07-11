#pragma once

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "..\AntiSQLi\AntiSQLi.h"
#pragma comment(lib, "mysqlcppconn.lib")
#pragma comment(lib, "mysqlcppconn-static.lib")
#include "..\ConfManager\ConfigReader.h"
//#include "..\Network\TransitionStructs.h"

#include <winsock.h>
#include "../MySQL/mysql.h"
#include <mysql_connection.h>
#pragma comment (lib, "libmysql.lib")

typedef struct _CHANNEL_INFO
{
	short ID;
	char ChannelName[10];
	char IP[16];
	short Port;
	int MaxPlayers;
} _CHANNEL_INFO;

class DATABASE
{

public:
	DATABASE(ConfigManager* CManager);
	~DATABASE();
	bool IsError();

	int GetChannelList(short int MaxLoad, OUT _CHANNEL_INFO CHList[], OUT int CHAmount);


private:
	MYSQL*			mysql;
	MYSQL*			db;
	bool			error;
};