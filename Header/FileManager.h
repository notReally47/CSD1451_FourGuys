#pragma once
#include "PCH.h"
#include <string>					// For std::string
#include <vector>					// For std::vector

using namespace std;

namespace FM
{
	struct GameData {
		static vector<OM::Object>		vO;
		static vector<OM::ObjectInst>	vOI;
		static OM::Character			player;
		static vector<OM::ObjectInst>	platform;
		static vector<OM::ObjectInst>	portraits;
		static vector<OM::ObjectLayer>	vOL;
	
		
		void			LoadShapeFromFile();
		void			LoadTransformFromFile();
		void			LoadPlayerStatsFromFile();
		void			LoadLayersFromFile();
		void			Option_Change();
		//void			ExtractTransformToFile();
		
	};

	struct Export : public OM::ObjectInst, public OM::Character
	{
		void					Extract_Transform_Data_Out(vector<OM::ObjectInst> vOI, OM::Character p_player, const string level_number);
	};

}
