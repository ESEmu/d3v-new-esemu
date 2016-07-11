#include "Skill Handler.h"

namespace Player
{
	SkillHandler::SkillHandler()
	{
		this->m_SID = NULL;
		this->m_Type = Constants::skillType::ST_NONE;
		this->m_Name = "";
		this->m_reqLearnSP = NULL;
		this->m_reqUpgradeSP = NULL;
		this->m_unitClass = Constants::unitClass::UC_NONE;
		this->m_masterLevel = NULL;

	}

	SkillHandler::~SkillHandler()
	{
		this->m_SID = NULL;
		this->m_Type = Constants::skillType::ST_NONE;
		this->m_Name = "";
		this->m_reqLearnSP = NULL;
		this->m_reqUpgradeSP = NULL;
		this->m_unitClass = Constants::unitClass::UC_NONE;
		this->m_masterLevel = NULL;
		this->m_reqCharLevel.clear();
		this->m_reqMP.clear();
		this->m_Cooldown.clear();
	}

	int						SkillHandler::GetSkillID()
	{
		return this->m_SID;
	}

	Constants::skillType	SkillHandler::GetSkillType()
	{
		return this->m_Type;
	}

	string					SkillHandler::GetSkillName()
	{
		return this->m_Name;
	}

	short					SkillHandler::GetReqLearnSP()
	{
		return this->m_reqLearnSP;
	}

	short					SkillHandler::GetReqUpgradeSP()
	{
		return this->m_reqUpgradeSP;
	}

	short					SkillHandler::GetReqCharLevel(short curLevel)
	{
		return this->m_reqCharLevel[curLevel];
	}

	short					SkillHandler::GetCooldown(short curLevel)
	{
		return this->m_Cooldown[curLevel];
	}

	short					SkillHandler::GetReqMP(short curLevel)
	{
		return this->m_reqMP[curLevel];
	}

	Constants::unitClass	SkillHandler::GetSkillUnitClass()
	{
		return this->m_unitClass;
	}

	short					SkillHandler::GetMasterLevel()
	{
		return this->m_masterLevel;
	}

}