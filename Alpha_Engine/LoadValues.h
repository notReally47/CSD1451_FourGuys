//FILE TO BE DELETED



#pragma once
#include "pch.h"
#include <string>           // For std::string
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector

namespace Load_Values {
	using namespace std;
	struct ValueFromFile {
		unsigned long type;
		GameObjects::Object object;
		f32 uv_01, uv_02, uv_03, uv_04, uv_05;
		f32 texture_offset_x, texture_offset_y;
		f32 transform_01, transform_02, transform_03, transform_04; //w, x, h, y
	};

	vector<ValueFromFile> Load_Values_From_File(const string level_number);
	vector<ValueFromFile> Load_Values_From_YAML(const string level_number);
	void Extract_Data_Out(vector<Load_Values::ValueFromFile>& vff, const string level_number);
	
}// END namespace Load_Values
