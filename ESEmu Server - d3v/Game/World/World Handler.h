#pragma once
#ifndef _WORLDHANDLER_H_
#define _WORLDHANDLER_H_

#include <map>
#include <vector>
#include "Map Handler.h"
#include "..\..\Network\SockHandler.h"
using namespace std;

namespace Environment
{
	class Player::Player;

	namespace WorldHandler
	{
		// Clients
		static map<string, pair<Server*, SockHandler*>>			m_Clients;

		bool													HasClient(string ip);
		pair<Server*, SockHandler*>*							GetClient(string ip);
		void													AddClient(string ip, SockHandler* conn);

		// World
		static map<int, Environment::MapHandler>				m_World;

		void													AddMap(Environment::MapHandler map);
		Environment::MapHandler*								GetMap(int mapid);

		// Parties
		static long long										m_PartyCount = 0;
		static std::map<long long, Player::PartyHandler>		m_Parties;

		long long												AddParty(Player::PartyHandler* party);
		void													DelParty(long long pid);
		Player::PartyHandler*									GetParty(long long pid);

		// PvP
		static map<int, Player::Player*>						m_PvPQueue[3];

		void													PvPQueue(int mode, Player::Player* player);
		void													PvPUnqueue(int mode, int id);
		map<int, Player::Player*>&								GetPvPQueue(int mode);

		static int												m_PvPID = 1;
		static std::map<int, Modes::PVPHandler>					m_PvPMatch[3];

		int														AddPvPMatch(int mode, Modes::PVPHandler match);
		Modes::PVPHandler*										GetPvPMatch(int id);

		// Dungeons


		// Fields


	}
}

#endif