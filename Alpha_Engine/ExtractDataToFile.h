#pragma once
#include <string>					// For std::string
#include <vector>					// For std::vector
#include "DataFiles.h"				// For ObjectTransform, ObjectShape & PlayerProperties

namespace Extract_Data_To_File{

	using namespace std;

	void Extract_Transform_Data_Out(vector<Load_Data_From_File::ObjectTransform>& vOT, Load_Data_From_File::PlayerProperties sPP, const string level_number);
	void Extract_Shape_Data_Out(vector<Load_Data_From_File::ObjectShape>& vOS, const string level_number);



}// END namespace Extract_Data_To_File