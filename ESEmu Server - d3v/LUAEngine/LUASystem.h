#pragma once
#ifndef _LUASYSTEM_H_
#define _LUASYSTEM_H_

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <stdint.h>
#include <vector>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <dirent.h>
#include <mutex>
#include <hash_map>
#include <iterator>
#include "..\Game\Player\Player.h"
#pragma comment(lib, "User32.lib")
#pragma comment (lib, "lua52.lib")

#if LUA_VERSION_NUM >= 502
	#define lua_strlen lua_rawlen
#endif

class LUASystem;
class LUASManager;

extern LUASManager g_LUAManager;
extern LUASystem*  g_LUAEngine;

enum _QUEST_EVENTS
{
	EVENT_ON_COMPLETE	= 1,
	EVENT_AWAITING		= 2,	
	EVENT_ON_ACCEPT		= 3,
	EVENT_ON_REFUSE		= 4,
	EVENT_NONE
};

enum _INTERACTION_EVENTS
{
	INTERACTION_TALKING				= 1,
	INTERACTION_ON_ACTION_SELECTION = 2,
	INTERACTION_FINISHED			= 3,
	INTERACTION_NONE
};

class LUASystem
{
private:
	lua_State* m_LVM;
	std::mutex m_Lock;

public:

	LUASystem();
	~LUASystem();

	void LoadScripts();
	void Shutdown();
	void Reload();
	void RegisterCore();

	inline std::mutex& GetLock()
	{
		return this->m_Lock;
	}

	void OnUnitEvent(); //World::Unit* Unit, const char* FunctionName, int EventType, World::Unit* AdditionalUnit, int AdditionalInfo);
	void OnQuestEvent(Player::Player* Unit, const char* FunctionName, int EventType, Player::Player* AdditionalUnit, int AdditionalInfo);
	void OnGameEntityEvent();
	void OnGameInteractionEvent();
	void Call(); //World::Unit* Unit, const char* FunctionName);
};

// Event counters, must be done after a while.
#define CREATURE_EVENT_COUNT	1	
#define QUEST_EVENT_COUNT		1

struct LUA_UnitBinding{ const char* Functions[CREATURE_EVENT_COUNT]; };
struct LUA_QuestBinding{ const char* Functions[QUEST_EVENT_COUNT]; };

class LUASManager
{
private:

	hash_map<unsigned int, LUA_UnitBinding> m_UnitMap;
	hash_map<unsigned int, LUA_QuestBinding> m_QuestMap;

public:

	LUASystem* m_LUAS;

	void Start();
	void Unload();

	void RegisterUnitEvent(unsigned int Id, unsigned int Event, const char * FunctionName);
	void RegisterQuestEvent(unsigned int Id, unsigned int Event, const char * FunctionName);
	void RegisterGameObjectEvent(unsigned int Id, unsigned int Event, const char * FunctionName);
	void RegisterUnitInteractionEvent(unsigned int Id, unsigned int Event, const char * FunctionName);
	void RegisterItemInteractionEvent(unsigned int Id, unsigned int Event, const char * FunctionName);
	void RegisterInteractionEvent(unsigned int Id, unsigned int Event, const char * FunctionName);

	LUA_QuestBinding* GetQuestBinding(unsigned int Id)
	{
		hash_map<unsigned int, LUA_QuestBinding>::iterator it = this->m_QuestMap.find(Id);
		return (it == this->m_QuestMap.end()) ? NULL : &it->second;
	}
};

#endif
