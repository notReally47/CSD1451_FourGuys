#pragma once
#include <string>           // For std::string
#include <vector>           // For std::vector
#include "DataFiles.h"		// For Precompiled Header Files

namespace Load_Data_From_File{

	using namespace std;



	struct ObjectShape {
		unsigned long type;
		f32 uv_01, uv_02, uv_03,
			uv_04, uv_05, uv_06;
		string texture_file;
	};



	struct ObjectTransform {
		ObjectShape OS;
		unsigned char flag;
		f32 texture_offset_x, texture_offset_y;
		f32 scale_x, shear_x, position_x,
			shear_y, scale_y, position_y,
			width, length, height;
		f32 elapsed;
		f32 z_axis;
	};



	struct PlayerProperties {
		AEVec2 direction, input;
		f32 rotation, speed;
		int sprite_iteration;
	};



	vector<ObjectShape> Load_Shape_From_YAML(const string level_number);
	vector<ObjectTransform> Load_Transform_From_YAML(const string level_number, vector<ObjectShape> vector_OS);
	PlayerProperties* Load_Player_Stats_From_YAML(const string level_number);
	void Load_Shape_To_Object(vector<ObjectShape>& vOS, GameObjects::Object* objs[]);



}// END namespace Load_Data_From_File