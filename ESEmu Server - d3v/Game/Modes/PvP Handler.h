#pragma once
#ifndef _PVPHANDLER_H_
#define _PVPHANDLER_H_

#include <vector>
#include "..\Player\Player.h"
using namespace std;

namespace Modes
{
	class PVPHandler
	{
		#define RED_TEAM	1
		#define BLUE_TEAM	2

	private:

		unsigned int					m_ID;
		int								m_Mode;
		int								m_Approvals;
		int								m_Load;
		std::vector<Player::Player*>	m_RedTeam;
		std::vector<Player::Player*>	m_BlueTeam;

	public:

		PVPHandler();
		~PVPHandler();
		unsigned int					GetID();
		void							SetID(int id);
		int								GetMode();
		void							SetMode(int mode);
		void							AddPlayer(int team, Player::Player* player);
		void							ApprovePVP();
		int								GetApprovals();
		void							DoneLoad();
		int								GetLoaded();
		std::vector<Player::Player*>&	GetTeam(int team);

	};
}

#endif