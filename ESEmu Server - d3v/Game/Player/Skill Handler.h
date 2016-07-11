#pragma once
#ifndef _SKILLHANDLER_H_
#define _SKILLHANDLER_H_

#include <string>
#include <vector>
#include "..\..\Common\Constants.h"
using namespace std;

namespace Player
{
	class SkillHandler
	{
	private:

		int						m_SID;					// skill id: a unique identifier for the skill
		Constants::skillType	m_Type;					// skill type: indicates the type of the skill (eg. special active)
		string					m_Name;					// skill name: the name of the skill
		short					m_reqLearnSP;			// skill reqLearnSP: indicates the amount of SP required the learn the skill
		short					m_reqUpgradeSP;			// skill reqUpgradeSP: indicates amount of SP needed to raise level of skill
		vector<short>			m_reqCharLevel;			// skill reqCharLevel: indicates the level required to raise level of skill
		vector<short>			m_Cooldown;				// skill cooldown: the cooldown of the skill
		vector<short>			m_reqMP;				// skill reqMP: indicates the amount of MP required to use the skill

		Constants::unitClass	m_unitClass;			// skill unitClass: indicates the unit class that the skill belongs to
		short					m_masterLevel;			// skill masterLevel: indicates the max level of the skill

	public:

		SkillHandler();
		~SkillHandler();

		int						GetSkillID();						// returns the unique identifier of the skill
		Constants::skillType	GetSkillType();						// returns the type of the skill (eg. special active)
		string					GetSkillName();						// returns the name of the skill
		short					GetReqLearnSP();					// returns the amount of SP required the learn the skill
		short					GetReqUpgradeSP();					// returns the amount of SP needed to raise the level the skill
		short					GetReqCharLevel(short curLevel);	// returns the level required to raise level of skill. curLevel: current level of skill
		short					GetCooldown(short curLevel);		// returns the cooldown of the skill. curLevel: current level of the skill
		short					GetReqMP(short curLevel);			// returns the amount of SP needed to use the skill. curLevel: current level of the skill
		Constants::unitClass	GetSkillUnitClass();				// returns the unit class that the skill belongs to
		short					GetMasterLevel();					// returns the master level of the skill

	};
}

#endif