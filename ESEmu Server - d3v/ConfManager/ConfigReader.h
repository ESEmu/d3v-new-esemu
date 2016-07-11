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
		TEST_SERVER,
		LAST_BOOLEAN_CONFIG
	};

	enum string_config_t {
		LICENSE_FILE,
		HS_CERTIFICATE,
		DB_HOST,
		DB_USER,
		DB_PASSWORD,
		DB_DATABASE,
		CLIENT_VERSION,
		SERVER_NAME,
		SERVER_IP,
		LAST_STRING_CONFIG
	};

	enum integer_config_t {
		SERVER_CHANNELS,
		SERVER_LOGINS,
		SERVER_TYPE,
		SERVER_PORT,
		DB_PORT,
		MAX_CLIENTS,
		WORKER_THREADS,
		PRIORITY_LOW_BELOW,
		PRIORITY_LOW_ABOVE,
		PRIORITY_MEDIUM_BELOW,
		PRIORITY_MEDIUM_ABOVE,
		PRIORITY_HIGH_BELOW,
		PRIORITY_HIGH_ABOVE,
		PRIORITY_CRITICAL_BELOW,
		PRIORITY_CRITICAL_ABOVE,
		MAX_PINCODE_TRIALS,
		THREAD_MEMORY,
		LAST_INTEGER_CONFIG
	};

	bool load(short Type);

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
