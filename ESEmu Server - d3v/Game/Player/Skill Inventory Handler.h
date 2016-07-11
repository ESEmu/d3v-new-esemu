#pragma once
#ifndef _SKILLINVHANDLER_H_
#define _SKILLINVHANDLER_H_

#include <map>
using namespace std;

namespace Player
{
	class SkillInvHandler
	{
	private:

		map<int, int>		m_SkillInv;
		int					m_SkillSlots[8];
		unsigned int		m_RemSP;

	public:

		SkillInvHandler();
		~SkillInvHandler();

		// GETs

		int					GetSkillLevel(int Skill);
		bool				HasSkill(int SkillID);
		map<int, int>*		GetSkillInventory(); // skillid, level
		unsigned int		GetRemainingSP();
		int*				GetEquippedSkills();

		// SETs

		void				SetSP(int Amount);
		void				AddSP(int Amount);
		void				SetSkillLevel(int Skill, int Level);
		void				AddSkill(int Skill, int Level);

	};
}

#endif