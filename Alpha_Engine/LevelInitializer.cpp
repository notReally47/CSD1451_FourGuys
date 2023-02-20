#include<iostream>
#include <vector>				// For std::vector	
#include "pch.h"	
#include "LoadValues.h"			// For Load_Values::
#include "LoadDataFromFile.h"	// For Load_Data_From_File::

namespace Level_Initializer {
	using namespace std;


	void Init_Object(vector<Load_Data_From_File::ObjectTransform>& vOT, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size) {
		// Scale
		f32 s = 1920.0f / static_cast<f32>(AEGetWindowWidth());

		for (size_t i{ 0 }; i < object_instance_size; i++) {
			if (vOT[i].OS.type == Enum::TYPE::PLAYER) {
				object_instance[i].pObj = object[Enum::TYPE::PLAYER];
			}
			else if (vOT[i].OS.type == Enum::TYPE::WALL) {
				object_instance[i].pObj = object[Enum::TYPE::WALL];
			}
			else if (vOT[i].OS.type == Enum::TYPE::FLOOR) {
				object_instance[i].pObj = object[Enum::TYPE::FLOOR];
			}
			else if (vOT[i].OS.type == Enum::TYPE::DECO) {
				object_instance[i].pObj = object[Enum::TYPE::DECO];
			}
			else if (vOT[i].OS.type == Enum::TYPE::PORTRAIT) {
				object_instance[i].pObj = object[Enum::TYPE::PORTRAIT];
			}
			else if (vOT[i].OS.type == Enum::TYPE::LANDSCAPE) {
				object_instance[i].pObj = object[Enum::TYPE::LANDSCAPE];
			}
			else if (vOT[i].OS.type == Enum::TYPE::PLATFORM) {
				object_instance[i].pObj = object[Enum::TYPE::PLATFORM];
			}
			object_instance[i].flag = GameObjects::FLAG_INACTIVE;
			object_instance[i].tex_offset = { vOT[i].texture_offset_x, vOT[i].texture_offset_y };
			object_instance[i].transform = { vOT[i].transformation_01 * s, vOT[i].transformation_02 * s, vOT[i].transformation_03 * s,
											vOT[i].transformation_04 * s, vOT[i].transformation_05 * s, vOT[i].transformation_06 * s,
											vOT[i].transformation_07 * s, vOT[i].transformation_08 * s, vOT[i].transformation_09 * s };
		}
		vOT.clear();
	}// END Init_Object



}// END namespace Level_Initializer
