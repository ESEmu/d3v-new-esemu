#pragma once
#include <string>

namespace Random {

	std::string alphaNumeric(int length);
	std::string numeric(int length, int lowerBound = 0, int upperBound = 9);
	std::string alpha(int length);
	int integer(int lowerBound, int upperBound);

}