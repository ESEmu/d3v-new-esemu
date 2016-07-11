#pragma once
#ifndef _ESEAH_H_
#define _ESEAH_H_

namespace Player
{
	#define FLAGID_SPEEDHACK		1
	#define FLAGID_NULLCOOLDOWN		2
	#define FLAGID_EDHACK			3
	#define FLAGID_ECHACK			4
	#define FLAGID_PARTYHACK		5
	#define FLAGID_SESSIONHIJACK	6

	class ESEAHSession
	{
	private:

		short			m_Strikes;		// INFINITE
		short			m_SuspectScore; // 0 - 100 S Score
		unsigned char	m_Group;		// 1. Normal (0 - 10)
										// 2. Low Suspect (11 - 20)
										// 3. Medium (21 - 40)
										// 4. Uhm... Suspect (41 - 55)
										// 5. High	( 56 - 80)
										// 6. Clearly cheating (idiot, update hacks!) (CRITICAL) (81 - 100)

		bool			m_Flags[5];		// 0. Speedhack
										// 1. Null cooldown
										// 2. ED Hack
										// 3. EC Hack
										// 4. Party Hack
										// 5. Stolen Session Token Hack

	public:

		ESEAHSession();
		~ESEAHSession();

		void IncreaseScore();
		void IncreaseScoreBy(short Amount);
		void SetScore(short Score);
		void PromoteGroup();
		void DecreaseGroup();
		void SetFlag(short FlagID, bool Status);
		bool GetFlag(short FlagID);
		void Ban();

		void Report();
	};
}

#endif