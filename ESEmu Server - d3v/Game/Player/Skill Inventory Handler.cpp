#include "Skill Inventory Handler.h"

#include <cstring>

namespace Player
{
	SkillInvHandler::SkillInvHandler()
	{
		this->m_RemSP = 0;
		memset(this->m_SkillSlots, 0, sizeof(this->m_SkillSlots));
	}

	SkillInvHandler::~SkillInvHandler()
	{
		this->m_RemSP = NULL;
		this->m_SkillInv.clear();
		memset(this->m_SkillSlots, 0, sizeof(this->m_SkillSlots));
	}

	// GETs

	int					SkillInvHandler::GetSkillLevel(int Skill)
	{
		if (this->HasSkill(Skill))
			return this->m_SkillInv[Skill];
		else
			return 0;
	}

	bool				SkillInvHandler::HasSkill(int SkillID)
	{
		if (this->m_SkillInv.find(SkillID) != this->m_SkillInv.end())
			return true;
		else
			return false;
	}

	map<int, int>*		SkillInvHandler::GetSkillInventory() // skillid, level
	{
		return &this->m_SkillInv;
	}
	
	unsigned int		SkillInvHandler::GetRemainingSP()
	{
		return this->m_RemSP;
	}

	int*				SkillInvHandler::GetEquippedSkills()
	{
		return &this->m_SkillSlots[0];
	}

	// SETs

	void				SkillInvHandler::SetSP(int Amount)
	{
		this->m_RemSP = Amount;
	}

	void				SkillInvHandler::AddSP(int Amount)
	{
		this->m_RemSP += Amount;
	}

	void				SkillInvHandler::SetSkillLevel(int Skill, int Level)
	{
		// TODO: Check if enough SP to advance level!
		//if (this->HasSkill(Skill) && Level <= this->m_RemSP) 
		//{
		this->m_SkillInv[Skill] = Level;
			//this->AddSP(-sp); // deduct sp used
		//}
	}

	void				SkillInvHandler::AddSkill(int Skill, int Level)
	{
		this->m_SkillInv[Skill] = Level;
	}

}