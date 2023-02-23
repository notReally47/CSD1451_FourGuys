#pragma once
#include <vector>				// For std::vector
#include "DataFiles.h"			// For GameObjects::

namespace Level_Initializer {

	using namespace std;



	void Option_Change				(vector<GameObjects::ObjectInst>& vOBJ_INST);
	void Init_Player				(GameObjects::ObjectInst* OBJ_INST, GameObjects::Character* sCHARACTER, GameObjects::Character& p_player);



}// END namspace Level_Initializer
