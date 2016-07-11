#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class ASQLi
{
private:

	static char Pattern[];

protected:


public:

	static char*	FilterQuery(char*	QInput);
	static string	FilterQuery(string	QInput);
};