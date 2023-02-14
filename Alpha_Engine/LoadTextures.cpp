//FILE TO BE DELETED



#include <string>           // For std::string
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector
#include <iostream>
#include "pch.h"
#include "LoadTextures.h"	// For struct TextureFromFile


namespace Load_Texture {

	using namespace std;
	int portraits{ 0 };

	vector<TextureFromFile> Load_Texture_From_File(const string level_number) {
		string data_line{ 0 }, file_name{ 0 };
		file_name = "../Assets/Data_Files/Level_" + level_number + "/Load_Level_" + level_number + "_Texture.txt";
		ifstream data_file(file_name);
		vector<TextureFromFile> vector_tff;
		TextureFromFile* tff = new TextureFromFile;
		if (data_file.is_open()) {
			while (!(data_file.eof())) {
				data_file >> tff->type, data_file >> data_line;
				tff->texture_file = data_line;
				vector_tff.push_back(*tff);
			}
			data_file.close();
		}
		else {
			cout << "Error Opening File: " << file_name << endl;
			exit(1);
		}
		return vector_tff;
	}// END load_texture_from_file


	void Load_Texture_To_Object(vector<TextureFromFile>& tff, GameObjects::Object& obj) {
		for (size_t i{ 0 }; i < tff.size(); i++) {
			const size_t length = (tff[i].texture_file).length();
			char* char_texture_file = new char[length + 1];
			strcpy_s(char_texture_file, length + 1, (tff[i].texture_file).c_str());
			s8* texture_file = char_texture_file;
			if (obj.type == tff[i].type) {
				AE_ASSERT_MESG(obj.pTex = AEGfxTextureLoad(texture_file), "Failed to load texture");
				break;
			}
		}
	}// END load_texture_to_object


}// END namespace Load_Texture
