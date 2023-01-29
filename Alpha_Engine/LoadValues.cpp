#include <string>           // For std::string
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector
#include <iostream>
#include "pch.h"
#include "LoadValues.h"		// For struct ValueFromfile

namespace Load_Values {

	using namespace std;

	vector<ValueFromFile> Load_Values_From_File(const string level_number) {
		string data_line{ 0 }, file_name{ 0 };
		file_name = "../Assets/Data_Files/Level_" + level_number + "/Load_Level_" + level_number + "_Data.txt";
		ifstream data_file(file_name);
		vector<ValueFromFile> vector_vff;
		ValueFromFile* vff = new ValueFromFile;
		if (data_file.is_open()) {
			while (!(data_file.eof())) {
				data_file >> vff->type,
					data_file >> vff->uv_01, data_file >> vff->uv_02, data_file >> vff->uv_03, data_file >> vff->uv_04, data_file >> vff->uv_05,
					data_file >> vff->texture_offset_x, data_file >> vff->texture_offset_y,
					data_file >> vff->transform_01, data_file >> vff->transform_02, data_file >> vff->transform_03, data_file >> vff->transform_04;
				vector_vff.push_back(*vff);
			}
			data_file.close();
		}
		else {
			cout << "Error Opening File: " << file_name << endl;
			exit;
		}
		return vector_vff;
	}// END load_vector_from_file


}// END namespace Load_Values
