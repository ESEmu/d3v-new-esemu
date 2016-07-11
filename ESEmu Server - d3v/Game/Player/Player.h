#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "..\..\DBHandler\DBHandler.h"
#include "Inventory Handler.h"
#include "Skill Inventory Handler.h"
#include "ESEAH Handlers\ESEAH Handler.h"
#include "..\..\Common\Constants.h"
#include <string>
using namespace std;

namespace Player
{
	class PartyHandler;

	class Player
	{
	private:

		unsigned long long		m_AccountID;
		unsigned long long		m_PlayerID;
		
		string					m_Name;
		string					m_IP;
		string					m_CreationDate;
		string					m_LastLogin;
		string					m_Region;
		DATABASE*				m_DBHandle;

		unsigned char			m_Level;
		unsigned int			m_ED;
		unsigned int			m_EXP;
		unsigned int			m_AP;
		Constants::unitType		m_unitType;
		Constants::unitClass	m_unitClass;

		unsigned int			m_MaxHP;
		unsigned int			m_BaseAttack;
		unsigned int			m_BaseMagicAttack;
		unsigned int			m_BaseDef;
		unsigned int			m_BaseMagicDef;

		int						m_Map;
		unsigned int			m_curDungeon;
		unsigned int			m_curPVPMatch;

		InventoryHandler		m_Inventory;
		SkillInvHandler			m_SkillInv;

		PartyHandler*			m_Party;

		ESEAHSession*			m_AHSession;


	public:

		Player(unsigned long long accid, unsigned long long playerid, string name, string ip, string createDate, string lastLogin, unsigned int hp, unsigned int attack, unsigned int mattack, unsigned int def, unsigned int mdef, int map, DATABASE* DB);
		Player();
		~Player();

		// GETs

		unsigned long long		GetAccountID();
		unsigned long long		GetPlayerID();
		string					GetName();
		string					GetIP();
		string					GetCreationDate();
		string					GetLastLogin();
		unsigned char			GetLevel();
		unsigned int			GetED();
		unsigned int			GetEXP();
		unsigned int			GetAP();
		Constants::unitType		GetUnitType();
		Constants::unitClass	GetUnitClass();
		unsigned int			GetMaxHP();
		unsigned int			GetBaseAttack();
		unsigned int			GetBaseMagicAttack();
		unsigned int			GetBaseDef();
		unsigned int			GetBaseMagicDef();
		int						GetMap();
		unsigned int			GetCurDungeon();
		unsigned int			GetCurPVPMatch();
		InventoryHandler*		GetInv();
		SkillInvHandler*		GetSkillInv();
		PartyHandler*			GetParty();
		string					GetPlayerRegion();

		// SETs

		void					SetName(string name);
		void					SetLevel(unsigned char level);
		void					SetED(unsigned int ed);
		void					SetEXP(unsigned int exp);
		void					SetAP(unsigned int ap);
		void					SetUnitType(Constants::unitType unitType);
		void					SetUnitClass(Constants::unitClass unitClass);
		void					SetMaxHP(unsigned int hp);
		void					SetBaseAttack(unsigned int attack);
		void					SetBaseMagicAttack(unsigned int mattack);
		void					SetBaseDef(unsigned int def);
		void					SetBaseMagicDef(unsigned int mdef);
		void					SetMap(unsigned int map);
		void					SetCurDungeon(unsigned int dungeon);
		void					SetCurPVPMatch(unsigned int match);
		void					SetInventory(InventoryHandler* inv);
		void					SetParty(PartyHandler* party);
		void					SetPlayerRegion();

	};
}


#endif