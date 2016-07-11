#pragma once

#include "..\Common\Credits.h"

#ifdef BOOST_NETWORK

#include "..\AntiSQLi\AntiSQLi.h"
#include "..\ConfManager\ConfigReader.h"
//#include "..\Network\TransitionStructs.h"

#include <mysql.h>
#pragma comment (lib, "libmysql.lib")

#ifndef OUT
	#define OUT
#endif

typedef struct _CHANNEL_INFO
{
	short ID;
	char ChannelName[10];
	char IP[16];
	short Port;
	int MaxPlayers;
	int LevelLimit;
	int LevelLimitBonus;
} _CHANNEL_INFO;

typedef struct _SERVER_INFO
{
	short ID;
	char ServerName[15];
	char IP[16];
} _SERVER_INFO;

typedef struct _CHARACTER_INFO
{
	unsigned long long ID;
	unsigned long long OWID;
	char Name[20];
	short Level;
	unsigned long long Experience;
	unsigned long long HealthPoints;
	unsigned long long PhysicalAttack;
	unsigned long long MagicAttack;
	unsigned long long PhysicalDefense;
	unsigned long long MagicDefense;
	unsigned int ED;
	short UnitType;
	short UnitClass;
	char CreateDate[25];
	int Map;
} _CHARACTER_INFO;

typedef struct _ACCOUNT_INFO
{
	unsigned long long ID;
	char Username[31];
	char Password[51];
	char Salt[17];
	char Email[41];
	char CreateDate[25];
	char Status[21];
	char TransfermentSerial[46];
	char LastLogin[25];
	char LastIP[46];
	short CharSlots;
	char PINCode[6];
} _ACCOUNT_INFO;

typedef struct _EQUIPMENT_INFO
{
	unsigned long long ID;
	unsigned long long IID;
	unsigned long long CID;
	unsigned int Amount;
	char ExpirationDate[25];
	int Endurance;
	char IsDecorative;
	char IsEquipped;
	char IsEquipmentItem;
	int InventoryPosition;
} _EQUIPMENT_INFO;

class DATABASE
{

public:
	DATABASE(ConfigManager* CManager);
	~DATABASE();
	bool IsError();

	bool CheckAccount(char* Username, char* Password);
	bool CheckAccountBan(char* Username);
	bool UpdateUser(char* Username, char* NewIP);
	int GetAccountID(char* Username);
	int GetAccountCharSlots(char* Username);
	int GetAccountCharSlots(int CharID);
	bool UpdateLoginSerial(char* Serial, char* Username);
	bool UpdateLoginSerial(char* Serial, int acc_id);
	bool CheckSerial(int CharID, char* Password);
	bool IsPINCodeProtected(int AccID);
	string GetPINCode(int AccID);

	int GetServerList(short int MaxLoad, OUT _SERVER_INFO SList[], OUT int SAmount);
	int GetChannelList(short int MaxLoad, OUT _CHANNEL_INFO CHList[], OUT int CHAmount);

	bool GetCharacterList(int OWID, OUT _CHARACTER_INFO CList[], OUT short& CAmount);
	int GetEquipmentAmountForChar(int CID);
	int GetCharsAmount(int OWID);
	bool GetEquipmentList(int CharID, OUT _EQUIPMENT_INFO EList[], OUT short& EAmount);

	string GetCountryByIP(string IP);


private:
	MYSQL*			mysql;
	MYSQL*			db;
	bool			error;
};

#else

#ifndef OUT
	#define OUT
#endif

/*
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
	DATABASE(ConfigManager* CManager);
	~DATABASE();
	bool IsError();

	bool CheckAccount(char* Username, char* Password);
	bool UpdateUser(char* Username, char* NewIP);

	int GetChannelList(short int MaxLoad, OUT _CHANNEL_INFO CHList[], OUT int CHAmount);
};
*/

#endif