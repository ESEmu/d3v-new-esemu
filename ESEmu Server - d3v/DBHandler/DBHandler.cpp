#pragma warning(disable : 4251)
#include "DBHandler.h"
#include "../ConfManager/ConfigReader.h"
#include "../Common/Time.h"
#include <conio.h>
#pragma warning (disable: 4996)

#ifdef BOOST_NETWORK

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

bool DATABASE::CheckAccountBan(char* Username)
{
	MYSQL_RES* Result;
	MYSQL_ROW  Row;
	char Query[256] = { 0 };

	string User_String(Username);
	printf("Filtered value is %s <-------------------\n", ASQLi::FilterQuery(User_String).c_str());

	sprintf(Query, "SELECT Status FROM Accounts WHERE Username = '%s';", ASQLi::FilterQuery(User_String).c_str());
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}

	Result = mysql_store_result(db);

	if ((Row = mysql_fetch_row(Result)))
	{
		if (!strcmp(Row[0], "STATUS_BANNED"))
			return true;
		else
			return false;
	}
	return false;
}

bool DATABASE::CheckAccount(char* Username, char* Password)
{
	MYSQL_RES* Result;
	MYSQL_ROW  Row;
	char Query[256] = { 0 };

	string User_String(Username);
	string Pass_String(Password);

	sprintf(Query, "SELECT ID FROM Accounts WHERE Username = '%s' AND Password = '%s';", ASQLi::FilterQuery(User_String).c_str(), ASQLi::FilterQuery(Pass_String).c_str());
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}

	Result = mysql_store_result(db);

	if ((Row = mysql_fetch_row(Result)))
	{
		if (Row[0])
			return true;
		else
			return false;
	}
	return false;
}

bool DATABASE::UpdateUser(char* Username, char* NewIP)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	string IP_String(NewIP);
	string User_String(Username);

	sprintf(Query, "UPDATE Accounts SET IP = '%s', LastLogin = NOW() WHERE Username = '%s';", ASQLi::FilterQuery(IP_String).c_str(), ASQLi::FilterQuery(User_String).c_str());
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}
	return true;
}

int DATABASE::GetAccountID(char* Username)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	string User_String(Username);

	sprintf(Query, "SELECT ID FROM Accounts WHERE Username = '%s';", ASQLi::FilterQuery(User_String).c_str());
	
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the ID for the specified user (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the List result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	MYSQL_ROW Row;
	Row = mysql_fetch_row(Result);
	
	if (IsBadReadPtr(Row, sizeof(MYSQL_ROW)) || Row[0] == NULL )
		return NULL;
	else
		return atoi(Row[0]);
}

bool DATABASE::UpdateLoginSerial(char* Serial, char* Username) 
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	string Serial_String(Serial);
	string User_String(Username);

	sprintf(Query, "UPDATE Accounts SET MovingSerial = '%s' WHERE Username = '%s';", ASQLi::FilterQuery(Serial_String).c_str(), ASQLi::FilterQuery(User_String).c_str());
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}
	return true;
}

bool DATABASE::UpdateLoginSerial(char* Serial, int acc_id)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	sprintf(Query, "UPDATE Accounts SET MovingSerial = '%s' WHERE ID = %d;", Serial, acc_id);
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}
	return true;
}


bool DATABASE::CheckSerial(int CharID, char* Password)
{
	MYSQL_RES* Result;
	MYSQL_ROW  Row;
	char Query[256] = { 0 };

	sprintf(Query, "SELECT COUNT(*) FROM Accounts WHERE ID = '%d' AND MovingSerial = '%s';", CharID, Password);
	if (mysql_query(db, Query))
	{
		printf("[!] MySQL Error: %s.\n", mysql_error(db));
		return false;
	}

	Result = mysql_store_result(db);

	if ((Row = mysql_fetch_row(Result)))
	{
		printf("Account ID: %d.\n", atoi(Row[0]));
		if (Row[0])
			return true;
		else
			return false;
	}
	return false;
}

int DATABASE::GetServerList(short int MaxLoad, OUT _SERVER_INFO SList[], OUT int SAmount)
{
	#define ROW_CH_ID				0
	#define ROW_CH_NAME				1
	#define ROW_CH_IP				2

	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

	sprintf(Query, "SELECT * FROM Servers;");
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the servers list (%d).\n", mysql_errno(this->db));
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
		SList[Index].ID = atoi(Row[ROW_CH_ID]);
		strcpy(SList[Index].ServerName, Row[ROW_CH_NAME]);
		strcpy(SList[Index].IP, Row[ROW_CH_IP]);
	}

	return 1;

	#undef ROW_CH_ID				
	#undef ROW_CH_NAME				
	#undef ROW_CH_IP				
}

