#pragma once
#ifndef _ITEMHANDLER_H_
#define _ITEMHANDLER_H_

#include <string>
#include <vector>
#include <array>
#include "..\..\Common\Constants.h"
using namespace std;

namespace Player
{
	class ItemHandler
	{
	private:

		unsigned int	m_UID;
		unsigned int	m_IID;
		unsigned int	m_Amount;
		bool			m_IsEquipment;
		unsigned int	m_Endurance;
		bool			m_IsEquipped;
		short			m_InvPosition;
		unsigned char	m_Status;
		unsigned char	m_Upgrades;
		bool			m_IsSealed;
		
		vector<int>		m_Sockets;
		vector<int>		m_Effects;

		unsigned int	m_Attributes[3];
		unsigned int	m_AttrIndex;

		string			m_ExpiryDate;

	public:

		ItemHandler(unsigned int UID, unsigned int IID, unsigned int Endurance, unsigned int Amount, bool IsEquipped, bool IsEquip, short Position, string ExpiryDate);
		ItemHandler() {}
		~ItemHandler() {};

		// GETs
		unsigned int	GetUID();
		unsigned int	GetIID();
		unsigned int	GetAmount();
		bool			GetIsEquipment();
		unsigned int	GetEndurance();
		bool			GetIsEquipped();
		short			GetInvPosition();
		unsigned char	GetStatus();
		unsigned char	GetUpgrades();
		bool			GetIsSealed();
		unsigned int	GetAttribute(unsigned char Index);
		vector<int>*	GetSockets();
		vector<int>*	GetEffects();

		// SETs

		void			SetUID(unsigned int nUID);
		void			SetIID(unsigned int nIID);
		void			SetAmount(unsigned int nA);
		void			SetIsEquipment(bool nIE);
		void			SetEndurance(unsigned int nE);
		void			SetIsEquipped(bool nIE);
		void			SetInvPosition(short nP);
		void			SetStatus(unsigned char nS);
		void			SetUpgrades(unsigned char nU);
		void			SetIsSealed(bool nIS);
		void			SetAttribute(unsigned char Index, unsigned int nA);
		void			AddSocket(int nS);
		void			AddEffect(int nE);


	};
}

#endif