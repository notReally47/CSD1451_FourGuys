#pragma once
#include "pch.h"			// For Precompiled Header Files
#include <string>           // For std::string
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector

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
		f32 texture_offset_x, texture_offset_y;
		f32 transformation_01, transformation_02, transformation_03,
			transformation_04, transformation_05, transformation_06,
			transformation_07, transformation_08, transformation_09;
	};



	vector<ObjectShape> Load_Shape_From_YAML(const string level_number);
	vector<ObjectTransform> Load_Transform_From_YAML(const string level_number, vector<ObjectShape> vector_OS);
	void Load_Shape_To_Object(vector<ObjectShape>& vOS, GameObjects::Object* objs[]);
	void Extract_Transform_Data_Out(vector<Load_Data_From_File::ObjectTransform>& vOT, const string level_number);
	void Extract_Shape_Data_Out(vector<Load_Data_From_File::ObjectShape>& vOS, const string level_number);



}// END namespace Load_Data_From_File