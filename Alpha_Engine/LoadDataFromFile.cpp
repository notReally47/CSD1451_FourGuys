#include <string>					// For std::string
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <iostream>					// For std::cout debugging
#include "DataFiles.h"				// For ObjectTransform, ObjectShape & PlayerProperties
#include <yaml-cpp/yaml.h>			// For Parsing YAML Files

namespace Load_Data_From_File {

	using namespace std;



	vector<GameObjects::Object> Load_Shape_From_YAML(const string level_number) {

		// Strings for Filtering through the YAML file
		string 
			find_object				{ "Object" },
			object_types			{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
			object_type				{ 0 }, 
			object_type_number		{ 0 }, 
			object_data_type		{ 0 };

		// YAML file to read from
		string file_name			{ "./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Shape.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Vector to load data into
		vector<GameObjects::Object>		vector_obj;
		GameObjects::Object*			OBJ			= new GameObjects::Object;

		// Parse YAML File
		YAML::Parser			parser(ifs);
		YAML::Node				yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key		{ 0 };
			long		type	{ 0 };

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
		return vector_obj;		// Return New Vector

	}// END LoadShapeFromYAML



	vector<GameObjects::ObjectInst> Load_Transform_From_YAML(const string level_number, vector<GameObjects::Object>& vector_OBJ) {

		// Strings for Filtering through the YAML file
		string 
			find_object				{ "Object_Instance" },
			object_types			{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
			object_type				{ 0 }, 
			object_type_number		{ 0 }, 
			object_data_type		{ 0 };

		// YAML file to read from
		string file_name			{ "./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Vector to load data into
		vector<GameObjects::ObjectInst>	vector_obj_inst;
		GameObjects::ObjectInst*		OBJ_INST		= new GameObjects::ObjectInst;

		// Parse YAML File
		YAML::Parser			parser(ifs);
		YAML::Node				yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key		{ 0 };
			long		type	{ 0 };
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
										for (int m{ 0 }; m < vector_OBJ.size(); m++)
											if (vector_OBJ[m].type == type) {
												OBJ_INST->pObj = &vector_OBJ[m];
											}
									}

									// If Node is "Flag"
									if (object_data_type == "Flag") {
										l.second() >> OBJ_INST->flag;
									}

									// If Node is "Texture_Offset"
									if (object_data_type == "Texture_Offset") {
										l.second()["x_offset"]		>> OBJ_INST->tex_offset.x;
										l.second()["y_offset"]		>> OBJ_INST->tex_offset.y;
									}

									// If Node is "Transformation"
									if (object_data_type == "Transformation") {
										l.second()["scale_x"]		>> OBJ_INST->transform.m[0][0];
										l.second()["shear_x"]		>> OBJ_INST->transform.m[0][1];
										l.second()["position_x"]	>> OBJ_INST->transform.m[0][2];
										l.second()["shear_y"]		>> OBJ_INST->transform.m[1][0];
										l.second()["scale_y"]		>> OBJ_INST->transform.m[1][1];
										l.second()["position_y"]	>> OBJ_INST->transform.m[1][2];
										l.second()["elapsed"]		>> OBJ_INST->transform.m[2][0];
										l.second()["empty"]			>> OBJ_INST->transform.m[2][1];
										l.second()["position_z"]	>> OBJ_INST->transform.m[2][2];
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
		return vector_obj_inst;		// Return New Vector

	}// END LoadTransformFromYAML



	GameObjects::Character* Load_Player_Stats_From_YAML(const string level_number) {
		// Strings for Filtering through the YAML file
		string 
			find_object				{ "Object_Instance" },
			object_types			{ "00_Player" },
			object_type				{ 0 }, 
			object_type_number		{ 0 }, 
			object_data_type		{ 0 };

		// YAML file to read from
		string file_name			{ "./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		// Struct to load data into
		GameObjects::Character* sCHARACTER = new GameObjects::Character;

		// Parse YAML File
		YAML::Parser parser(ifs);
		YAML::Node yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string		key		{ 0 };
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
										l.second()["direction_x"]	>> sCHARACTER->dir.x;
										l.second()["direction_y"]	>> sCHARACTER->dir.y;
									}

									// If Node is "Input"
									if (object_data_type == "Input") {
										l.second()["input_x"]		>> sCHARACTER->input.x;
										l.second()["input_y"]		>> sCHARACTER->input.y;
									}

									// If Node is "Is_Moving"
									if (object_data_type == "Is_Moving") {
										int is_moving{ 0 };
										l.second() >> is_moving;
										sCHARACTER->isMoving = is_moving;
									}


									// If Node is "Is_Jumping"
									if (object_data_type == "Is_Jumping") {
										int is_jumping{ 0 };
										l.second() >> is_jumping;
										sCHARACTER->isJumping = is_jumping;
									}


									// If Node is "Z_Velocity"
									if (object_data_type == "Z_Velocity") {
										l.second() >> sCHARACTER->zVel;
									}

									// If Node is "Speed"
									if (object_data_type == "Speed") {
										l.second() >> sCHARACTER->speed;
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