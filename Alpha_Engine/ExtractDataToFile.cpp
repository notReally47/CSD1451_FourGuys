#include <string>					// For std::string
#include <sstream>					// For std::stringstream
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <iostream>					// For std::cout debugging
#include "DataFiles.h"				// For GameObjects::

namespace Extract_Data_To_File {

	using namespace std;

	void Set_Object_Transform_Type	(vector<GameObjects::ObjectInst>& vOBJ_INST, string& object_type, int& object_count, int& index, ofstream& data_file);
	void Print_To_Transform_YAML	(vector<GameObjects::ObjectInst>& vOBJ_INST, GameObjects::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);



	void Extract_Transform_Data_Out(vector<GameObjects::ObjectInst> vOBJ_INST, GameObjects::Character p_player, const string level_number) {

		// file name to extract to based on level_number
		string 
			out_file		{ "./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform_Extracted.yml" },
			object_type		{ 0 };

		// converting int to string to count objects
		stringstream object_type_number;

		// out file to extract data to
		ofstream data_file(out_file);
		if (!data_file.good())
			data_file.open("." + out_file);

		// to check object type
		int 
			type			{ 0 }, 
			previous_type	{ -1 };

		// if out file successfully opened
		if (data_file.is_open()) {
			data_file << "Level: " + level_number << endl;												// first line is level number
			data_file << "Object_Instance:" << endl;														// second line is 'Object_Instance: '

			// iterate through data vector
			for (int i{ 0 }, object_count{ 0 }; i < vOBJ_INST.size(); i++, object_count++) {
				type = vOBJ_INST[i].pObj->type;															// set type enum for object type

				// if object type changes, prints different object as header for list
				if (type != previous_type)
					Set_Object_Transform_Type(vOBJ_INST, object_type, object_count, i, data_file);

				// adding '0' to front of object count if less than 10
				if (object_count < 10)
					object_type_number << '0' << object_count;
				else
					object_type_number << object_count;

				Print_To_Transform_YAML(vOBJ_INST, p_player, object_type, object_type_number, i, data_file);	// print data of object to file

				previous_type = type;
			}
			data_file.close();																	// close file
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// if out file can't be opened
			exit(1);																			// exit program
		}
	}// END extract_transform_data_out



	void Set_Object_Transform_Type(vector<GameObjects::ObjectInst>& vOBJ_INST, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;												// Reset Object Count
		if (vOBJ_INST[index].pObj->type == Enum::TYPE::PLAYER) {
			object_type = "00_Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::FLOOR) {
			object_type = "01_Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::WALL) {
			object_type = "02_Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::DECO) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::PORTRAIT) {
			object_type = "04_Portrait";								// Set to Portrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::LANDSCAPE) {
			object_type = "05_Landscape";								// Set to Landscape
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOBJ_INST[index].pObj->type == Enum::TYPE::PLATFORM) {
			object_type = "06_Platform";								// Set to Platform
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type



	void Print_To_Transform_YAML(vector<GameObjects::ObjectInst>& vOBJ_INST, GameObjects::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {
		
		// Print data of object to file
		data_file << "    "	<< object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      "			<< "Type: "					<< vOBJ_INST[index].pObj->type				<< endl;
		data_file << "      "			<< "Flag: "					<< vOBJ_INST[index].flag					<< endl;
		data_file << "      "			<< "Texture_Offset:"													<< endl;
		data_file << "        "			<< "x_offset: "				<< vOBJ_INST[index].tex_offset.x			<< endl;
		data_file << "        "			<< "y_offset: "				<< vOBJ_INST[index].tex_offset.y			<< endl;
		data_file << "      "			<< "Transformation:"													<< endl;
		data_file << "        "			<< "scale_x: "				<< vOBJ_INST[index].transform.m[0][0]		<< endl;
		data_file << "        "			<< "shear_x: "				<< vOBJ_INST[index].transform.m[0][1]		<< endl;
		data_file << "        "			<< "position_x: "			<< vOBJ_INST[index].transform.m[0][2]		<< endl;
		data_file << "        "			<< "shear_y: "				<< vOBJ_INST[index].transform.m[1][0]		<< endl;
		data_file << "        "			<< "scale_y: "				<< vOBJ_INST[index].transform.m[1][1]		<< endl;
		data_file << "        "			<< "position_y: "			<< vOBJ_INST[index].transform.m[1][2]		<< endl;
		data_file << "        "			<< "elapsed: "				<< vOBJ_INST[index].transform.m[2][0]		<< endl;
		data_file << "        "			<< "empty: "				<< vOBJ_INST[index].transform.m[2][1]		<< endl;
		data_file << "        "			<< "position_z: "			<< vOBJ_INST[index].transform.m[2][2]		<< endl;

		// Player Stats
		if (vOBJ_INST[index].pObj->type == Enum::TYPE::PLAYER) {
			data_file	<< "      "		<< "Direction:"															<< endl;
			data_file	<< "        "	<< "direction_x: "			<< p_player.dir.x							<< endl;
			data_file	<< "        "	<< "direction_y: "			<< p_player.dir.y							<< endl;
			data_file	<< "      "		<< "Input:"																<< endl;
			data_file	<< "        "	<< "input_x: "				<< p_player.input.x							<< endl;
			data_file	<< "        "	<< "input_y: "				<< p_player.input.y							<< endl;
			data_file	<< "      "		<< "Is_Moving: "			<< p_player.isMoving						<< endl;
			data_file	<< "      "		<< "Is_Jumping: "			<< p_player.isJumping						<< endl;
			data_file	<< "      "		<< "Z_Velocity: "			<< p_player.zVel							<< endl;
			data_file	<< "      "		<< "Speed: "				<< p_player.speed							<< endl;
			data_file	<< "      "		<< "Sprite_Iteration: "		<< p_player.spriteIteration					<< endl;
		}

		data_file << endl;

	}// END Print_To_Transform_YAML



}// END namespace Extract_Data_To_File