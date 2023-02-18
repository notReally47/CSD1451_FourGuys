#include<iostream>
#include <vector>				// For std::vector	
#include "pch.h"	
#include "LoadValues.h"			// For Load_Values::
#include "LoadDataFromFile.h"	// For Load_Data_From_File::

namespace Level_Initializer {
	using namespace std;


	void Init_Object(vector<Load_Data_From_File::ObjectTransform>& vOT, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size) {
		for (size_t i{ 0 }; i < object_instance_size; i++) {
			if (vOT[i].OS.type == Enum::TYPE::PLAYER) {
				object_instance[i].pObj = object[0];
			}
			else if (vOT[i].OS.type == Enum::TYPE::WALL) {
				object_instance[i].pObj = object[1];
			}
			else if (vOT[i].OS.type == Enum::TYPE::FLOOR) {
				object_instance[i].pObj = object[2];
			}
			else if (vOT[i].OS.type == Enum::TYPE::DECO) {
				object_instance[i].pObj = object[3];
			}
			else if (vOT[i].OS.type == Enum::TYPE::PORTRAIT) {
				object_instance[i].pObj = object[4];
			}
			else if (vOT[i].OS.type == Enum::TYPE::LANDSCAPE) {
				object_instance[i].pObj = object[5];
			}
			object_instance[i].flag = GameObjects::FLAG_INACTIVE;
			object_instance[i].tex_offset = { vOT[i].texture_offset_x, vOT[i].texture_offset_y };
			object_instance[i].transform = { vOT[i].transformation_01, vOT[i].transformation_02, vOT[i].transformation_03,
											vOT[i].transformation_04, vOT[i].transformation_05, vOT[i].transformation_06,
											vOT[i].transformation_07, vOT[i].transformation_08, vOT[i].transformation_09 };
		}
		vOT.clear();
	}// END Init_Object



}// END namespace Level_Initializer
