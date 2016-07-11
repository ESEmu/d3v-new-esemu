#include "Item Handler.h"

#include <assert.h>

namespace Player
{
	ItemHandler::ItemHandler()
	{
		this->m_UID = NULL;
		this->m_IID = NULL;
		this->m_Amount = NULL;
		this->m_IsEquipment = false;
		this->m_Endurance = NULL;
		this->m_IsEquipped = false;
		this->m_InvPosition = NULL;
		this->m_Status = NULL;
		this->m_Upgrades = NULL;
		this->m_IsSealed = false;

		this->m_Attributes[0] = NULL;
		this->m_Attributes[1] = NULL;
		this->m_Attributes[2] = NULL;
		this->m_Attributes[3] = NULL;
		this->m_AttrIndex = NULL;

		this->m_ExpiryDate = "";
	}

	ItemHandler::ItemHandler(unsigned int UID, unsigned int IID, unsigned int Endurance, unsigned int Amount, bool IsEquipped, bool IsEquip, short Position, string ExpiryDate) :
		m_UID(UID), m_IID(IID), m_Endurance(Endurance), m_IsEquipped(IsEquipped), m_IsEquipment(IsEquip), m_InvPosition(Position), m_ExpiryDate(ExpiryDate),
		m_Amount(Amount), m_AttrIndex(0)
	{
		this->m_Attributes[0] = NULL;
		this->m_Attributes[1] = NULL;
		this->m_Attributes[2] = NULL;
		this->m_Attributes[3] = NULL;
	}

	ItemHandler::~ItemHandler()
	{
		this->m_UID = NULL;
		this->m_IID = NULL;
		this->m_Amount = NULL;
		this->m_IsEquipment = false;
		this->m_Endurance = NULL;
		this->m_IsEquipped = false;
		this->m_InvPosition = NULL;
		this->m_Status = NULL;
		this->m_Upgrades = NULL;
		this->m_IsSealed = false;

		this->m_Attributes[0] = NULL;
		this->m_Attributes[1] = NULL;
		this->m_Attributes[2] = NULL;
		this->m_Attributes[3] = NULL;
		this->m_AttrIndex = NULL;

		this->m_ExpiryDate = "";
	}

	// GETs

	unsigned int	ItemHandler::GetUID()
	{
		return this->m_UID;
	}

	unsigned int	ItemHandler::GetIID()
	{
		return this->m_IID;
	}

	unsigned int	ItemHandler::GetAmount()
	{
		return this->m_Amount;
	}

	bool			ItemHandler::GetIsEquipment()
	{
		return this->m_IsEquipment;
	}

	unsigned int	ItemHandler::GetEndurance()
	{
		return this->m_Endurance;
	}

	bool			ItemHandler::GetIsEquipped()
	{
		return this->m_IsEquipped;
	}

	short			ItemHandler::GetInvPosition()
	{
		return this->m_InvPosition;
	}

	unsigned char	ItemHandler::GetStatus()
	{
		return this->m_Status;
	}

	unsigned char	ItemHandler::GetUpgrades()
	{
		return this->m_Upgrades;
	}

	bool			ItemHandler::GetIsSealed()
	{
		return this->m_IsSealed;
	}

	unsigned int	ItemHandler::GetAttribute(unsigned char Index)
	{
		if (Index < 5)
			return this->m_Attributes[Index];
		else
			assert("ItemHandler::m_Attributes[Index] > 5 (GET)!");
	}

	vector<int>*	ItemHandler::GetSockets()
	{
		return &this->m_Sockets;
	}

	vector<int>*	ItemHandler::GetEffects()
	{
		return &this->m_Effects;
	}

	// SETs

	void			ItemHandler::SetUID(unsigned int nUID)
	{
		this->m_UID = nUID;
	}

	void			ItemHandler::SetIID(unsigned int nIID)
	{
		this->m_IID = nIID;
	}

	void			ItemHandler::SetAmount(unsigned int nA)
	{
		this->m_Amount = nA;
	}

	void			ItemHandler::SetIsEquipment(bool nIE)
	{
		this->m_IsEquipment = nIE;
	}

	void			ItemHandler::SetEndurance(unsigned int nE)
	{
		this->m_Endurance = nE;
	}

	void			ItemHandler::SetIsEquipped(bool nIE)
	{
		this->m_IsEquipped = nIE;
	}

	void			ItemHandler::SetInvPosition(short nP)
	{
		this->m_InvPosition = nP;
	}

	void			ItemHandler::SetStatus(unsigned char nS)
	{
		this->m_Status = nS;
	}

	void			ItemHandler::SetUpgrades(unsigned char nU)
	{
		this->m_Upgrades = nU;
	}

	void			ItemHandler::SetIsSealed(bool nIS)
	{
		this->m_IsSealed = nIS;
	}

	void			ItemHandler::SetAttribute(unsigned char Index, unsigned int nA)
	{
		if (Index < 5)
		{
			if (Index != 0)
				this->m_AttrIndex++;
			else 
				--this->m_AttrIndex;

			this->m_Attributes[Index] = nA;
		}
		else
			assert("ItemHandler::m_Attributes[Index] > 5 (SET)!");
	}

	void			ItemHandler::AddSocket(int nS)
	{
		this->m_Sockets.push_back(nS);
	}

	void			ItemHandler::AddEffect(int nE)
	{
		this->m_Effects.push_back(nE);
	}

}