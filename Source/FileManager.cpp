#include "PCH.h"
#include "FileManager.h"
#include <string>					// For std::string
#include <sstream>					// For std::stringstream
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <yaml-cpp/yaml.h>			// For Parsing YAML Files

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace FM
{
	vector<OM::Object>* Import::Load_Shape_From_YAML(const string level_number) {

		// Strings for Filtering through the YAML file
		string
			find_object{ "Object" },
			object_types{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
			object_type{ 0 },
			object_type_number{ 0 },
			object_data_type{ 0 };

		// YAML file to read from
		string file_name{ "./Resource/Data/Level_" + level_number + "_Shape.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Vector to load data into
		vector<OM::Object>		vector_obj;
		OM::Object* OBJ = new  OM::Object;

		// Parse YAML File
		YAML::Parser			parser(ifs);
		YAML::Node				yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key{ 0 };
			long		type{ 0 };

			i.first() >> key;

			// If key is 'Object'
			if (key == find_object) {

				// Iterate through 'Object' List
				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
					j.first() >> object_type;								// Get Object Type String

					// If  Object is matches list of existing object (e.g. '02_Wall', '01_Floor', '04_Portrait', etc.)
					if (object_types.find(object_type) != string::npos) {

						// Iterate through Specific Object
						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
							k.first() >> object_data_type;					// Get the Data Type String

							// If Node is "Type"
							if (object_data_type == "Type") {
								k.second() >> type;
								OBJ->type = static_cast<unsigned long>(type);
							}

							// If Node is "Mesh"
							if (object_data_type == "Mesh") {
								// Local Placeholder to Extract Data
								f32 uv_01,
									uv_02,
									uv_03,
									uv_04,
									uv_05,
									uv_06;

								k.second()["uv_01"] >> uv_01;
								k.second()["uv_02"] >> uv_02;
								k.second()["uv_03"] >> uv_03;
								k.second()["uv_04"] >> uv_04;
								k.second()["uv_05"] >> uv_05;
								k.second()["uv_06"] >> uv_06;

								// Start creating mesh for object
								AEGfxMeshStart();
								AEGfxTriAdd(
									-0.5f, -0.5f, 0xFFFF0000, uv_01, uv_02,		// bottom left
									0.5f, -0.5f, 0xFFFF0000, uv_03, uv_04,		// bottom right
									-0.5f, 0.5f, 0xFFFF0000, uv_05, uv_06		// top left
								);
								AEGfxTriAdd(
									0.5f, 0.5f, 0xFFFF0000, uv_03, uv_06,		// top right
									0.5f, -0.5f, 0xFFFF0000, uv_03, uv_04,		// bottom right
									-0.5f, 0.5f, 0xFFFF0000, uv_05, uv_06		// top left
								);

								// Set Object Mesh
								OBJ->pMesh = AEGfxMeshEnd();
							}

							// If Node is "Texture"
							if (object_data_type == "Texture") {
								// Local Placeholder to Extract Data
								string texture_filename{ 0 };
								k.second() >> texture_filename;

								// Check Filename
								ifstream ifs_02(texture_filename);
								if (!ifs_02.good()) {
									texture_filename = "." + texture_filename;
									ifs_02.open("." + texture_filename);
								}

								// Set Object Texture and assert message if failed
								AE_ASSERT_MESG(OBJ->pTex = AEGfxTextureLoad(texture_filename.c_str()), "Failed to load texture");
								ifs_02.close();
							}

							// If Node is "Width"
							if (object_data_type == "Width") {
								k.second() >> OBJ->width;
							}

							// If Node is "Length"
							if (object_data_type == "Length") {
								k.second() >> OBJ->length;
							}

							// If Node is "Height"
							if (object_data_type == "Height") {
								k.second() >> OBJ->height;
							}
						}// END For-Loop Through Specific Object

						// Push into Vector
						vector_obj.push_back(*OBJ);

					}// END If Specific Object Exist
				}// END For-Loop Through Object
			}// END If key is Object
		}// END For-Loop Through YAML File

		delete OBJ;				// Delete Temporary Struct
		ifs.close();			// Close File Stream
		return &vector_obj;		// Return New Vector

	}// END LoadShapeFromYAML



	vector<OM::ObjectInst>* Import::Load_Transform_From_YAML(const string level_number, vector<OM::Object>& vO) {

		// Strings for Filtering through the YAML file
		string
			find_object{ "Object_Instance" },
			object_types{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
			object_type{ 0 },
			object_type_number{ 0 },
			object_data_type{ 0 };

		// YAML file to read from
		string file_name{ "./Resource/Data/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Vector to load data into
		vector<OM::ObjectInst>	vector_obj_inst;
		OM::ObjectInst* OBJ_INST = new OM::ObjectInst;

		// Parse YAML File
		YAML::Parser			parser(ifs);
		YAML::Node				yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key{ 0 };
			long		type{ 0 };
			i.first() >> key;

			// If key is 'Object'
			if (key == find_object) {

				// Iterate through 'Object' List
				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
					j.first() >> object_type;								// Get Object Type String

					// If  Object is matches list of existing object (e.g. '02_Wall', '01_Floor', '04_Portrait', etc.)
					if (object_types.find(object_type) != string::npos) {

						// Iterate through specific 'Object' List
						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
							k.first() >> object_type_number;				// Get the Number of the Object	String

							// If Numbered Object is part of Object (e.g. '02_Wall_00' is under '02_Wall')
							if (object_type_number.find(object_type) != string::npos) {

								// Iterate through Numbered Object
								for (YAML::Iterator l = k.second().begin(); l != k.second().end(); l++) {
									l.first() >> object_data_type;			// Get the Data Type String

									// If Node is "Type"
									if (object_data_type == "Type") {
										l.second() >> type;
										for (int m{ 0 }; m < vO.size(); m++)
											if (vO[m].type == type)
												OBJ_INST->pObj = &vO[m];
									}

									// If Node is "Flag"
									if (object_data_type == "Flag") {
										long flag{ 0 };
										l.second() >> flag;
										OBJ_INST->flag = static_cast<unsigned long>(flag);
									}

									// If Node is "Texture_Offset"
									if (object_data_type == "Texture_Offset") {
										l.second()["x_offset"] >> OBJ_INST->tex_offset.x;
										l.second()["y_offset"] >> OBJ_INST->tex_offset.y;
									}

									// If Node is "Transformation"
									if (object_data_type == "Transformation") {

										l.second()["scale_x"] >> OBJ_INST->transform.m[0][0];
										l.second()["shear_x"] >> OBJ_INST->transform.m[0][1];
										l.second()["position_x"] >> OBJ_INST->transform.m[0][2];
										l.second()["shear_y"] >> OBJ_INST->transform.m[1][0];
										l.second()["scale_y"] >> OBJ_INST->transform.m[1][1];
										l.second()["position_y"] >> OBJ_INST->transform.m[1][2];
										l.second()["elapsed"] >> OBJ_INST->transform.m[2][0];
										l.second()["empty"] >> OBJ_INST->transform.m[2][1];
										l.second()["position_z"] >> OBJ_INST->transform.m[2][2];
									}
								}// END For-Loop Through Numbered Object_Instance

								// Push into Vector
								vector_obj_inst.push_back(*OBJ_INST);

							}// END If Numbered Object Belong to Specific Object
						}// END For-Loop Through Specific Object Type
					}// END If Specific Object Exist
				}// END For-Loop Through Object_Instance
			}// END If key is Object_Instance
		}// END For-Loop Through YAML File

		delete OBJ_INST;			// Delete Temporary Struct
		ifs.close();				// Close File Stream
		return &vector_obj_inst;		// Return New Vector

	}// END LoadTransformFromYAML



	OM::Character* Import::Load_Player_Stats_From_YAML(const string level_number) {
		// Strings for Filtering through the YAML file
		string
			find_object{ "Object_Instance" },
			object_types{ "00_Player" },
			object_type{ 0 },
			object_type_number{ 0 },
			object_data_type{ 0 };

		// YAML file to read from
		string file_name{ "./Resource/Data/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Struct to load data into
		OM::Character* sCHARACTER = new  OM::Character;

		// Parse YAML File
		YAML::Parser parser(ifs);
		YAML::Node yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key{ 0 };
			i.first() >> key;

			// If key is 'ObjectInstance'
			if (key == find_object) {

				// Iterate through 'Object_Instance' List
				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
					j.first() >> object_type;								// Get Object Type String

					// If  Object matches list of existing object ("00_Player")
					if (object_types.find(object_type) != string::npos) {

						// Iterate through specific 'Object' List
						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
							k.first() >> object_type_number;				// Get the Number of the Object	String

							// If Numbered Object is part of Object (e.g. '00_Player_00' is under '00_Player')
							if (object_type_number.find(object_type) != string::npos) {

								// Iterate through Numbered Object
								for (YAML::Iterator l = k.second().begin(); l != k.second().end(); l++) {
									l.first() >> object_data_type;			// Get the Data Type String

									// If Node is "Direction"
									if (object_data_type == "Direction") {
										l.second()["direction_x"] >> sCHARACTER->dir.x;
										l.second()["direction_y"] >> sCHARACTER->dir.y;
									}

									// If Node is "Input"
									if (object_data_type == "Input") {
										l.second()["input_x"] >> sCHARACTER->input.x;
										l.second()["input_y"] >> sCHARACTER->input.y;
									}

									// If Node is "Z_Velocity"
									if (object_data_type == "Z_Velocity") {
										l.second() >> sCHARACTER->zVel;
									}

									// If Node is "Sprite_Iteration"
									if (object_data_type == "Sprite_Iteration") {
										l.second() >> sCHARACTER->spriteIteration;
									}
								}// END For-Loop Through Numbered Object_Instance
							}// END If Numbered Object Belong to Specific Object
						}// END For-Loop Through Specific Object Type
					}// END If Specific Object Exist
				}// END For-Loop Through Object_Instance
			}// END If key is Object_Instance
		}// END For-Loop Through YAML File

		ifs.close();				// Close File Stream
		return sCHARACTER;			// Return New Struct

	}// END Load_Player_Stats_From_YAML



}// End namespace Load_Data_From_File


