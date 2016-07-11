#include "Random.h"
#include <random>

namespace Random {

	std::string alphaNumeric(int length) {

		std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::string random = "";

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(1, alphanum.length());

		for (int i = 0; i < length; ++i) {
			random += alphanum[distribution(rng)];
		}

		return random;
	}

	std::string numeric(int length, int lowerBound, int upperBound) {

		std::string num = "0123456789";
		std::string random = "";

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(lowerBound, upperBound);

		for (int i = 0; i < length; ++i) {
			random += num[distribution(rng)];
		}

		return random;
	}

	std::string alpha(int length) {

		std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::string random = "";

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(1, alpha.length());

		for (int i = 0; i < length; ++i) {
			random += alpha[distribution(rng)];
		}

		return random;

	}

	int integer(int lowerBound, int upperBound) {

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(lowerBound, upperBound);

		return distribution(rng);

	}

}