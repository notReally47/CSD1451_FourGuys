#pragma once
#include <string>					// For std::string
#include <vector>					// For std::vector
#include "DataFiles.h"				// For ObjectTransform, ObjectShape & PlayerProperties

namespace Extract_Data_To_File {

	using namespace std;

	void Extract_Transform_Data_Out(vector<GameObjects::ObjectInst> vOBJ_INST, GameObjects::Character p_player, const string level_number);


}// END namespace Extract_Data_To_File