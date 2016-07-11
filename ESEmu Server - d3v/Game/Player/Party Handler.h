#pragma once
#ifndef _PARTYHANDLER_H_
#define _PARTYHANDLER_H_

#include <map>
#include "Player.h"
using namespace std;

namespace Player
{
	class PartyHandler
	{
	private:

		map<int, Player*>	m_Members;
		Player*				m_Leader;
		long long			m_ID;

	public:

		PartyHandler();
		~PartyHandler();
		void					SetLeader(Player* player);
		Player*					GetLeader();
		int						GetSize();
		void					AddMember(Player* player);
		void					KickMember(int chrid);
		bool					HasMember(int chrid);
		map<int, Player*>*		GetMembers();
		void					SetID(long long id);
		long long				GetID();

	};
}

#endif