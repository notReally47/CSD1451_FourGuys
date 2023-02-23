#pragma once
#include <vector>				// For std::vector
#include "DataFiles.h"			// For GameObjects::

namespace Level_Initializer {

	using namespace std;



	void Init_Object_From_Vector	(vector<GameObjects::ObjectInst> vOBJ_INST, GameObjects::ObjectInst object_instance[], size_t object_instance_size);
	void Init_Player				(GameObjects::ObjectInst* OBJ_INST, GameObjects::Character* sCHARACTER, GameObjects::Character& p_player);



}// END namspace Level_Initializer
