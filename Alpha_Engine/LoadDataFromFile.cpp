#include <string>					// For std::string
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <iostream>					// For std::cout debugging
#include "DataFiles.h"				// For ObjectTransform, ObjectShape & PlayerProperties
#include <yaml-cpp/yaml.h>			// For Parsing YAML Files

namespace Load_Data_From_File {

	using namespace std;



	vector<ObjectShape> Load_Shape_From_YAML(const string level_number) {

		// Strings for Filtering through the YAML file
		string find_object = "Object",
			object_types = "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 08_Platform",
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from

		string file_name{ "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Shape.yml" };
		ifstream ifs(file_name.c_str());
		if (!ifs.good())
			ifs.open("./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Shape.yml");

		// Vector to load data into
		vector<ObjectShape> vector_os;
		ObjectShape* OS = new ObjectShape;

		// Parse YAML File
		YAML::Parser parser(ifs);
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

					// If  Object is matches list of existing object (e.g. '02_Wall', '01_Floor', '04_Portrait', etc.)
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

						// Push into Vector
						vector_os.push_back(*OS);
					}
				}
			}
		}

		delete OS;
		ifs.close();
		return vector_os;

	}// END LoadShapeFromYAML



	vector<ObjectTransform> Load_Transform_From_YAML(const string level_number, vector<ObjectShape> vector_OS) {

		// Strings for Filtering through the YAML file
		string find_object = "ObjectInstance",
			object_types = "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 08_Platform",
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from
		string file_name{ "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name.c_str());

		if (!ifs.good())
			ifs.open("./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml");

		// Vector to load data into
		vector<ObjectTransform> vector_ot;
		ObjectTransform* OT = new ObjectTransform;

		// Parse YAML File
		YAML::Parser parser(ifs);
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
										for (int m{ 0 }; m < vector_OS.size(); m++)
											if (vector_OS[m].type == type)
												OT->OS = vector_OS[m];
									}

									// If Node is "Flag"
									if (object_data_type == "Flag") {
										l.second() >> OT->flag;
									}

									// If Node is "Texture_Offset"
									if (object_data_type == "Texture_Offset") {
										l.second()["x_offset"] >> OT->texture_offset_x;
										l.second()["y_offset"] >> OT->texture_offset_y;
									}

									// If Node is "Transformation"
									if (object_data_type == "Transformation") {
										l.second()["scale_x"] >> OT->scale_x;
										l.second()["shear_x"] >> OT->shear_x;
										l.second()["position_x"] >> OT->position_x;
										l.second()["scale_y"] >> OT->scale_y;
										l.second()["shear_y"] >> OT->shear_y;
										l.second()["position_y"] >> OT->position_y;
										l.second()["width"] >> OT->width;
										l.second()["length"] >> OT->length;
										l.second()["height"] >> OT->height;
									}

									// If Node is "Elapsed"
									if (object_data_type == "Elapsed") {
										l.second() >> OT->elapsed;
									}

									// If Node is "Z_Axis"
									if (object_data_type == "Z_Axis") {
										l.second() >> OT->z_axis;
									}
								}

								// Push into Vector
								vector_ot.push_back(*OT);
							}
						}
					}
				}
			}
		}

		delete OT;
		ifs.close();
		return vector_ot;

	}// END LoadTransformFromYAML



	PlayerProperties* Load_Player_Stats_From_YAML(const string level_number) {
		// Strings for Filtering through the YAML file
		string find_object = "ObjectInstance",
			object_types = "00_Player",
			object_type{ 0 }, object_type_number{ 0 }, object_data_type{ 0 };

		// YAML file to read from
		string file_name{ "../Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml" };
		ifstream ifs(file_name.c_str());

		if (!ifs.good())
			ifs.open("./Assets/Data_Files/Level_" + level_number + "/Level_" + level_number + "_Transform.yml");

		// Struct to load data into
		PlayerProperties* PP = new PlayerProperties;

		// Parse YAML File
		YAML::Parser parser(ifs);
		YAML::Node yaml_document;
		parser.GetNextDocument(yaml_document);

		// Iterate through YAML File
		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
			string key;
			i.first() >> key;
			long type{ 0 };

			// If key is 'ObjectInstance'
			if (key == find_object) {

				// Iterate through 'ObjectInstance' List
				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
					j.first() >> object_type;								// Get Object Type String

					// If  Object is matches list of existing object ("00_Player")
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
										l.second()["direction_x"] >> PP->direction.x;
										l.second()["direction_y"] >> PP->direction.y;
									}

									// If Node is "Input"
									if (object_data_type == "Input") {
										l.second()["input_x"] >> PP->input.x;
										l.second()["input_y"] >> PP->input.y;
									}

									// If Node is "Rotation"
									if (object_data_type == "Rotation") {
										l.second() >> PP->rotation;
									}

									// If Node is "Speed"
									if (object_data_type == "Speed") {
										l.second() >> PP->speed;
									}

									// If Node is "Sprite_Iteration"
									if (object_data_type == "Sprite_Iteration") {
										l.second() >> PP->sprite_iteration;
									}
								}
							}
						}
					}
				}
			}
		}

		ifs.close();
		return PP;

	}// END Load_Player_Stats_From_YAML



	void Load_Shape_To_Object(vector<ObjectShape>& vOS, GameObjects::Object* objs[]) {
		
		// Iterate through ObjectShape Vector
		for (auto iter : vOS) {

			// Set Object Type
			objs[iter.type]->type = iter.type;

			// Set Object Texture and assert message if failed
			AE_ASSERT_MESG(objs[iter.type]->pTex = AEGfxTextureLoad(iter.texture_file.c_str()), "Failed to load texture");

			// Start creating mesh for object
			AEGfxMeshStart();
			AEGfxTriAdd(
				-0.5f, -0.5f, 0xFFFF0000, iter.uv_01, iter.uv_02,	// bottom left
				0.5f, -0.5f, 0xFFFF0000, iter.uv_03, iter.uv_04,	// bottom right
				-0.5f, 0.5f, 0xFFFF0000, iter.uv_05, iter.uv_06		// top left
			);
			AEGfxTriAdd(
				0.5f, 0.5f, 0xFFFF0000, iter.uv_03, iter.uv_06,		// top right
				0.5f, -0.5f, 0xFFFF0000, iter.uv_03, iter.uv_04,	// bottom right
				-0.5f, 0.5f, 0xFFFF0000, iter.uv_05, iter.uv_06		// top left
			);

			// Set Object Mesh
			objs[iter.type]->pMesh = AEGfxMeshEnd();
			
		}

		// Clear ObjectShape Vector
		vOS.clear();


	}// END LoadTextureToObject



}// End namespace Load_Data_From_File