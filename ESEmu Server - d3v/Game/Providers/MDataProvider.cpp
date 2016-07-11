#include "MDataProvider.h"

#include <fstream>
#include <utility>
#include <iostream>

namespace Providers
{
	namespace Maps
	{
		void LoadMaps()
		{
			for (int i = 20000; i < 20008; i++) {
				Environment::MapHandler map(i);
				Environment::WorldHandler::AddMap(map);
			}

			for (int i = 30000; i < 30007; i++) {
				Environment::MapHandler map(i);
				Environment::WorldHandler::AddMap(map);
			}
		}
	}
}