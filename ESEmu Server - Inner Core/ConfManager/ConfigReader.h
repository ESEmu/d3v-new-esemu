#pragma once

extern "C" 
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <string>
#include <stdint.h>
#pragma comment (lib, "lua52.lib")

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	enum boolean_config_t {
		LAST_BOOLEAN_CONFIG
	};

	enum string_config_t {
		LICENSE_FILE,
		DB_HOST,
		DB_USER,
		DB_PASSWORD,
		DB_DATABASE,
		SERVER_NAME,
		SERVER_IP,
		LAST_STRING_CONFIG
	};

	enum integer_config_t {
		SERVER_CHANNELS,
		SERVER_PORT,
		DB_PORT,
		LAST_INTEGER_CONFIG
	};

	bool load();
	bool reload();

	const std::string& getString(string_config_t _what) const;
	int32_t getNumber(integer_config_t _what) const;
	bool getBoolean(boolean_config_t _what) const;

private:
	static std::string getGlobalString(lua_State* _L, const std::string& _identifier, const std::string& _default = "");
	static int32_t getGlobalNumber(lua_State* _L, const std::string& _identifier, const int32_t _default = 0);
	static std::string getGlobalStringField(lua_State* _L, const std::string& _identifier, const int32_t _key, const std::string& _default = "");

	bool m_isLoaded;
	std::string StringCFG[LAST_STRING_CONFIG];
	int32_t IntegerCFG[LAST_INTEGER_CONFIG];
	bool BoolCFG[LAST_BOOLEAN_CONFIG];
};