int DATABASE::GetChannelList(short int MaxLoad, OUT _CHANNEL_INFO CHList[], OUT int CHAmount)
{
	#define ROW_CH_ID				0
	#define ROW_CH_NAME				1
	#define ROW_CH_IP				2
	#define ROW_CH_PORT				3
	#define ROW_CH_MAXP				4
	#define ROW_CH_LEVELIMIT		5
	#define ROW_CH_LEVELIMITBONUS	6

	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

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
		CHList[Index].LevelLimit = atoi(Row[ROW_CH_LEVELIMIT]);
		CHList[Index].LevelLimitBonus = atoi(Row[ROW_CH_LEVELIMITBONUS]);
	}

	return 1;
}

bool DATABASE::GetCharacterList(int OWID, OUT _CHARACTER_INFO CList[], OUT short& CAmount)
{
	#define ROW_C_ID				0
	#define ROW_C_OWID				1
	#define ROW_C_NAME				2
	#define ROW_C_LEVEL				3
	#define ROW_C_HP				4
	#define ROW_C_EXP				5
	#define ROW_C_PHYATK			6
	#define ROW_C_MAGATK			7
	#define ROW_C_PHYDEF			8
	#define ROW_C_MAGDEF			9
	#define ROW_C_ED				10
	#define ROW_C_UTYPE				11
	#define ROW_C_UCLASS			12
	#define ROW_C_DATEC				13
	#define ROW_C_MAP				14

	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

	std::cout << "OK GETTING CHAR CNT" << std::endl;
	sprintf(Query, "SELECT COUNT(*) FROM Characters WHERE OWID = '%d';", OWID);
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the count of characters list for %d (%d).\n", OWID, mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the count of characters for %d (%d).\n", OWID, mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);
	std::cout << "OK CHAR COUNT GET" << std::endl;
	CAmount = (short)atoi(Row[0]);

	if (atoi(Row[0]) != NULL)
	{
		sprintf(Query, "SELECT * FROM Characters WHERE OWID = '%d';", OWID);
		if (mysql_query(this->db, Query))
		{
			printf("[!] Unable to get the characters list for %d (%d).\n", OWID, mysql_errno(this->db));
			return 0;
		}

		Result = mysql_store_result(this->db);
		if (!Result)
		{
			printf("[!] Unable to store characters list for %d (%d).\n", OWID, mysql_errno(this->db));
			return 0;
		}

		Row = mysql_fetch_row(Result);

		for (int Index = 0; Index <= CAmount; Index++)
		{
			CList[Index].ID = (unsigned long long)atoi(Row[ROW_C_ID]);
			CList[Index].OWID = (unsigned long long)atoi(Row[ROW_C_OWID]);
			strcpy(CList[Index].Name, Row[ROW_C_NAME]);
			CList[Index].Level = (short)atoi(Row[ROW_C_LEVEL]);
			CList[Index].HealthPoints = (unsigned long long)atoi(Row[ROW_C_HP]);
			CList[Index].Experience = (unsigned long long)atoi(Row[ROW_C_EXP]);
			CList[Index].PhysicalAttack = (unsigned long long)atoi(Row[ROW_C_PHYATK]);
			CList[Index].MagicAttack = (unsigned long long)atoi(Row[ROW_C_MAGATK]);
			CList[Index].PhysicalDefense = (unsigned long long)atoi(Row[ROW_C_PHYDEF]);
			CList[Index].MagicDefense = (unsigned long long)atoi(Row[ROW_C_MAGDEF]);
			CList[Index].ED = (unsigned long long)atoi(Row[ROW_C_ED]);
			CList[Index].UnitType = (short)atoi(Row[ROW_C_UTYPE]);
			CList[Index].UnitClass = (short)atoi(Row[ROW_C_UCLASS]);
			strcpy(CList[Index].CreateDate, Row[ROW_C_DATEC]);
			CList[Index].Map = (int)atoi(Row[ROW_C_MAP]);
		}
	}

	return 1;
}

