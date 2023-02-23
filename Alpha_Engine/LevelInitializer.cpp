#include <vector>				// For std::vector	
#include "DataFiles.h"			// For GameObjects::

namespace Level_Initializer {
	using namespace std;



	void Init_Object_From_Vector(vector<GameObjects::ObjectInst> vOBJ_INST, GameObjects::ObjectInst object_instance[], size_t object_instance_size) {
		//Set Object to ObjectInstance
		for (size_t i{ 0 }; i < object_instance_size; i++)
			object_instance[i] = vOBJ_INST[i];
	}// END Init_Object_From_Vector



	void Init_Player(GameObjects::ObjectInst* OBJ_INST, GameObjects::Character* sCHARACTER, GameObjects::Character& p_player) {
		
		p_player.pObjInst			=			OBJ_INST;					// Set Player ObjectInstance
		p_player.dir				=			(*sCHARACTER).dir;					// Set Player Direction
		p_player.input				=			(*sCHARACTER).input;				// Set Player Input
		p_player.speed				=			(*sCHARACTER).speed;				// Set Player Speed
		p_player.isMoving			=			(*sCHARACTER).isMoving;				// Set Player bool isMoving
		p_player.isJumping			=			(*sCHARACTER).isJumping;			// Set Player bool isJumping
		p_player.zVel				=			(*sCHARACTER).zVel;					// Set Player z velocity
		p_player.spriteIteration	=			(*sCHARACTER).spriteIteration;		// Set Player Sprite Iteration

		delete sCHARACTER;															// Delete Struct

	}// END Init_Player



}// END namespace Level_Initializer
