#include "ESEAH Handler.h"

#include <iostream>

namespace Player
{
	ESEAHSession::ESEAHSession()
	{
		this->m_Group = NULL;
		this->m_Strikes = NULL;
		this->m_SuspectScore = NULL;
		memset(this->m_Flags, 0x00, sizeof(this->m_Flags));
	}

	ESEAHSession::~ESEAHSession()
	{
		this->m_Group = NULL;
		this->m_Strikes = NULL;
		this->m_SuspectScore = NULL;
		memset(this->m_Flags, 0x00, sizeof(this->m_Flags));
	}

	void ESEAHSession::IncreaseScore()
	{
		this->m_SuspectScore++;
	}

	void ESEAHSession::IncreaseScoreBy(short Amount)
	{
		this->m_SuspectScore += Amount;
	}

	void ESEAHSession::SetScore(short Score)
	{
		this->m_SuspectScore = Score;
	}

	void ESEAHSession::PromoteGroup()
	{
		this->m_Group++;
	}

	void ESEAHSession::DecreaseGroup()
	{
		--this->m_Group;
	}

	void ESEAHSession::SetFlag(short FlagID, bool Status)
	{
		this->m_Flags[FlagID] = Status;
	}

	bool ESEAHSession::GetFlag(short FlagID)
	{
		return this->m_Flags[FlagID];
	}

	void ESEAHSession::Ban()
	{
		// TODO
	}

	void ESEAHSession::Report()
	{
		// TODO:
		//   - Create and algorithm to identify whenever the bastard is hacking... d3vil401, bring out your calculus skills!
	}
}