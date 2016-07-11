#include "IDataProvider.h"

namespace Providers
{
	namespace Items
	{
		void Init(short Modality)
		{
			printf("[+] Loading Items Provider...\n");

			if (Modality == IPD_LOADERMODE_LUA)
			{
				lua_getglobal(LUAProviders::GetLVM(), "Load_PItems");

				if (lua_pcall(LUAProviders::GetLVM(), 0, 0, 0) != 0)
				{
					printf("[!] Unable to load Load_PItems function!\n");
					return;
				}
			}

			if (Modality == IPD_LOADERMODE_KIM)
			{
				// KIMLoader::Load();
			}

			if (Modality == IPD_LOADERMODE_DATABASE)
			{
				// DATABASE::LoadItems();
			}
		}

		Constants::itemType GetItemType(unsigned int ItemID)
		{
			LUAProviders::GetLock()->lock();

			lua_getglobal(LUAProviders::GetLVM(), "getItemType");
			lua_pushnumber(LUAProviders::GetLVM(), ItemID);
			lua_call(LUAProviders::GetLVM(), 1, 1);

			int type = lua_tonumber(LUAProviders::GetLVM(), -1);
			lua_pop(LUAProviders::GetLVM(), 1);
			LUAProviders::GetLock()->unlock();

			return (Constants::itemType)type;
		}

		bool IsDecorative(unsigned int ItemID)
		{
			LUAProviders::GetLock()->lock();

			lua_getglobal(LUAProviders::GetLVM(), "isDecorative");
			lua_pushnumber(LUAProviders::GetLVM(), ItemID);
			lua_call(LUAProviders::GetLVM(), 1, 1);

			bool isdecor = lua_toboolean(LUAProviders::GetLVM(), -1);
			lua_pop(LUAProviders::GetLVM(), 1);
			LUAProviders::GetLock()->unlock();

			return isdecor;
		}

		int	GetItemLevel(unsigned int ItemID)
		{
			LUAProviders::GetLock()->lock();

			lua_getglobal(LUAProviders::GetLVM(), "getItemLevel");
			lua_pushnumber(LUAProviders::GetLVM(), ItemID);
			lua_call(LUAProviders::GetLVM(), 1, 1);

			int level = lua_tointeger(LUAProviders::GetLVM(), -1);
			lua_pop(LUAProviders::GetLVM(), 1);
			LUAProviders::GetLock()->unlock();

			return level;
		}

		int	GetItemGrade(unsigned int ItemID)
		{
			LUAProviders::GetLock()->lock();

			lua_getglobal(LUAProviders::GetLVM(), "getItemGrade");
			lua_pushnumber(LUAProviders::GetLVM(), ItemID);
			lua_call(LUAProviders::GetLVM(), 1, 1);

			int grade = lua_tointeger(LUAProviders::GetLVM(), -1);
			lua_pop(LUAProviders::GetLVM(), 1);
			LUAProviders::GetLock()->unlock();

			return grade;
		}

		int	MapToInvType(unsigned int ItemID, bool IsEquipped, bool IsDecorative)
		{
			int type = GetItemType(ItemID);

			switch (type) 
			{
			case 1: // attack
			case 2: // defence
				if (IsEquipped) 
					return 9;
				else if (IsDecorative) 
					return 7; // decoratives
				else 
					return 1;
			case 3:
				if (IsEquipped) 
					return 9;
				return 2; // accessory
			case 5:
				return 6; // consume
			case 6:
				return 3; // material
			case 7:
				return 4; // special
			case 8:
				return 5; // quest
			default:
				return 0;
		}
	}
}