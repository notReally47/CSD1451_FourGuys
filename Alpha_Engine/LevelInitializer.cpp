#include <vector>				// For std::vector	
#include "DataFiles.h"			// For Load_Data_From_File:: & GameObjects::

namespace Level_Initializer {
	using namespace std;


	void Init_Object(vector<Load_Data_From_File::ObjectTransform>& vOT, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size) {
		
		// Loop Through ObjectInstances
		// Scale
		f32 s = 1920.0f / static_cast<f32>(AEGetWindowWidth());

		for (size_t i{ 0 }; i < object_instance_size; i++) {

			//Set Object to OnjectInstance
			if (vOT[i].OS.type == Enum::TYPE::PLAYER)
				object_instance[i].pObj = object[Enum::TYPE::PLAYER];
			else if (vOT[i].OS.type == Enum::TYPE::WALL)
				object_instance[i].pObj = object[Enum::TYPE::WALL];
			else if (vOT[i].OS.type == Enum::TYPE::FLOOR)
				object_instance[i].pObj = object[Enum::TYPE::FLOOR];
			else if (vOT[i].OS.type == Enum::TYPE::DECO)
				object_instance[i].pObj = object[Enum::TYPE::DECO];
			else if (vOT[i].OS.type == Enum::TYPE::PORTRAIT)
				object_instance[i].pObj = object[Enum::TYPE::PORTRAIT];
			else if (vOT[i].OS.type == Enum::TYPE::LANDSCAPE)
				object_instance[i].pObj = object[Enum::TYPE::LANDSCAPE];

			// Set ObjectInstance Flag
			object_instance[i].flag = vOT[i].flag;

			// Set ObjectInstance Texture Offset
			object_instance[i].tex_offset = { vOT[i].texture_offset_x, vOT[i].texture_offset_y };

			// Set ObjectInstance Transformation
			object_instance[i].transform = { vOT[i].scale_x, vOT[i].shear_x, vOT[i].position_x,
											vOT[i].scale_y, vOT[i].shear_y, vOT[i].position_y,
											vOT[i].width, vOT[i].length, vOT[i].height };

		}// END For-Loop

		vOT.clear();						// Clear ObjectTransform Vector

	}// END Init_Object



	void Init_Player(Load_Data_From_File::PlayerProperties* sPP, GameObjects::Character& p_player, GameObjects::Object* object, GameObjects::ObjectInst object_instance) {
		
		p_player.pObjInst = object_instance;					// Set Player ObjectInstance
		p_player.pObjInst.pObj = object;						// Set Player Object to Player ObjectInstance

		p_player.dir = (*sPP).direction;						// Set Player Direction
		p_player.input = (*sPP).input;							// Set Player Input
		p_player.rotation = (*sPP).rotation;					// Set Player Rotation
		p_player.speed = (*sPP).speed;							// Set Player Speed
		p_player.spriteIteration = (*sPP).sprite_iteration;		// Set Player Sprite Iteration

		delete sPP;												// Delete PlayerProperties Struct

	}// END Init_Player



}// END namespace Level_Initializer
