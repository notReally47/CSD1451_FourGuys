#pragma once
#include <string>           // For std::string
#include <vector>           // For std::vector
#include "DataFiles.h"		// For Precompiled Header Files

namespace Load_Data_From_File{

	using namespace std;



	vector<GameObjects::Object>			Load_Shape_From_YAML		(const string level_number);
	vector<GameObjects::ObjectInst>		Load_Transform_From_YAML	(const string level_number, vector<GameObjects::Object>& vector_OBJ);
	GameObjects::Character*				Load_Player_Stats_From_YAML	(const string level_number);



}// END namespace Load_Data_From_File