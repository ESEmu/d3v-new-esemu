#include "Inventory Handler.h"

#include <assert.h>

namespace Player
{
	InventoryHandler::InventoryHandler()
	{
		for (auto i = 0; i < sizeof(this->m_Quantity); i++)
			this->m_Quantity[i] = NULL;
	}

	InventoryHandler::~InventoryHandler()
	{
		for (auto i = 0; i < sizeof(this->m_Quantity); i++)
			this->m_Quantity[i] = NULL;
		for (auto k = 0; k < sizeof(this->m_MaxSlots); k++)
			this->m_MaxSlots[k] = NULL;

		this->m_ItemsList.clear();
		this->m_Items->clear();
	}

	// GETs

	map<int, ItemHandler>*	InventoryHandler::GetInventory()
	{
		return &this->m_ItemsList;
	}

	vector<int>*			InventoryHandler::GetInventory(int InvType)
	{
		if (InvType < 11 && InvType != 0)
			return &this->m_Items[InvType];
		else
			assert("InventoryHandler::m_Items[InvType] > 11 || < 0 (GET)!");
	}

	ItemHandler*			InventoryHandler::GetItem(unsigned int UID)
	{
		map<int, ItemHandler>::iterator Item = this->m_ItemsList.find(UID);
		if (Item != this->m_ItemsList.end())
			return &Item->second;
		else 
			return nullptr;
	}

	short					InventoryHandler::GetMaxSlots(int InvType)
	{
		if (InvType < 11 && InvType != 0)
			return this->m_MaxSlots[InvType];
		else 
			return -1;
	}

	short					InventoryHandler::GetQuantity(int Type)
	{
		return this->m_Quantity[Type];
	}

	// SETs

	void					InventoryHandler::AddItem(ItemHandler* Item)
	{
		bool decorative = Providers::Items::IsDecorative(Item->GetIID());
		bool equipped = Item->GetIsEquipped();
		int type = Providers::Items::MapToInvType(Item->GetIID(), equipped, decorative);
		this->m_Quantity[type]++;
		this->m_ItemsList.insert(std::make_pair(Item->GetUID(), *Item));
		this->m_Items[type][Item->GetInvPosition()] = Item->GetUID();
	}

	void					InventoryHandler::RemoveItem(unsigned int UID)
	{
		auto item = this->m_ItemsList.find(UID);
		if (item != this->m_ItemsList.end())
		{
			bool decorative = Providers::Items::IsDecorative(item->second.GetIID());
			int invtype = Providers::Items::MapToInvType(item->second.GetIID(), item->second.GetIsEquipped(), decorative);
			this->m_ItemsList.erase(UID);
			replace(this->m_Items[invtype].begin(), this->m_Items[invtype].end(), UID, -1);
		}
	}

	unsigned int			InventoryHandler::FindItem(unsigned int IID)
	{
		for (auto item : this->m_ItemsList) 
		{
			if (item.second.GetIID() == IID)
				return item.second.GetIID();
		}
		return -1;
	}

	void					InventoryHandler::SetMaxSlots(int InvType, short nMS)
	{
		this->m_MaxSlots[InvType] = nMS;
		this->m_Items[InvType].assign(nMS, -1);
	}

	void					InventoryHandler::SetQuantity(int Type, short nQ)
	{
		this->m_Quantity[Type] = nQ;
	}

	void					InventoryHandler::ChangeQuantity(int Type, short nQ)
	{
		this->m_Quantity[Type] += nQ;
	}

}