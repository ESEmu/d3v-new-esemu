#include "AntiSQLi.h"
#pragma warning (disable: 4996)

char ASQLi::Pattern[] = "'();\\-!";

static void removeCharsFromString(string &str, char* charsToRemove)
{
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i)
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
}

static bool string_is_valid(const std::string &str)
{
	return find_if(str.begin(), str.end(),
		[](char c) { return !(isalnum(c)); }) == str.end();
}

char* ASQLi::FilterQuery(char* QInput)
{
	string str(QInput);
	
	removeCharsFromString(str, "\|!\"?$%&/()=?\''^¦Ì¦Ø¡ì¦È¦É+*[]¦Ç?¡ã#,;.:");
	if (!string_is_valid(str))
		return NULL;
	else {
		strcpy(QInput, str.c_str());
		return (char*)str.c_str();
	}
}

string ASQLi::FilterQuery(string QInput)
{
	removeCharsFromString(QInput, "\|!\"?$%&/()=?\''^¦Ì¦Ø¡ì¦È¦É+*[]¦Ç?¡ã#,;.:");
	if (!string_is_valid(QInput))
		return NULL;
	else
		return QInput;
}

