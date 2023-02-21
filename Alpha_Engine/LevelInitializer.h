#pragma once
#include <vector>				// For std::vector
#include "DataFiles.h"			// For Load_Data_From_File:: & GameObjects::

namespace Level_Initializer {

	using namespace std;
	void Init_Object(vector<Load_Data_From_File::ObjectTransform>& vOT, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size);
	void Init_Player(Load_Data_From_File::PlayerProperties* PP, GameObjects::Character& p_player, GameObjects::Object* object, GameObjects::ObjectInst object_instance);

}// END namspace Level_Initializer
