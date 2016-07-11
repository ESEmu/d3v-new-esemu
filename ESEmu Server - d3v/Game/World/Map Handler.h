#pragma once
#ifndef _MAPHANDLER_H_
#define _MAPHANDLER_H_

#include <map>
#include "..\Player\Player.h"
#include "..\Player\Party Handler.h"
using namespace std;

namespace Environment
{
	class MapHandler
	{
	private:

		unsigned int							m_ID;
		map<int, Player::Player*>				m_Players;
		map<long long, Player::PartyHandler*>	m_Parties;

	public:

		MapHandler(unsigned int ID);
		MapHandler();
		~MapHandler();

		int											GetID();
		map<int, Player::Player*>*					GetPlayers();
		void										AddPlayer(Player::Player* player);
		void										RemovePlayer(int id);
		void										AddParty(Player::PartyHandler* party);
		void										DelParty(long long pid);
		map<long long, Player::PartyHandler*>*		GetParties();

	};
}

#endif