#pragma once
#ifndef _DDATAPROVIDER_H_
#define _DDATAPROVIDER_H_

#include <map>
#include <vector>
using namespace std;

namespace Providers
{
	namespace Dungeons
	{
		static map<int, vector<pair<int, int>>> dungeons;

		void LoadDungeons(std::string area);
		void Init();
		vector<pair<int, int> >* GetRegion(int dungeonGate);
	}
}

#endif