#include <vector>				// For std::vector	
#include "DataFiles.h"			// For GameObjects::

namespace Level_Initializer {
	using namespace std;
	const static int count = 3;


	void Option_Change(vector<GameObjects::ObjectInst>& vOBJ_INST) {
		// Scale Value
		f32 scaling = 1920.0f / static_cast<f32>(AEGetWindowWidth());

		//Set Object to ObjectInstance
		for (size_t i{ 0 }; i < vOBJ_INST.size(); i++) {
			for (int j{ 0 }; j < count * 3; j++)
				vOBJ_INST[i].transform.m[j / count][j % count] /= scaling;
		}
		
	}// END Init_Object_From_Vector



	void Init_Player(GameObjects::ObjectInst* OBJ_INST, GameObjects::Character* sCHARACTER, GameObjects::Character& p_player) {
		
		p_player.pObjInst			=			OBJ_INST;							// Set Player ObjectInstance
		p_player.dir				=			(*sCHARACTER).dir;					// Set Player Direction
		p_player.input				=			(*sCHARACTER).input;				// Set Player Input
		p_player.zVel				=			(*sCHARACTER).zVel;					// Set Player z velocity
		p_player.spriteIteration	=			(*sCHARACTER).spriteIteration;		// Set Player Sprite Iteration

		delete sCHARACTER;															// Delete Struct

	}// END Init_Player



}// END namespace Level_Initializer
