#include "Party Handler.h"

namespace Player
{
	PartyHandler::PartyHandler()
	{
		this->m_ID = NULL;
		this->m_Leader = nullptr;
	}

	PartyHandler::~PartyHandler()
	{

		this->m_ID = NULL;
		this->m_Leader = nullptr;
		this->m_Members.clear();
	}

	void					PartyHandler::SetLeader(Player* player)
	{
		this->m_Leader = player;
	}

	Player*					PartyHandler::GetLeader()
	{
		return this->m_Leader;
	}

	int						PartyHandler::GetSize()
	{
		return this->m_Members.size() + 1;
	}

	void					PartyHandler::AddMember(Player* player)
	{
		this->m_Members.insert(make_pair(player->GetPlayerID(), player));
	}

	void					PartyHandler::KickMember(int chrid)
	{
		if (this->m_Members.find(chrid) != this->m_Members.end())
			this->m_Members.erase(chrid);
	}

	bool					PartyHandler::HasMember(int chrid)
	{
		if (this->m_Members.find(chrid) != this->m_Members.end())
			return true;
		else
			return false;
	}

	map<int, Player*>*		PartyHandler::GetMembers()
	{
		return &this->m_Members;
	}

	void					PartyHandler::SetID(long long id)
	{
		this->m_ID = id;
	}

	long long				PartyHandler::GetID()
	{
		return this->m_ID;
	}

}