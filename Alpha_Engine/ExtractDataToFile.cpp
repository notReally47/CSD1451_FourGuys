#include <string>					// For std::string
#include <sstream>					// For std::stringstream
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <iostream>					// For std::cout debugging
#include "DataFiles.h"				// For ObjectTransform, ObjectShape & PlayerProperties

namespace Extract_Data_To_File {

	using namespace std;

	void Set_Object_Transform_Type(vector<Load_Data_From_File::ObjectTransform>& vff, string& object_type, int& object_count, int& count, ofstream& data_file);
	void Set_Object_Shape_Type(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, int& object_count, int& index, ofstream& data_file);
	void Print_To_Transform_YAML(vector<Load_Data_From_File::ObjectTransform>& vOT, Load_Data_From_File::PlayerProperties sPP, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);
	void Print_To_Shape_YAML(vector<Load_Data_From_File::ObjectShape>& vOS, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);



	void Extract_Transform_Data_Out(vector<Load_Data_From_File::ObjectTransform>& vOT, Load_Data_From_File::PlayerProperties sPP, const string level_number) {

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
			data_file << "ObjectInstance:" << endl;														// Second Line is 'Object:'

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

				Print_To_Transform_YAML(vOT, sPP, object_type, object_type_number, i, data_file);	// Print data of object to file

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
			object_type = "01_Floor";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 2) {
			object_type = "02_Wall";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 3) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 4) {
			object_type = "04_Portrait";								// Set to SPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 5) {
			object_type = "05_Landscape";								// Set to SPortrait2
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOT[index].OS.type == 6) {
			object_type = "06_Platform";								// Set to MPortrait
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
			object_type = "01_Floor";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 2) {
			object_type = "02_Wall";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 3) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 4) {
			object_type = "04_Portrait";								// Set to SPortrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 5) {
			object_type = "05_Landscape";								// Set to SPortrait2
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOS[index].type == 6) {
			object_type = "06_Platform";								// Set to MPortrait
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type



	void Print_To_Transform_YAML(vector<Load_Data_From_File::ObjectTransform>& vOT, Load_Data_From_File::PlayerProperties sPP, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {
		// Print data of object to file
		data_file << "    " << object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      " << "Type: " << vOT[index].OS.type << endl;
		data_file << "      " << "Flag: " << 0x0 << endl;
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
		data_file << "        " << "transformation_09: " << vOT[index].transformation_09 << endl;
		if (vOT[index].OS.type == Enum::TYPE::PLAYER) {
			data_file << "      " << "Direction:" << endl;
			data_file << "        " << "direction_x: " << sPP.direction.x << endl;
			data_file << "        " << "direction_y: " << sPP.direction.y << endl;
			data_file << "      " << "Input:" << endl;
			data_file << "        " << "input_x: " << sPP.input.x << endl;
			data_file << "        " << "input_y: " << sPP.input.y << endl;
			data_file << "      " << "Rotation: " << sPP.rotation << endl;
			data_file << "      " << "Speed: " << sPP.speed << endl;
			data_file << "      " << "Sprite_Iteration: " << sPP.sprite_iteration << endl;
		}
		data_file << endl;
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



}// END namespace Extract_Data_To_File