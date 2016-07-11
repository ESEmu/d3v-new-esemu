#include "PvP Handler.h"

namespace Modes
{
	PVPHandler::PVPHandler()
	{
		this->m_Approvals = NULL;
		this->m_ID = NULL;
		this->m_Load = NULL;
		this->m_Mode = NULL;
	}

	PVPHandler::~PVPHandler()
	{
		this->m_Approvals = NULL;
		this->m_ID = NULL;
		this->m_Load = NULL;
		this->m_Mode = NULL;
		this->m_BlueTeam.clear();
		this->m_RedTeam.clear();
	}

	unsigned int					PVPHandler::GetID()
	{
		return this->m_ID;
	}

	void							PVPHandler::SetID(int id)
	{
		this->m_ID = id;
	}

	int								PVPHandler::GetMode()
	{
		return this->m_Mode;
	}

	void							PVPHandler::SetMode(int mode)
	{
		this->m_Mode = mode;
	}

	void							PVPHandler::AddPlayer(int team, Player::Player* player)
	{
		switch (team) 
		{
		case RED_TEAM:
			this->m_RedTeam.push_back(player);
			break;
		case BLUE_TEAM:
			this->m_BlueTeam.push_back(player);
			break;
		}
	}

	void							PVPHandler::ApprovePVP()
	{
		this->m_Approvals++;
	}

	int								PVPHandler::GetApprovals()
	{
		return this->m_Approvals;
	}

	void							PVPHandler::DoneLoad()
	{
		this->m_Load++;
	}

	int								PVPHandler::GetLoaded()
	{
		return this->m_Load;
	}

	std::vector<Player::Player*>&	PVPHandler::GetTeam(int team)
	{
		switch (team) 
		{
		case RED_TEAM:
			return this->m_RedTeam;
			break;
		case BLUE_TEAM:
			return this->m_BlueTeam;
			break;
		}
	}

}