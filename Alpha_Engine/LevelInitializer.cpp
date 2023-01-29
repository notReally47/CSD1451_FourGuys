#include<iostream>
#include <vector>			// For std::vector	
#include "pch.h"	
#include "LoadValues.h"		// For Load_Values::

namespace Level_Initializer {
	using namespace std;

	void Init_Mesh_From_File(vector<Load_Values::ValueFromFile>& vff, GameObjects::Object& object) {
		for (size_t i{ 0 }; i < vff.size(); i++) {
			if (object.type == vff[i].type) {
				AEGfxMeshStart();
				AEGfxTriAdd(
					-1.0f, -1.0f, 0xFFFF0000, vff[i].uv_01, vff[i].uv_02,
					1.0f, -1.0f, 0xFFFF0000, vff[i].uv_03, vff[i].uv_04,
					-1.0f, 1.0f, 0xFFFF0000, .0f, vff[i].uv_05
				);
				AEGfxTriAdd(
					1.0f, 1.0f, 0xFFFF0000, vff[i].uv_03, vff[i].uv_05,
					1.0f, -1.0f, 0xFFFF0000, vff[i].uv_03, vff[i].uv_04,
					-1.0f, 1.0f, 0xFFFF0000, .0f, vff[i].uv_05
				);
				object.pMesh = AEGfxMeshEnd();
			}
		}
	}// END Init_Mesh_From_File

	void Init_Object_Instance(vector<Load_Values::ValueFromFile>& vff, GameObjects::Object* object[], GameObjects::ObjectInst object_instance[], size_t object_instance_size) {
		for (size_t i{ 0 }; i < object_instance_size; i++) {
			if (vff[i].type == Enum::TYPE::WALL) {
				object_instance[i].pObj = object[0];
			}
			else if (vff[i].type == Enum::TYPE::FLOOR) {
				object_instance[i].pObj = object[1];
			}
			else if (vff[i].type == Enum::TYPE::DECO) {
				object_instance[i].pObj = object[2];
			}
			else if (vff[i].type == Enum::TYPE::PORTRAIT) {
				object_instance[i].pObj = object[3];
			}
			else if (vff[i].type == Enum::TYPE::PORTRAIT2) {
				object_instance[i].pObj = object[4];
			}
			else if (vff[i].type == Enum::TYPE::MPORTRAIT) {
				object_instance[i].pObj = object[5];
			}
			else if (vff[i].type == Enum::TYPE::LPORTRAIT) {
				object_instance[i].pObj = object[6];
			}
			object_instance[i].flag = 0x0;
			object_instance[i].tex_offset = { vff[i].texture_offset_x, vff[i].texture_offset_y };
			object_instance[i].transform = { vff[i].transform_01, .0f, vff[i].transform_02,
											.0f, vff[i].transform_03, vff[i].transform_04,
											.0f, .0f, 1.0f };
		}
	}// END Init_Object_Instance

}// END namespace Level_Initializer
