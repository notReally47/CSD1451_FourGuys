#include <string>					// For std::string
#include <sstream>					// For std::stringstream
#include <iomanip>			
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <iostream>					// For std::cout debugging
#include "pch.h"					// For Precompiled Header Files
#include "LoadDataFromFile.h"		// For structs
#include "yaml-cpp/yaml.h"			// For Parsing YAML Files

namespace Load_Data_From_File {

	using namespace std;

	void Set_Object_Transform_Type(vector<Load_Data_From_File::ObjectTransform>& vff, string& object_type, int& object_count, int& count, ofstream& data_file);
	void Set_Object_Shape_Type(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, int& object_count, int& index, ofstream& data_file);
	void Print_To_Transform_YAML(vector<Load_Data_From_File::ObjectTransform>& vOT, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);
	void Print_To_Shape_YAML(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);

	vector<ObjectShape> Load_Shape_From_YAML(const string level_number) {

		// Strings for Filtering through the YAML file
		string find_object = "Object",
			object_types = "00_Player 01_Wall 02_Floor 03_Decoration 04_SPortrait 05_SPortrait2 06_MPortrait 07_LPortrait 08_Platform 09_Highlight",
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from
		ifstream file_name("../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Shape.yml");

		// Vector to load data into
		vector<ObjectShape> vector_os;
		ObjectShape* OS = new ObjectShape;

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

						// Iterate through Specific Object
						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
							k.first() >> object_data_type;			// Get the Data Type String

							// If Node is "Type"
							if (object_data_type == "Type") {
								k.second() >> type;
								OS->type = static_cast<unsigned long>(type);
							}

							// If Node is "Mesh"
							if (object_data_type == "Mesh") {
								k.second()["uv_01"] >> OS->uv_01;
								k.second()["uv_02"] >> OS->uv_02;
								k.second()["uv_03"] >> OS->uv_03;
								k.second()["uv_04"] >> OS->uv_04;
								k.second()["uv_05"] >> OS->uv_05;
								k.second()["uv_06"] >> OS->uv_06;
							}

							// If Node is "Texture_Offset"
							if (object_data_type == "Texture") {
								k.second() >> OS->texture_file;
							}

						}

						// Print to console for debugging purposes
						cout << object_type << ' ' << OS->type << ' '
							<< "Mesh: " << OS->uv_01 << ' ' << OS->uv_02 << ' ' << OS->uv_03 << ' ' << OS->uv_04 << ' ' << OS->uv_05 << ' ' << OS->uv_06 << ' '
							<< "Texture: " << OS->texture_file << endl;

