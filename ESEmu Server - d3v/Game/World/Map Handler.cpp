#include "Map Handler.h"

namespace Environment
{
	MapHandler::MapHandler(unsigned int ID)
	{
		this->m_ID = ID;
	}

	MapHandler::MapHandler()
	{
		this->m_ID = NULL;
	}

	MapHandler::~MapHandler()
	{
		this->m_ID = NULL;
		this->m_Parties.clear();
		this->m_Players.clear();
	}

	int											MapHandler::GetID()
	{
		return this->m_ID;
	}

	map<int, Player::Player*>*					MapHandler::GetPlayers()
	{
		return &this->m_Players;
	}

	void										MapHandler::AddPlayer(Player::Player* player)
	{
		this->m_Players.insert(std::make_pair(player->GetPlayerID(), player));
	}

	void										MapHandler::RemovePlayer(int id)
	{
		if (this->m_Players.find(id) != this->m_Players.end())
			this->m_Players.erase(id);
	}

	void										MapHandler::AddParty(Player::PartyHandler* party)
	{
		this->m_Parties.insert(make_pair(party->GetID(), party));
	}

	void										MapHandler::DelParty(long long pid)
	{
		if (this->m_Parties.find(pid) != this->m_Parties.end()) {
			this->m_Parties.erase(pid);
		}
	}

	map<long long, Player::PartyHandler*>*		MapHandler::GetParties()
	{
		return &this->m_Parties;
	}

}