bool DATABASE::GetEquipmentList(int CharID, OUT _EQUIPMENT_INFO EList[], OUT short& EAmount)
{
	#define ROW_E_ID		0
	#define ROW_E_IID		1
	#define ROW_E_CID		2
	#define ROW_E_AMOUNT	3
	#define ROW_E_EXPIR		4
	#define ROW_E_ISEQUIP	5
	#define ROW_E_ENDUR		6
	#define ROW_E_DECOR		7
	#define ROW_E_EQUIP		8
	#define ROW_E_INVPOS	9

	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

	sprintf(Query, "SELECT COUNT(*) FROM Equipment WHERE CID = '%d';", CharID);
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the count of items list for %d (%d).\n", CharID, mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the count of items for %d (%d).\n", CharID, mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);

	EAmount = (short)atoi(Row[0]);

	if (Row[0] != NULL)
	{
		sprintf(Query, "SELECT * FROM Equipment WHERE CID = '%d';", CharID);
		if (mysql_query(this->db, Query))
		{
			printf("[!] Unable to get the items list for %d (%d).\n", CharID, mysql_errno(this->db));
			return 0;
		}

		Result = mysql_store_result(this->db);
		if (!Result)
		{
			printf("[!] Unable to store items list for %d (%d).\n", CharID, mysql_errno(this->db));
			return 0;
		}

		Row = mysql_fetch_row(Result);

		for (int Index = 0; Index <= EAmount; Index++)
		{
			EList[Index].ID = (unsigned long long)atoi(Row[ROW_E_ID]);
			EList[Index].IID = (unsigned long long)atoi(Row[ROW_E_IID]);
			EList[Index].CID = (unsigned long long)atoi(Row[ROW_E_CID]);
			EList[Index].Amount = (unsigned int)atoi(Row[ROW_E_AMOUNT]);
			strcpy(EList[Index].ExpirationDate, Row[ROW_E_EXPIR]);
			EList[Index].IsEquipmentItem = (char)Row[ROW_E_ISEQUIP];
			EList[Index].Endurance = (unsigned int)atoi(Row[ROW_E_ENDUR]);
			EList[Index].IsDecorative = (char)atoi(Row[ROW_E_DECOR]);
			EList[Index].IsEquipped = (char)atoi(Row[ROW_E_EQUIP]);
			EList[Index].InventoryPosition = (int)atoi(Row[ROW_E_INVPOS]);
		}
	}

	return 1;
}

int DATABASE::GetEquipmentAmountForChar(int CID)
{
	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

	sprintf(Query, "SELECT COUNT(*) FROM Equipment WHERE CID = '%d';", CID);
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the count of items list for %d (%d).\n", CID, mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the count of items for %d (%d).\n", CID, mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);
	return (int)atoi(Row[0]);
}

int DATABASE::GetCharsAmount(int OWID)
{
	MYSQL_RES* Result;
	MYSQL_ROW  Row = { 0 };
	char Query[256];

	sprintf(Query, "SELECT COUNT(*) FROM Characters WHERE OWID = '%d';", OWID);
	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the count of chars list for %d (%d).\n", OWID, mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the count of chars for %d (%d).\n", OWID, mysql_errno(this->db));
		return 0;
	}

	Row = mysql_fetch_row(Result);
	return (int)atoi(Row[0]);
}

int DATABASE::GetAccountCharSlots(char* Username)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	string User_String(Username);

	sprintf(Query, "SELECT Slots FROM Accounts WHERE Username = '%s';", ASQLi::FilterQuery(User_String).c_str());

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the Slots for the specified user (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	MYSQL_ROW Row = mysql_fetch_row(Result);

	if (IsBadReadPtr(Row, sizeof(MYSQL_ROW)) || Row[0] == NULL)
		return NULL;
	else
		return atoi(Row[0]);
}

int DATABASE::GetAccountCharSlots(int CharID)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	sprintf(Query, "SELECT Slots FROM Accounts WHERE ID = '%d';", CharID);

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the Slots for the specified user (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	MYSQL_ROW Row = mysql_fetch_row(Result);

	if (IsBadReadPtr(Row, sizeof(MYSQL_ROW)) || Row[0] == NULL)
		return NULL;
	else
		return atoi(Row[0]);
}

bool DATABASE::IsPINCodeProtected(int AccID)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	sprintf(Query, "SELECT PINCode FROM Accounts WHERE ID = '%d';", AccID);

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the PINCode for the specified user (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	MYSQL_ROW Row = mysql_fetch_row(Result);

	if (Row[0])
		return true;
	return false;
}

string DATABASE::GetPINCode(int AccID)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	sprintf(Query, "SELECT PINCode FROM Accounts WHERE ID = '%s';", AccID);

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the PINCode for the specified user (%d).\n", mysql_errno(this->db));
		return 0;
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the result (%d).\n", mysql_errno(this->db));
		return 0;
	}

	MYSQL_ROW Row = mysql_fetch_row(Result);
	string Res(Row[0]);

	return Res;
}

string DATABASE::GetCountryByIP(string IP)
{
	MYSQL_RES* Result;
	char Query[256] = { 0 };

	sprintf(Query, "SELECT country_code FROM IPs WHERE INET_ATON(\"%s\") <= ip_to LIMIT 1", ASQLi::FilterQuery(IP.c_str()));

	if (mysql_query(this->db, Query))
	{
		printf("[!] Unable to get the country_code for the specified IP (%d).\n", mysql_errno(this->db));
		return "-";
	}

	Result = mysql_store_result(this->db);
	if (!Result)
	{
		printf("[!] Unable to store the result (%d).\n", mysql_errno(this->db));
		return "-";
	}

	MYSQL_ROW Row = mysql_fetch_row(Result);
	string Res(Row[0]);

	return Res;
}


#else



#endif