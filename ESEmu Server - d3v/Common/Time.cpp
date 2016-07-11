#include "Time.h"
#include <ctime>

namespace Time {

	std::string now() {

		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		std::string now;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);

		return now.assign(buffer);
	}

	std::string andnow()
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		std::string now;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, 80, "&%Y-%m-%d %H:%M:%S", &timeinfo);

		return now.assign(buffer);
	}

	std::string now_withoutNOW()
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		std::string now;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, 80, "%Y-%m-%d_%H.%M.%S", &timeinfo);

		return now.assign(buffer);
	}

	int timestamp()
	{
		return std::time(0);
	}

}