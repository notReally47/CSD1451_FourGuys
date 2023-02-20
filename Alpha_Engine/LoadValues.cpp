//FILE TO BE DELETED



#include <string>           // For std::string
#include <sstream>			// For std::stringstream
#include <iomanip>			
#include <fstream>          // For std::istream/std::ostream
#include <vector>           // For std::vector
#include <iostream>
#include "pch.h"
#include "LoadValues.h"		// For struct ValueFromFile
#include "yaml-cpp/yaml.h"	// For Parsing YAML Files


namespace Load_Values {

	using namespace std;

	void Set_Object_Type(vector<Load_Values::ValueFromFile>& vff, string& object_type, int& object_count, int& count, ofstream& data_file);
	void Print_To_Data_File(vector<Load_Values::ValueFromFile>& vff, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);
	//void Zip_Protect_File(const string data_file, const string level_number);

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
			exit(1);
		}
		return vector_vff;
	}// END load_vector_from_file



	vector<ValueFromFile> Load_Values_From_YAML(const string level_number) {
		
		// Strings for Filtering through the YAML file
		string find_object = "Object", 
			object_types = "Player Wall Floor Decoration Portrait Landscape Platform", 
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from
		ifstream file_name("../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Data.yml");
		string data_file_name = "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Data.yml";
		//Zip_Protect_File(data_file_name, level_number);
		// Vector to load data into
		vector<ValueFromFile> vector_vff;
		ValueFromFile* vff = new ValueFromFile;

		// Parse YAML File
		YAML::Parser parser(file_name);
		YAML::Node yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string key;
			i.first() >> key;
			long type{ 0 };

			// If key is 'Object'
			if (key == find_object) {

				// Iterate through 'Object' List
				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
					j.first() >> object_type;								// Get Object Type String

					// If  Object is matches list of existing object (e.g. 'Wall', 'Floor', 'SPortrait', etc.)
					if (object_types.find(object_type) != string::npos) {

						// Iterate through specific 'Object' List
						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
							k.first() >> object_type_number;				// Get the Number of the Object	String

							// If Numbered Object is part of Object (e.g. 'Wall_00' is under 'Wall')
							if (object_type_number.find(object_type) != string::npos) {

								// Iterate through Numbered Object
								for (YAML::Iterator l = k.second().begin(); l != k.second().end(); l++) {
									l.first() >> object_data_type;			// Get the Data Type String

									// If Node is "Type"
									if (object_data_type == "Type") {
										l.second() >> type;
										vff->type = static_cast<unsigned long>(type);
									}

									// If Node is "Mesh"
									if (object_data_type == "Mesh") {
										l.second()["uv_01"] >> vff->uv_01;
										l.second()["uv_02"] >> vff->uv_02;
										l.second()["uv_03"] >> vff->uv_03;
										l.second()["uv_04"] >> vff->uv_04;
										l.second()["uv_05"] >> vff->uv_05;
									}

									// If Node is "Texture_Offset"
									if (object_data_type == "Texture_Offset") {
										l.second()["x_offset"] >> vff->texture_offset_x;
										l.second()["y_offset"] >> vff->texture_offset_y;
									}

									// If Node is "Transformation"
									if (object_data_type == "Transformation") {
										l.second()["transformation_01"] >> vff->transform_01;
										l.second()["transformation_02"] >> vff->transform_02;
										l.second()["transformation_03"] >> vff->transform_03;
										l.second()["transformation_04"] >> vff->transform_04;
									}
								}

								// Print to console for debugging purposes
								//cout << object_type << ' ' << object_type_number << ' ' << "Type: " << vff->type << ' ' 
									//<< "Mesh: " << vff->uv_01 << ' ' << vff->uv_02 << ' ' << vff->uv_03 << ' ' << vff->uv_04 << ' ' << vff->uv_05 << ' ' 
									//<< "Offset: " << vff->texture_offset_x << ' ' << vff->texture_offset_y << ' ' 
									//<< "Transform: " << vff->transform_01 << ' ' << vff->transform_02 << ' ' << vff->transform_03 << ' ' << vff->transform_04 << endl;

								// Push into Vector
								vector_vff.push_back(*vff);
							}
						}
					}
				}
			}
		}
		return vector_vff;
	}// END  read_yaml



	void Extract_Data_Out(vector<Load_Values::ValueFromFile>& vff, const string level_number) {
		
		// File Name to extract to based on level_number
		string out_file = "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Data_No_UV.yml", object_type{ 0 };

		// Converting int to string to count objects
		stringstream object_type_number;

		// Out file to extract data to
		ofstream data_file(out_file);
		
		// To check object type
		int type{ 0 }, previous_type{ -1 };

		// If Out file successfully opened
		if (data_file.is_open()) {
			data_file << "Level: " + level_number << endl;										// First Line is Level Number
			data_file << "Object:" << endl;														// Second Line is 'Object:'

			// Iterate through Data Vector
			for (int i{ 0 }, object_count{ 0 }; i < vff.size(); i++, object_count++) {
				type = vff[i].type;																// Set Type Enum for Object Type
				
				// If Object Type changes, Prints different object as Header for list
				if (type != previous_type)
					Set_Object_Type(vff, object_type, object_count, i, data_file);

				// Adding '0' to front of object count if less than 10
				if (object_count < 10)
					object_type_number << '0' << object_count;
				else
					object_type_number << object_count;

				Print_To_Data_File(vff, object_type, object_type_number, i, data_file);			// Print data of object to file

				previous_type = type;
			}
			data_file.close();																	// Close File
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// If Out File can't be opened
			exit(1);																			// Exit Program
		}
	}// END extract_data



	void Set_Object_Type(vector<Load_Values::ValueFromFile>& vff, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;											// Reset Object Count
		if (vff[index].type == 0) {
			object_type = "Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 1) {
			object_type = "Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 2) {
			object_type = "Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 3) {
			object_type = "Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 4) {
			object_type = "Portrait";								// Set to SPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 5) {
			object_type = "Landscape";								// Set to SPortrait2
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vff[index].type == 6) {
			object_type = "Platform";								// Set to MPortrait
			data_file << "  " << object_type << ":" << endl;
		}
	}// END set_object_type



	void Print_To_Data_File(vector<Load_Values::ValueFromFile>& vff, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {
		// Print data of object to file
		data_file << "    " << object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      " << "Type: " << vff[index].type << endl;
		//data_file << "      " << "Mesh:" << endl;
		//data_file << "        " << "uv_01: " << vff[index].uv_01 << endl;
		//data_file << "        " << "uv_02: " << vff[index].uv_02 << endl;
		//data_file << "        " << "uv_03: " << vff[index].uv_03 << endl;
		//data_file << "        " << "uv_04: " << vff[index].uv_04 << endl;
		//data_file << "        " << "uv_05: " << vff[index].uv_05 << endl;
		data_file << "      " << "Texture_Offset:" << endl;
		data_file << "        " << "x_offset: " << vff[index].texture_offset_x << endl;
		data_file << "        " << "y_offset: " << vff[index].texture_offset_y << endl;
		data_file << "      " << "Transformation:" << endl;
		data_file << "        " << "transformation_01: " << vff[index].transform_01 << endl;
		data_file << "        " << "transformation_02: " << 0 << endl;
		data_file << "        " << "transformation_03: " << vff[index].transform_02 << endl;
		data_file << "        " << "transformation_04: " << 0 << endl;
		data_file << "        " << "transformation_05: " << vff[index].transform_03 << endl;
		data_file << "        " << "transformation_06: " << vff[index].transform_04 << endl;
		data_file << "        " << "transformation_07: " << 0 << endl;
		data_file << "        " << "transformation_08: " << 0 << endl;
		data_file << "        " << "transformation_09: " << 0.5 << endl << endl;
	}// END print_to_data_file



}// END namespace Load_Values