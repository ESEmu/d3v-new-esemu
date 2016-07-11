#include "Player.h"

#include <assert.h>

namespace Player
{
	Player::Player(unsigned long long accid, unsigned long long playerid, string name, string ip, string createDate, string lastLogin, unsigned int hp, unsigned int attack, unsigned int mattack, unsigned int def, unsigned int mdef, int map, DATABASE* DB) :
		m_AccountID(accid), m_PlayerID(playerid), m_Name(name), m_IP(ip), m_CreationDate(createDate), m_LastLogin(lastLogin), m_MaxHP(hp), m_BaseAttack(attack), m_BaseMagicAttack(mattack),
		m_BaseDef(def), m_BaseMagicDef(mdef), m_Map(map), m_DBHandle(DB)
	{
		this->m_AP = NULL;
		this->m_AHSession = nullptr;
		this->m_curDungeon = NULL;
		this->m_curPVPMatch = NULL;
		this->m_ED = NULL;
		this->m_EXP = NULL;
		this->m_Level = NULL;
		this->m_Party = nullptr;
		this->m_unitClass = Constants::unitClass::UC_NONE;
		this->m_unitType = Constants::unitType::UN_NONE;
	}

	Player::Player()
	{
		this->m_AccountID = NULL;
		this->m_PlayerID = NULL;
		this->m_AP = NULL;
		this->m_AHSession = nullptr;
		this->m_BaseAttack = NULL;
		this->m_BaseDef = NULL;
		this->m_BaseMagicAttack = NULL;
		this->m_BaseMagicDef = NULL;
		this->m_CreationDate = "";
		this->m_curDungeon = NULL;
		this->m_curPVPMatch = NULL;
		this->m_ED = NULL;
		this->m_EXP = NULL;
		this->m_IP = "";
		this->m_LastLogin = "";
		this->m_Level = NULL;
		this->m_Map = NULL;
		this->m_MaxHP = NULL;
		this->m_Name = "";
		this->m_Party = nullptr;
		this->m_PlayerID = NULL;
		this->m_unitClass = Constants::unitClass::UC_NONE;
		this->m_unitType = Constants::unitType::UN_NONE;
	}

	Player::~Player()
	{
		this->m_AccountID = NULL;
		this->m_PlayerID = NULL;
		this->m_AP = NULL;
		this->m_AHSession = nullptr;
		this->m_BaseAttack = NULL;
		this->m_BaseDef = NULL;
		this->m_BaseMagicAttack = NULL;
		this->m_BaseMagicDef = NULL;
		this->m_CreationDate = "";
		this->m_curDungeon = NULL;
		this->m_curPVPMatch = NULL;
		this->m_ED = NULL;
		this->m_EXP = NULL;
		this->m_IP = "";
		this->m_LastLogin = "";
		this->m_Level = NULL;
		this->m_Map = NULL;
		this->m_MaxHP = NULL;
		this->m_Name = "";
		this->m_Party = nullptr;
		this->m_PlayerID = NULL;
		this->m_unitClass = Constants::unitClass::UC_NONE;
		this->m_unitType = Constants::unitType::UN_NONE;
	}

	// GETs

	unsigned long long		Player::GetAccountID()
	{
		return this->m_AccountID;
	}

	unsigned long long		Player::GetPlayerID()
	{
		return this->m_PlayerID;
	}

	string					Player::GetName()
	{
		return this->m_Name;
	}

	string					Player::GetIP()
	{
		return this->m_IP;
	}

	string					Player::GetCreationDate()
	{
		return this->m_CreationDate;
	}

	string					Player::GetLastLogin()
	{
		return this->m_LastLogin;
	}

	unsigned char			Player::GetLevel()
	{
		return this->m_Level;
	}

	unsigned int			Player::GetED()
	{
		return this->m_ED;
	}

	unsigned int			Player::GetEXP()
	{
		return this->m_EXP;
	}

	unsigned int			Player::GetAP()
	{
		return this->m_AP;
	}

	Constants::unitType		Player::GetUnitType()
	{
		return this->m_unitType;
	}

	Constants::unitClass	Player::GetUnitClass()
	{
		return this->m_unitClass;
	}

	unsigned int			Player::GetMaxHP()
	{
		return this->m_MaxHP;
	}

	unsigned int			Player::GetBaseAttack()
	{
		return this->m_BaseAttack;
	}

	unsigned int			Player::GetBaseMagicAttack()
	{
		return this->m_BaseMagicAttack;
	}

	unsigned int			Player::GetBaseDef()
	{
		return this->m_BaseDef;
	}

	unsigned int			Player::GetBaseMagicDef()
	{
		return this->m_BaseMagicDef;
	}

	int						Player::GetMap()
	{
		return this->m_Map;
	}

	unsigned int			Player::GetCurDungeon()
	{
		return this->m_curDungeon;
	}

	unsigned int			Player::GetCurPVPMatch()
	{
		return this->m_curPVPMatch;
	}

	InventoryHandler*		Player::GetInv()
	{
		return &this->m_Inventory;
	}

	SkillInvHandler*		Player::GetSkillInv()
	{
		return &this->m_SkillInv;
	}

	PartyHandler*			Player::GetParty()
	{
		return this->m_Party;
	}

	string					Player::GetPlayerRegion()
	{
		return this->m_Region;
	}

	// SETs

	void					Player::SetName(string name)
	{
		if (name.length() > 6 && name.length() != 0)
			this->m_Name = name;
		else
			assert("Player::m_Name.lenght() < 6 || < 0!");
	}

	void					Player::SetLevel(unsigned char level)
	{
		this->m_Level = level;
	}

	void					Player::SetED(unsigned int ed)
	{
		this->m_ED = ed;
	}

	void					Player::SetEXP(unsigned int exp)
	{
		this->m_EXP = exp;
	}

	void					Player::SetAP(unsigned int ap)
	{
		this->m_AP = ap;
	}

	void					Player::SetUnitType(Constants::unitType unitType)
	{
		this->m_unitType = unitType;
	}

	void					Player::SetUnitClass(Constants::unitClass unitClass)
	{
		this->m_unitClass = unitClass;
	}

	void					Player::SetMaxHP(unsigned int hp)
	{
		this->m_MaxHP = hp;
	}

	void					Player::SetBaseAttack(unsigned int attack)
	{
		this->m_BaseAttack = attack;
	}

	void					Player::SetBaseMagicAttack(unsigned int mattack)
	{
		this->m_BaseMagicAttack = mattack;
	}

	void					Player::SetBaseDef(unsigned int def)
	{
		this->m_BaseDef = def;
	}

	void					Player::SetBaseMagicDef(unsigned int mdef)
	{
		this->m_BaseMagicDef = mdef;
	}

	void					Player::SetMap(unsigned int map)
	{
		this->m_Map = map;
	}

	void					Player::SetCurDungeon(unsigned int dungeon)
	{
		this->m_curDungeon = dungeon;
	}

	void					Player::SetCurPVPMatch(unsigned int match)
	{
		this->m_curPVPMatch = match;
	}

	void					Player::SetInventory(InventoryHandler* inv)
	{
		this->m_Inventory = *inv;
	}

	void					Player::SetParty(PartyHandler* party)
	{
		this->m_Party = party;
	}

	void					Player::SetPlayerRegion()
	{
		
	}

}