/*
*  EXPORT HERE
*/

namespace FM
{
	using namespace std;

	void Set_Object_Transform_Type(vector<OM::ObjectInst>& vOBJ_INST, string& object_type, int& object_count, int& index, ofstream& data_file);
	void Print_To_Transform_YAML(vector<OM::ObjectInst>& vOBJ_INST, OM::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);

	void Export::Extract_Transform_Data_Out(vector<OM::ObjectInst> vOI, OM::Character p_player, const string level_number)
	{

		// file name to extract to based on level_number
		string
			out_file{ "./Resource/Data/Level_" + level_number + "_Transform_Extracted.yml" },
			object_type{ 0 };

		// converting int to string to count objects
		stringstream object_type_number;

		// out file to extract data to
		ofstream data_file(out_file);
		if (!data_file.good())
			data_file.open("." + out_file);

		// to check object type
		int
			type{ 0 },
			previous_type{ -1 };

		// if out file successfully opened
		if (data_file.is_open()) {
			data_file << "Level: " + level_number << endl;												// first line is level number
			data_file << "Object_Instance:" << endl;														// second line is 'Object_Instance: '

			// iterate through data vector
			for (int i{ 0 }, object_count{ 0 }; i < vOI.size(); i++, object_count++) {
				type = vOI[i].pObj->type;															// set type enum for object type

				// if object type changes, prints different object as header for list
				if (type != previous_type)
					Set_Object_Transform_Type(vOI, object_type, object_count, i, data_file);

				// adding '0' to front of object count if less than 10
				if (object_count < 10)
					object_type_number << '0' << object_count;
				else
					object_type_number << object_count;

				Print_To_Transform_YAML(vOI, p_player, object_type, object_type_number, i, data_file);	// print data of object to file

				previous_type = type;
			}
			data_file.close();																	// close file
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// if out file can't be opened
			exit(1);																			// exit program
		}
	}// END extract_transform_data_out



