#include "DDataProvider.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

namespace Providers
{
	namespace Dungeons
	{
		void LoadDungeons(string area)
		{
			ifstream fin("data/Dungeons/dg_" + area + ".dgl");

			int dungeonGate, dungeonID;
			fin >> dungeonGate;

			vector<std::pair<int, int> > dg;

			while (fin >> dungeonID) {
				dg.push_back(make_pair(dungeonID, 0));
			}

			dungeons.insert(make_pair(dungeonGate, dg));

			fin.close();
		}

		void Init()
		{
			LoadDungeons("Ruben");
			LoadDungeons("Elder");

			// TODO: Add other regions.

		}

		vector<pair<int, int> >* GetRegion(int dungeonGate)
		{
			if (dungeons.find(dungeonGate) != dungeons.end())
				return &dungeons[dungeonGate];
			else 
			{
				for (auto area : dungeons) 
				{
					for (auto i = area.second.begin(); i != area.second.end(); i++) 
					{
						if (i->first == dungeonGate)
							return &area.second;
					}
				}
			}
			return nullptr;
		}
	}
}