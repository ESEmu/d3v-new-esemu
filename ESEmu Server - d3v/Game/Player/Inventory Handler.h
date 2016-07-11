#pragma once
#ifndef _INVENTORYHANDLER_H_
#define _INVENTORYHANDLER_H_

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <array>
#include <functional>
#include "Item Handler.h"
#include "..\Providers\IDataProvider.h"
using namespace std;

namespace Player
{
	class InventoryHandler
	{
	private:

		map<int, ItemHandler>		m_ItemsList; // (UID, ItemInstance) -> Item Search
		vector<int>					m_Items[16]; // (UID, Item) -> Item Position Tracker
		short						m_MaxSlots[16];
		short						m_Quantity[16];

	public:

		InventoryHandler();
		~InventoryHandler();

		// GETs

		map<int, ItemHandler>*	GetInventory();
		vector<int>*			GetInventory(int InvType);
		ItemHandler*			GetItem(unsigned int UID);
		short					GetMaxSlots(int InvType);
		short					GetQuantity(int Type);

		// SETs

		void					AddItem(ItemHandler* Item);
		void					RemoveItem(unsigned int UID);
		unsigned int			FindItem(unsigned int IID);
		void					SetMaxSlots(int InvType, short nMS);
		void					SetQuantity(int Type, short nQ);
		void					ChangeQuantity(int Type, short nQ);
	
	};
}

#endif