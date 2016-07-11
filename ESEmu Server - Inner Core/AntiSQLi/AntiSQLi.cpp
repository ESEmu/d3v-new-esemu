#include "AntiSQLi.h"

char ASQLi::Pattern[] = "'();\\-!=";

char* ASQLi::FilterQuery(char* QInput)
{
	string str(QInput);

	for (unsigned int i = 0; i < strlen(Pattern); ++i)
	{
		str.erase(remove(str.begin(), str.end(), Pattern[i]), str.end());
	}
	return (char*)str.c_str();
}

string ASQLi::FilterQuery(string QInput)
{

	for (unsigned int i = 0; i < strlen(Pattern); ++i)
	{
		QInput.erase(remove(QInput.begin(), QInput.end(), Pattern[i]), QInput.end());
	}
	return QInput;
}

