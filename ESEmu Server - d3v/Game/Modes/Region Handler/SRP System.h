#pragma once
#ifndef _SRPSYSTEM_H_
#define _SRPSYSTEM_H_

#include <map>
#include <vector>
#include "..\..\..\DBHandler\DBHandler.h"
#include "..\..\Player\Player.h"
using namespace std;

namespace Region
{
	class SRPSystem
	{
	private:

		map<Player::Player*, short> m_RegionQueue; // Player, RegionID

	public:

		

	};
}

#endif