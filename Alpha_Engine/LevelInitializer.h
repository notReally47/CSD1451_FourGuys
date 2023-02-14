#pragma once
#include <vector>				// For std::vector
#include "LoadValues.h"			// For Load_Values::
#include "LoadDataFromFile.h"	// For Load_Data_From_File::

namespace Level_Initializer {

	using namespace std;
	void Init_Mesh(vector<Load_Data_From_File::ObjectShape>& vOS, GameObjects::Object& object);
	void Init_Object(vector<Load_Data_From_File::ObjectTransform>& vOT, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size);

}// END namspace Level_Initializer