						// Push into Vector
						vector_os.push_back(*OS);
					}
				}
			}
		}
		return vector_os;
	}// END LoadShapeFromYAML



	vector<ObjectTransform> Load_Transform_From_YAML(const string level_number, vector<ObjectShape> vector_OS) {

		// Strings for Filtering through the YAML file
		string find_object = "Object",
			object_types = "00_Player 01_Wall 02_Floor 03_Decoration 04_SPortrait 05_SPortrait2 06_MPortrait 07_LPortrait 08_Platform 09_Highlight",
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from
		ifstream file_name("../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml");

		// Vector to load data into
		vector<ObjectTransform> vector_ot;
		ObjectTransform* OT = new ObjectTransform;

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
					cout << object_type << endl;
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
										for (int m{ 0 }; m < vector_OS.size(); m++)
											if (vector_OS[m].type == type)
												OT->OS = vector_OS[m];
									}

									// If Node is "Texture_Offset"
									if (object_data_type == "Texture_Offset") {
										l.second()["x_offset"] >> OT->texture_offset_x;
										l.second()["y_offset"] >> OT->texture_offset_y;
									}

									// If Node is "Transformation"
									if (object_data_type == "Transformation") {
										l.second()["transformation_01"] >> OT->transformation_01;
										l.second()["transformation_02"] >> OT->transformation_02;
										l.second()["transformation_03"] >> OT->transformation_03;
										l.second()["transformation_04"] >> OT->transformation_04;
										l.second()["transformation_05"] >> OT->transformation_05;
										l.second()["transformation_06"] >> OT->transformation_06;
										l.second()["transformation_07"] >> OT->transformation_07;
										l.second()["transformation_08"] >> OT->transformation_08;
										l.second()["transformation_09"] >> OT->transformation_09;
									}
								}

								// Print to console for debugging purposes
								cout << object_type << ' ' << object_type_number << ' ' << "Type: " << OT->OS.type << ' '
									<< "Mesh: " << OT->OS.uv_01 << ' ' << OT->OS.uv_02 <<  ' ' << OT->OS.uv_03 << ' ' << OT->OS.uv_04 << ' ' << OT->OS.uv_05 << ' ' << OT->OS.uv_06 << ' '
									<< "Offset: " << OT->texture_offset_x << ' ' << OT->texture_offset_y << ' '
									<< "Transform: " << OT->transformation_01 << ' ' << OT->transformation_02 << ' ' << OT->transformation_03 << ' ' << OT->transformation_04 << ' '
									<< OT->transformation_05 << ' ' << OT->transformation_06 << ' ' << OT->transformation_07 << ' ' << OT->transformation_08 << ' ' << OT->transformation_09 << ' '
									<< "Texture: " << OT->OS.texture_file  << endl;

								// Push into Vector
								vector_ot.push_back(*OT);
							}
						}
					}
				}
			}
		}
		return vector_ot;
	}// END LoadTransformFromYAML



	void Load_Texture_To_Object(vector<ObjectShape>& vOS, GameObjects::Object& obj) {
		for (size_t i{ 0 }; i < vOS.size(); i++) {
			const size_t length = (vOS[i].texture_file).length();
			char* char_texture_file = new char[length + 1];
			strcpy_s(char_texture_file, length + 1, (vOS[i].texture_file).c_str());
			s8* texture_file = char_texture_file;
			cout << texture_file << endl;
			if (obj.type == vOS[i].type) {
				AE_ASSERT_MESG(obj.pTex = AEGfxTextureLoad(texture_file), "Failed to load texture");
				break;
			}
		}
	}// END LoadTextureToObject



	void Extract_Transform_Data_Out(vector<Load_Data_From_File::ObjectTransform>& vOT, const string level_number) {

		// File Name to extract to based on level_number
		string out_file = "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform_Extracted.yml", object_type{ 0 };

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
			for (int i{ 0 }, object_count{ 0 }; i < vOT.size(); i++, object_count++) {
				type = vOT[i].OS.type;															// Set Type Enum for Object Type

				// If Object Type changes, Prints different object as Header for list
				if (type != previous_type)
					Set_Object_Transform_Type(vOT, object_type, object_count, i, data_file);

				// Adding '0' to front of object count if less than 10
				if (object_count < 10)
					object_type_number << '0' << object_count;
				else
					object_type_number << object_count;

				Print_To_Transform_YAML(vOT, object_type, object_type_number, i, data_file);	// Print data of object to file

				previous_type = type;
			}
			data_file.close();																	// Close File
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// If Out File can't be opened
			exit(1);																			// Exit Program
		}
	}// END Extract_Transform_Data_Out



	void Extract_Shape_Data_Out(vector<Load_Data_From_File::ObjectShape>& vOS, const string level_number) {

		// File Name to extract to based on level_number
		string out_file = "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Shape_Extracted.yml", object_type{ 0 };

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
			for (int i{ 0 }, object_count{ 0 }; i < vOS.size(); i++, object_count++) {
				type = vOS[i].type;															// Set Type Enum for Object Type

				// If Object Type changes, Prints different object as Header for list
				if (type != previous_type)
					Set_Object_Shape_Type(vOS, object_type, object_count, i, data_file);

				// Adding '0' to front of object count if less than 10
				if (object_count < 10)
					object_type_number << '0' << object_count;
				else
					object_type_number << object_count;

				Print_To_Shape_YAML(vOS, object_type, object_type_number, i, data_file);		// Print data of object to file

				previous_type = type;
			}
			data_file.close();																	// Close File
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// If Out File can't be opened
			exit(1);																			// Exit Program
		}
	}// END Extract_Shape_Data_Out



	void Set_Object_Transform_Type(vector<Load_Data_From_File::ObjectTransform>& vOT, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;											// Reset Object Count
		if (vOT[index].OS.type == 0) {
			object_type = "00_Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 1) {
			object_type = "01_Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 2) {
			object_type = "02_Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 3) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 4) {
			object_type = "04_SPortrait";								// Set to SPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 5) {
			object_type = "05_SPortrait2";								// Set to SPortrait2
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 6) {
			object_type = "06_MPortrait";								// Set to MPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 7) {
			object_type = "07_LPortrait";								// Set to LPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 8) {
			object_type = "08_Platform";								// Set to Platform
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 9) {
			object_type = "09_Highlight";								// Set to Highlight
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type



	void Set_Object_Shape_Type(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;											// Reset Object Count
		if (vOS[index].type == 0) {
			object_type = "00_Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 1) {
			object_type = "01_Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 2) {
			object_type = "02_Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 3) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 4) {
			object_type = "04_SPortrait";								// Set to SPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 5) {
			object_type = "05_SPortrait2";								// Set to SPortrait2
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 6) {
			object_type = "06_MPortrait";								// Set to MPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 7) {
			object_type = "07_LPortrait";								// Set to LPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 8) {
			object_type = "08_Platform";								// Set to Platform
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 9) {
			object_type = "09_Highlight";								// Set to Highlight
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type



	void Print_To_Transform_YAML(vector<Load_Data_From_File::ObjectTransform>& vOT, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {
		// Print data of object to file
		data_file << "    " << object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      " << "Type: " << vOT[index].OS.type << endl;
		data_file << "      " << "Texture_Offset:" << endl;
		data_file << "        " << "x_offset: " << vOT[index].texture_offset_x << endl;
		data_file << "        " << "y_offset: " << vOT[index].texture_offset_y << endl;
		data_file << "      " << "Transformation:" << endl;
		data_file << "        " << "transformation_01: " << vOT[index].transformation_01 << endl;
		data_file << "        " << "transformation_02: " << vOT[index].transformation_02 << endl;
		data_file << "        " << "transformation_03: " << vOT[index].transformation_03 << endl;
		data_file << "        " << "transformation_04: " << vOT[index].transformation_04 << endl;
		data_file << "        " << "transformation_05: " << vOT[index].transformation_05 << endl;
		data_file << "        " << "transformation_06: " << vOT[index].transformation_06 << endl;
		data_file << "        " << "transformation_07: " << vOT[index].transformation_07 << endl;
		data_file << "        " << "transformation_08: " << vOT[index].transformation_08 << endl;
		data_file << "        " << "transformation_09: " << vOT[index].transformation_09 << endl << endl;
	}// END Print_To_Transform_YAML



	void Print_To_Shape_YAML(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {
		// Print data of object to file
		object_type_number.str(string());
		data_file << "    " << "Type: " << vOS[index].type << endl;
		data_file << "    " << "Mesh:" << endl;
		data_file << "      " << "uv_01: " << vOS[index].uv_01 << endl;
		data_file << "      " << "uv_02: " << vOS[index].uv_02 << endl;
		data_file << "      " << "uv_03: " << vOS[index].uv_03 << endl;
		data_file << "      " << "uv_04: " << vOS[index].uv_04 << endl;
		data_file << "      " << "uv_05: " << vOS[index].uv_05 << endl;
		data_file << "      " << "uv_06: " << vOS[index].uv_06 << endl;
		data_file << "    " << "Texture: " << "\"" << vOS[index].texture_file << "\"" << endl << endl;
	}// END Print_To_Shape_YAML



}// End namespace Load_Data_From_File