#include "ConfigReader.h"
#include <stdexcept>
#include <iostream>
#pragma warning (disable: 4172, 4005)

#define SERVER_INNER_PORT 9800

#if LUA_VERSION_NUM >= 502
	#define lua_strlen lua_rawlen
#endif

bool booleanString(const std::string& str)
{
	if (str.empty()) {
		return false;
	}

	char ch = tolower(str.front());
	return ch != 'f' && ch != 'n' && ch != '0';
}

ConfigManager::ConfigManager()
{
	this->m_isLoaded = false;
}

ConfigManager::~ConfigManager()
{
	//
}

bool ConfigManager::load()
{
	lua_State* L = luaL_newstate();
	if (!L)
	{
		printf("Can't allocate memory.\n");
		throw std::runtime_error("Failed to allocate memory");
	}

	luaL_openlibs(L);

	if (luaL_dofile(L, "ICSettings.lua")) {
		printf("Cannot open file.\n%s\n", lua_tostring(L, -1));
		lua_close(L);
		return false;
	}

	// parse config
	
	if (!this->m_isLoaded)
	{

		// ------- LICENSE & INTERNAL
		this->StringCFG[SERVER_IP] = this->getGlobalString(L, "ServerIP", "127.0.0.1");
		this->StringCFG[SERVER_NAME] = this->getGlobalString(L, "ServerName", "d3vil401");
		this->StringCFG[LICENSE_FILE] = this->getGlobalString(L, "License", "License.d3v");
		this->IntegerCFG[SERVER_CHANNELS] = this->getGlobalNumber(L, "Channels", 1);
		this->IntegerCFG[SERVER_PORT] = this->getGlobalNumber(L, "ServerPort", SERVER_INNER_PORT);
		// ----------------

		// ------- DATABASE
		this->StringCFG[DB_HOST] = this->getGlobalString(L, "DBHost", "127.0.0.1");
		this->IntegerCFG[DB_PORT] = this->getGlobalNumber(L, "DBPort", 3304);
		this->StringCFG[DB_USER] = this->getGlobalString(L, "DBUser", "root");
		this->StringCFG[DB_PASSWORD] = this->getGlobalString(L, "DBPass", "");
		this->StringCFG[DB_DATABASE] = this->getGlobalString(L, "DBDatabase", "ESEmu");
		// ----------------
	}
	
	// ------- LICENSE & INTERNAL
	this->StringCFG[SERVER_IP] = this->getGlobalString(L, "ServerIP", "127.0.0.1");
	this->StringCFG[SERVER_NAME] = this->getGlobalString(L, "ServerName", "d3vil401");
	this->StringCFG[LICENSE_FILE] = this->getGlobalString(L, "License", "License.d3v");
	this->IntegerCFG[SERVER_CHANNELS] = this->getGlobalNumber(L, "Channels", 1);
	this->IntegerCFG[SERVER_PORT] = this->getGlobalNumber(L, "ServerPort", SERVER_INNER_PORT);
	// ----------------

	// ------- DATABASE
	this->StringCFG[DB_HOST] = this->getGlobalString(L, "DBHost", "127.0.0.1");
	this->IntegerCFG[DB_PORT] = this->getGlobalNumber(L, "DBPort", 3304);
	this->StringCFG[DB_USER] = this->getGlobalString(L, "DBUser", "root");
	this->StringCFG[DB_PASSWORD] = this->getGlobalString(L, "DBPass", "");
	this->StringCFG[DB_DATABASE] = this->getGlobalString(L, "DBDatabase", "ESEmu");
	// ----------------

	this->m_isLoaded = true;
	lua_close(L);
	return true;
}

bool ConfigManager::reload()
{
	if (!this->m_isLoaded) {
		return false;
	}

	bool result = this->load();
	return result;
}

const std::string& ConfigManager::getString(string_config_t _what) const
{
	char* Noll = "NULL";
	if (this->m_isLoaded && _what < LAST_STRING_CONFIG) {
		return StringCFG[_what];
	}
	else {
		printf("Warning about ConfigManager::getString() -> %s", _what);
		return Noll;
	}
}

int32_t ConfigManager::getNumber(integer_config_t _what) const
{
	if (this->m_isLoaded && _what < LAST_INTEGER_CONFIG) {
		return IntegerCFG[_what];
	}
	else {
		//CM->Write(LOG_WARN, "Warning about ConfigManager::getNumber() -> %s", _what);
		return 0;
	}
}

bool ConfigManager::getBoolean(boolean_config_t _what) const
{
	if (this->m_isLoaded && _what < LAST_BOOLEAN_CONFIG) {
		return BoolCFG[_what];
	}
	else {
		//CM->Write(LOG_WARN, "Warning about ConfigManager::getBoolean() -> %s", _what);
		return false;
	}
}

std::string ConfigManager::getGlobalString(lua_State* _L, const std::string& _identifier, const std::string& _default)
{
	lua_getglobal(_L, _identifier.c_str());

	if (!lua_isstring(_L, -1)) {
		return _default;
	}

	size_t len = lua_strlen(_L, -1);
	std::string ret(lua_tostring(_L, -1), len);
	lua_pop(_L, 1);
	return ret;
}

int32_t ConfigManager::getGlobalNumber(lua_State* _L, const std::string& _identifier, const int32_t _default)
{
	lua_getglobal(_L, _identifier.c_str());

	if (!lua_isnumber(_L, -1)) {
		return _default;
	}

	int32_t val = (int32_t)lua_tonumber(_L, -1);
	lua_pop(_L, 1);
	return val;
}

std::string ConfigManager::getGlobalStringField(lua_State* _L, const std::string& _identifier, const int32_t _key, const std::string& _default)
{
	lua_getglobal(_L, _identifier.c_str());

	lua_pushnumber(_L, _key);
	lua_gettable(_L, -2);  /* get table[key] */

	if (!lua_isstring(_L, -1)) {
		return _default;
	}

	std::string result = lua_tostring(_L, -1);
	lua_pop(_L, 2);  /* remove number and key*/
	return result;
}