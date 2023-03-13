#pragma once
#include "PCH.h"
#include <vector>					// For std::vector

using namespace std;

namespace FM
{
	struct GameData {

		static	vector<OM::Object>			vO;
		static	vector<OM::ObjectInst>		vOI;
		static	vector<OM::ObjectLayer>		vOL;
		static	OM::Character				player;
		static	vector<OM::Platform>		platforms;
		static	vector<OM::Portraits>		portraits;
		
	
		
		void	LoadShapeFromFile();
		void	LoadTransformFromFile();
		void	LoadPlayerStatsFromFile();
		void	LoadLayersFromFile();
		void	SaveProgress();
		void	OptionChange();
		
	};

}// END namespace FM
