#pragma once
#include "pch.h"
#include <string>           // For std::string
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector


namespace Load_Texture {
	using namespace std;
	struct TextureFromFile {
		unsigned long type;
		string texture_file;
	};

	vector<TextureFromFile> Load_Texture_From_File(const string level_number);
	void Load_Texture_To_Object(std::vector<TextureFromFile>& tff, GameObjects::Object& obj);
}// END namespace Load_Texture