	void Set_Object_Transform_Type(vector<OM::ObjectInst>& vOI, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;												// Reset Object Count
		if (vOI[index].pObj->type == Enum::TYPE::PLAYER) {
			object_type = "00_Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::FLOOR) {
			object_type = "01_Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::WALL) {
			object_type = "02_Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::DECO) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::PORTRAIT) {
			object_type = "04_Portrait";								// Set to Portrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::LANDSCAPE) {
			object_type = "05_Landscape";								// Set to Landscape
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pObj->type == Enum::TYPE::PLATFORM) {
			object_type = "06_Platform";								// Set to Platform
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type



	void Print_To_Transform_YAML(vector<OM::ObjectInst>& vOI, OM::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {

		// Print data of object to file
		data_file << "    " << object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      " << "Type: " << vOI[index].pObj->type << endl;
		data_file << "      " << "Flag: " << vOI[index].flag << endl;
		data_file << "      " << "Texture_Offset:" << endl;
		data_file << "        " << "x_offset: " << vOI[index].tex_offset.x << endl;
		data_file << "        " << "y_offset: " << vOI[index].tex_offset.y << endl;
		data_file << "      " << "Transformation:" << endl;
		data_file << "        " << "scale_x: " << vOI[index].transform.m[0][0] << endl;
		data_file << "        " << "shear_x: " << vOI[index].transform.m[0][1] << endl;
		data_file << "        " << "position_x: " << vOI[index].transform.m[0][2] << endl;
		data_file << "        " << "shear_y: " << vOI[index].transform.m[1][0] << endl;
		data_file << "        " << "scale_y: " << vOI[index].transform.m[1][1] << endl;
		data_file << "        " << "position_y: " << vOI[index].transform.m[1][2] << endl;
		data_file << "        " << "elapsed: " << vOI[index].transform.m[2][0] << endl;
		data_file << "        " << "empty: " << vOI[index].transform.m[2][1] << endl;
		data_file << "        " << "position_z: " << vOI[index].transform.m[2][2] << endl;

		// Player Stats
		if (vOI[index].pObj->type == Enum::TYPE::PLAYER) {
			data_file << "      " << "Direction:" << endl;
			data_file << "        " << "direction_x: " << p_player.dir.x << endl;
			data_file << "        " << "direction_y: " << p_player.dir.y << endl;
			data_file << "      " << "Input:" << endl;
			data_file << "        " << "input_x: " << p_player.input.x << endl;
			data_file << "        " << "input_y: " << p_player.input.y << endl;
			data_file << "      " << "Z_Velocity: " << p_player.zVel << endl;
			data_file << "      " << "Sprite_Iteration: " << p_player.spriteIteration << endl;
		}

		data_file << endl;

	}// END Print_To_Transform_YAML








	const static int count = 3;


	void Option_Change(vector<OM::ObjectInst>& vOI) {
		// Scale Value
		f32 scaling = 1920.0f / static_cast<f32>(AEGetWindowWidth());

		//Set Object to ObjectInstance
		for (size_t i{ 0 }; i < vOI.size(); i++) {
			for (int j{ 0 }; j < count * 3; j++)
				vOI[i].transform.m[j / count][j % count] /= scaling;
		}

	}// END Init_Object_From_Vector



	void Init_Player(OM::ObjectInst* vOI, OM::Character* sCHARACTER, OM::Character& p_player) {

		p_player.pObjInst = vOI;							// Set Player ObjectInstance
		p_player.dir = (*sCHARACTER).dir;					// Set Player Direction
		p_player.input = (*sCHARACTER).input;				// Set Player Input
		p_player.zVel = (*sCHARACTER).zVel;					// Set Player z velocity
		p_player.spriteIteration = (*sCHARACTER).spriteIteration;		// Set Player Sprite Iteration

		delete sCHARACTER;															// Delete Struct

	}// END Init_Player
}


