#pragma once
#include <vector>			// For std::vector
#include "LoadValues.h"		// For Load_Values::

namespace Level_Initializer {
	using namespace std;
	void Init_Mesh_From_File(vector<Load_Values::ValueFromFile>& vff, GameObjects::Object& obj);
	void Init_Object_Instance(vector<Load_Values::ValueFromFile>& vff, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size);
}// END namspace Level_Initializer
