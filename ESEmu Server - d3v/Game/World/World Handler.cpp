#include "World Handler.h"

#include <map>
#include <vector>
#include "..\Modes\PvP Handler.h"
#include "..\Player\Player.h"
#include "..\Player\Party Handler.h"

namespace Environment
{
	namespace WorldHandler
	{
		bool HasClient(string ip) 
		{
			if (m_Clients.find(ip) != m_Clients.end()) return true;
			else return false;
		}

		pair<Server*, SockHandler*>* GetClient(std::string ip)
		{
			return &m_Clients[ip];
		}

		void AddClient(string ip, SockHandler* conn) 
		{
			m_Clients.insert(make_pair(ip, make_pair(conn, nullptr)));
		}

		void AddMap(Environment::MapHandler map) 
		{
			m_World.insert(std::make_pair(map.GetID(), map));
		}

		Environment::MapHandler* GetMap(int mapid) 
		{
			auto it = m_World.find(mapid);
			if (it != m_World.end()) 
				return &it->second;
			else return nullptr;
		}

		std::mutex pmtx;

		long long AddParty(Player::PartyHandler* party) 
		{
			pmtx.lock();
			m_PartyCount++;
			long long a = m_PartyCount;
			m_Parties.insert(std::make_pair(m_PartyCount, *party));
			m_Parties[a].SetID(m_PartyCount);
			pmtx.unlock();
			return a;
		}

		void DelParty(long long pid) 
		{
			m_Parties.erase(pid);
		}

		Player::PartyHandler* GetParty(long long pid) 
		{
			return &m_Parties[pid];
		}

		void PvPQueue(int mode, Player::Player* player) 
		{
			m_PvPQueue[mode].insert(make_pair(player->GetPlayerID(), player));
		}

		void PvPUnqueue(int mode, int id) 
		{
			if (m_PvPQueue[mode].find(id) != m_PvPQueue[mode].end())
				m_PvPQueue[mode].erase(id);
		}

		std::map<int, Player::Player*>& GetPVPQueue(int mode) 
		{
			return m_PvPQueue[mode];
		}

		std::mutex pvpmtx;

		int AddPVPMatch(int mode, Modes::PVPHandler match) 
		{
			pvpmtx.lock();
			match.SetID(m_PvPID + (mode + 1) * 1000000);
			m_PvPMatch[mode].insert(std::make_pair(m_PvPID + (mode + 1) * 1000000, match));
			int ret = m_PvPID + (mode + 1) * 1000000;
			m_PvPID++;
			pvpmtx.unlock();

			return ret;
		}

		Modes::PVPHandler* getPVPMatch(int id) 
		{
			if (m_PvPMatch[id % 1000000].find(id) != m_PvPMatch[id % 1000000].end()) 
			{
				return &m_PvPMatch[id % 1000000][id];
			}
		}
	}
}