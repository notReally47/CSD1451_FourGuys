/*!***********************************************************************
  \file   FileManager.cpp
  \authors
  
  \brief 
  This file contains the implementation of the FileManager class

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

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
#include <iostream>
#endif

vector<OM::Object>		FM::GameData::vO;
vector<OM::ObjectInst>	FM::GameData::vOI;
vector<OM::ObjectLayer> FM::GameData::vOL;
OM::Character			FM::GameData::player;



/*
				 8764  39   34  644348     223    742524   948266
				  42   248 468  83   72   79 53   47   38    22
				  45   4828777  58   86  78   95  63   37    22
				  87   57 3 22  844969   22   97  856494     27
				  48   55   98  95        87 49   49   99    99
				 7456  99   75  65         626    29   86    44
*/
namespace FM {


	// Load Shape From Data Functions
	void operator >> (const YAML::Node& node, OM::Object& Object) {
		string	type{}, flag{};
		f32		uv01{ 0 }, uv02{ 0 }, uv03{ 0 }, uv04{ 0 }, uv05{ 0 }, uv06{ 0 };

		// Extract Object Type
		node["Type"] >> type;
		if (type == "Player")
			Object.type = 0;
		else if (type == "Floor")
			Object.type = 1;
		else if (type == "Wall")
			Object.type = 2;
		else if (type == "Decoration")
			Object.type = 3;
		else if (type == "Portrait")
			Object.type = 4;
		else if (type == "Platform")
			Object.type = 5;

		node["Flag"] >> type;
		if (type == "Empty")
			Object.flag = 0;
		else if (type == "Candle")
			Object.flag = 0;
		else if (type == "Horizontal")
			Object.flag = 0;
		else if (type == "Vertical")
			Object.flag = 0;
		else if (type == "Stairs")
			Object.flag = 0;
		else if (type == "Bridge")
			Object.flag = 0;

		// Extract Object Mesh Data
		node["Mesh"][0] >> uv01;
		node["Mesh"][1] >> uv02;
		node["Mesh"][2] >> uv03;
		node["Mesh"][3] >> uv04;
		node["Mesh"][4] >> uv05;
		node["Mesh"][5] >> uv06;

		// Start creating mesh for object
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, uv01, uv02,		// bottom left
			0.5f, -0.5f, 0xFFFF0000, uv03, uv04,		// bottom right
			-0.5f, 0.5f, 0xFFFF0000, uv05, uv06			// top left
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, uv03, uv06,			// top right
			0.5f, -0.5f, 0xFFFF0000, uv03, uv04,		// bottom right
			-0.5f, 0.5f, 0xFFFF0000, uv05, uv06			// top left
		);

		// Set Object Mesh
		Object.pMesh = AEGfxMeshEnd();

		// Local Placeholder to Extract Data
		string textureFilename{ 0 };
		node["Texture"] >> textureFilename;

		// Check Filename
		ifstream ifs(textureFilename);
		if (!ifs.good()) {
			textureFilename = "." + textureFilename;
			ifs.open(textureFilename);
		}

		// Set Object Texture and assert message if failed
		AE_ASSERT_MESG(Object.pTex = AEGfxTextureLoad(textureFilename.c_str()), "Failed to load texture");
		ifs.close();
	}// END operator >> overload for Load Shape



	void GameData::LoadShapeFromFile() {
		// YAML file to read from
		string file_name{ "./Resource/Data/Shape_Data.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);

		for (unsigned i = 0; i < doc.size(); i++) {
			OM::Object Object;
			doc[i] >> Object;
			FM::GameData::vO.push_back(Object);
		}
	}// END LoadShapeFromFile



	// Load Transform From Data Functions
	void operator >> (const YAML::Node& node, OM::ObjectInst& ObjectInstance) {
		string			type_string{};
		unsigned long	type{ 0 };

		// Extract Object Type
		node["Type"] >> type_string;
		if (type_string == "Player")
			type = 0;
		else if (type_string == "Floor")
			type = 1;
		else if (type_string == "Wall")
			type = 2;
		else if (type_string == "Decoration")
			type = 3;
		else if (type_string == "Portrait")
			type = 4;
		else if (type_string == "Platform")
			type = 5;

		for (size_t i{ 0 }; i < FM::GameData::vO.size(); i++)
			if (FM::GameData::vO[i].type == type)
				ObjectInstance.pO = &FM::GameData::vO[i];

		// Extract Flag
		node["Flag"] >> ObjectInstance.flag;

		// Extract Texture Offset
		node["Texture_Offset"]["x_offset"] >> ObjectInstance.texture.x;
		node["Texture_Offset"]["y_offset"] >> ObjectInstance.texture.y;

		// Extract Transformation
		node["Transformation"]["scale_x"] >> ObjectInstance.transf.m[0][0];
		node["Transformation"]["shear_x"] >> ObjectInstance.transf.m[0][1];
		node["Transformation"]["position_x"] >> ObjectInstance.transf.m[0][2];
		node["Transformation"]["shear_y"] >> ObjectInstance.transf.m[1][0];
		node["Transformation"]["scale_y"] >> ObjectInstance.transf.m[1][1];
		node["Transformation"]["position_y"] >> ObjectInstance.transf.m[1][2];
		node["Transformation"]["elapsed"] >> ObjectInstance.transf.m[2][0];
		node["Transformation"]["empty"] >> ObjectInstance.transf.m[2][1];
		node["Transformation"]["position_z"] >> ObjectInstance.transf.m[2][2];
		//node["Pair"] >> ObjectInstance.pair;

	}// END operator >> overload for Load Transform



	void GameData::LoadTransformFromFile() {
		// YAML file to read from
		string file_name{ "./Resource/Data/Transform_Data.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);

		for (unsigned i = 0; i < doc.size(); i++) {
			OM::ObjectInst ObjectInstance{};
			doc[i] >> ObjectInstance;
			FM::GameData::vOI.push_back(ObjectInstance);
		}
	}// END LoadTransformFromFile


	// Load Player Stats From Data Functions
	void operator >> (const YAML::Node& node, OM::Character& Player) {

		//Set Player Object Instance & Object
		Player.pOI = &FM::GameData::vOI[0];

		// Extract Player Direction
		node["Direction"]["direction_x"] >> Player.dir.x;
		node["Direction"]["direction_y"] >> Player.dir.y;

		// Extract Player Input
		node["Input"]["input_x"] >> Player.input.x;
		node["Input"]["input_y"] >> Player.input.y;

		// Extract Player Z Velocity
		node["Z_Velocity"] >> Player.zVel;


		// Extract Player Sprite Iteration
		node["Sprite_Iteration"] >> Player.iter;

	}// END operator >> overload for Load Player Stats



	void GameData::LoadPlayerStatsFromFile() {
		// YAML file to read from
		string file_name{ "./Resource/Data/Transform_Data.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);
		OM::Character Player{};
		for (unsigned i = 0; i < 1; i++) {
			doc[i] >> Player;
		}

		GameData::player = Player;
	}// END LoadPlayerStatsFromFile


	// Load Layer From Data Functions
	void operator >> (const YAML::Node& node, OM::ObjectLayer& ObjectLayer) {
		string layer{};
		// Extract Layer Data
		node["Layer"] >> layer;
		if (layer == "Ground")
			ObjectLayer.layer = 0;
		else if (layer == "Floor01")
			ObjectLayer.layer = 1;
		else if (layer == "Floor02")
			ObjectLayer.layer = 2;
		else if (layer == "Floor03")
			ObjectLayer.layer = 3;
		else if (layer == "Floor04")
			ObjectLayer.layer = 4;
		else if (layer == "Floor05")
			ObjectLayer.layer = 5;
		else if (layer == "Floor06")
			ObjectLayer.layer = 6;
		else if (layer == "Floor07")
			ObjectLayer.layer = 7;
		else if (layer == "Floor08")
			ObjectLayer.layer = 8;
		else if (layer == "Floor09")
			ObjectLayer.layer = 9;
		else if (layer == "Floor10")
			ObjectLayer.layer = 10;
		else if (layer == "Floor11")
			ObjectLayer.layer = 11;
		else if (layer == "Floor12")
			ObjectLayer.layer = 12;
		else if (layer == "Floor13")
			ObjectLayer.layer = 13;
		else if (layer == "Floor14")
			ObjectLayer.layer = 14;
		else if (layer == "Floor15")
			ObjectLayer.layer = 15;
		else if (layer == "Floor16")
			ObjectLayer.layer = 16;

		// Extract Grid Data
		for (size_t i{ 0 }; i < 25; ++i)
			node["Grid"][i] >> ObjectLayer.data[i];

		// Extract Offset Data
		node["Offset"][0] >> ObjectLayer.offset.x;
		node["Offset"][1] >> ObjectLayer.offset.y;

		// Extract Transparency Data
		node["Transparency"] >> ObjectLayer.transp;

	}// END operator >> overload Object Layer



	void GameData::LoadLayersFromFile() {
		// YAML file to read from
		string file_name{ "./Resource/Data/Layer_Data.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);
		OM::Character Player{};
		for (unsigned i = 0; i < doc.size(); i++) {
			OM::ObjectLayer ObjectLayer{};
			doc[i] >> ObjectLayer;
			FM::GameData::vOL.push_back(ObjectLayer);
		}
	}// END LoadLayersFromFile


	void PrintToYAML(const int& index, ofstream& data_file) {

		// Print data of object to file
		if(FM::GameData::vOI[index].pO->type == Enum::TYPE::PLAYER)
			data_file << "- " << "Type: " << "Player" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::FLOOR)
			data_file << "- " << "Type: " << "Floor" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::WALL)
			data_file << "- " << "Type: " << "Wall" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::DECO)
			data_file << "- " << "Type: " << "Decoration" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::PORTRAIT)
			data_file << "- " << "Type: " << "Portrait" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::LANDSCAPE)
			data_file << "- " << "Type: " << "Portrait" << endl;
		else if (FM::GameData::vOI[index].pO->type == Enum::TYPE::PLATFORM)
			data_file << "- " << "Type: " << "Platform" << endl;
		data_file << "  " << "Flag: " << FM::GameData::vOI[index].flag << endl;
		data_file << "  " << "Texture_Offset:" << endl;
		data_file << "    " << "x_offset: " << FM::GameData::vOI[index].texture.x << endl;
		data_file << "    " << "y_offset: " << FM::GameData::vOI[index].texture.y << endl;
		data_file << "  " << "Transformation:" << endl;
		data_file << "    " << "scale_x: " << FM::GameData::vOI[index].transf.m[0][0] << endl;
		data_file << "    " << "shear_x: " << FM::GameData::vOI[index].transf.m[0][1] << endl;
		data_file << "    " << "position_x: " << FM::GameData::vOI[index].transf.m[0][2] << endl;
		data_file << "    " << "shear_y: " << FM::GameData::vOI[index].transf.m[1][0] << endl;
		data_file << "    " << "scale_y: " << FM::GameData::vOI[index].transf.m[1][1] << endl;
		data_file << "    " << "position_y: " << FM::GameData::vOI[index].transf.m[1][2] << endl;
		data_file << "    " << "elapsed: " << FM::GameData::vOI[index].transf.m[2][0] << endl;
		data_file << "    " << "empty: " << FM::GameData::vOI[index].transf.m[2][1] << endl;
		data_file << "    " << "position_z: " << FM::GameData::vOI[index].transf.m[2][2] << endl;
		data_file << "  " << "Pair: " << 0 << endl;

		// Player Stats
		if (FM::GameData::vOI[index].pO->type == Enum::TYPE::PLAYER) {
			data_file << "  " << "Direction:" << endl;
			data_file << "    " << "direction_x: " << FM::GameData::player.dir.x << endl;
			data_file << "    " << "direction_y: " << FM::GameData::player.dir.y << endl;
			data_file << "  " << "Input:" << endl;
			data_file << "    " << "input_x: " << FM::GameData::player.input.x << endl;
			data_file << "    " << "input_y: " << FM::GameData::player.input.y << endl;
			data_file << "  " << "Z_Velocity: " << FM::GameData::player.zVel << endl;
			data_file << "  " << "Sprite_Iteration: " << FM::GameData::player.iter << endl;
		}

		data_file << endl;

	}// END Print_To_Transform_YAML

	void GameData::ExtractTransformToFile() {
		// file name to extract to based on level_number
		string out_file{ "./Resource/Data/Transform_Data_Extracted.yml" };

		// out file to extract data to
		ofstream data_file(out_file);
		if (!data_file.good())
			data_file.open("." + out_file);

		// if out file successfully opened
		if (data_file.is_open()) {

			// iterate through data vector
			for (size_t i{ 0 }; i < FM::GameData::vOI.size(); ++i)
				PrintToYAML(i, data_file);	// print data of object to file

			data_file.close();
		}
		else {
			cout << "Error Opening File: " << out_file << endl;									// if out file can't be opened
			exit(1);																			// exit program
		}
	}



	// Scaling Stuff
	void GameData::Option_Change() {
		// Scale Value
		f32 scaling = 1920.0f / static_cast<f32>(AEGetWindowWidth());
		size_t count = 3;

		//Set Object to ObjectInstance
		for (size_t i{ 0 }; i < FM::GameData::vOI.size(); i++)
			for (size_t j{ 0 }; j < count * 3; j++)
				FM::GameData::vOI[i].transf.m[j / count][j % count] /= scaling;

	}// END Init_Object_From_Vector

}





//namespace FM
//{
//	/*
//				 8764  39   34  644348     223    742524   948266
//				  42   248 468  83   72   79 53   47   38    22
//				  45   4828777  58   86  78   95  63   37    22
//				  87   57 3 22  844969   22   97  856494     27
//				  48   55   98  95        87 49   49   99    99
//				 7456  99   75  65         626    29   86    44
//	*/
//	/*!***********************************************************************
//	  \brief Load mesh data from YAML file
//	  
//	  \param level_number 
//	  \return vector<OM::Object>* 
//	*************************************************************************/
//	vector<OM::Object>* Import::Load_Shape_From_YAML(const string level_number) {
//
//		// Strings for Filtering through the YAML file
//		string
//			find_object			{ "Object" },
//			object_types		{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
//			object_type			{ 0 },
//			object_type_number	{ 0 },
//			object_data_type	{ 0 };
//
//		// YAML file to read from
//		string file_name{ "./Resource/Data/Level_" + level_number + "_Shape.yml" };
//		ifstream ifs(file_name);
//		if (!ifs.good())
//			ifs.open("." + file_name);
//
//		// Vector to load data into
//		//vector<OM::Object>		vector_obj;
//		OM::Object* OBJ = new  OM::Object;
//
//		// Parse YAML File
//		YAML::Parser			parser(ifs);
//		YAML::Node				yaml_document;
//		parser.GetNextDocument(yaml_document);
//
//		// Iterate through YAML File
//		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
//			string		key	{ 0 };
//			long		type{ 0 };
//
//			i.first() >> key;
//
//			// If key is 'Object'
//			if (key == find_object) {
//
//				// Iterate through 'Object' List
//				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
//					j.first() >> object_type;								// Get Object Type String
//
//					// If  Object is matches list of existing object (e.g. '02_Wall', '01_Floor', '04_Portrait', etc.)
//					if (object_types.find(object_type) != string::npos) {
//
//						// Iterate through Specific Object
//						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
//							k.first() >> object_data_type;					// Get the Data Type String
//
//							// If Node is "Type"
//							if (object_data_type == "Type") {
//								k.second() >> type;
//								OBJ->type = static_cast<unsigned long>(type);
//							}
//
//							// If Node is "Mesh"
//							if (object_data_type == "Mesh") {
//								// Local Placeholder to Extract Data
//								f32 uv_01,
//									uv_02,
//									uv_03,
//									uv_04,
//									uv_05,
//									uv_06;
//
//								k.second()["uv_01"] >> uv_01;
//								k.second()["uv_02"] >> uv_02;
//								k.second()["uv_03"] >> uv_03;
//								k.second()["uv_04"] >> uv_04;
//								k.second()["uv_05"] >> uv_05;
//								k.second()["uv_06"] >> uv_06;
//
//								// Start creating mesh for object
//								AEGfxMeshStart();
//								AEGfxTriAdd(
//									-0.5f, -0.5f, 0xFFFF0000, uv_01, uv_02,		// bottom left
//									0.5f, -0.5f, 0xFFFF0000, uv_03, uv_04,		// bottom right
//									-0.5f, 0.5f, 0xFFFF0000, uv_05, uv_06		// top left
//								);
//								AEGfxTriAdd(
//									0.5f, 0.5f, 0xFFFF0000, uv_03, uv_06,		// top right
//									0.5f, -0.5f, 0xFFFF0000, uv_03, uv_04,		// bottom right
//									-0.5f, 0.5f, 0xFFFF0000, uv_05, uv_06		// top left
//								);
//
//								// Set Object Mesh
//								OBJ->pMesh = AEGfxMeshEnd();
//							}
//
//							// If Node is "Texture"
//							if (object_data_type == "Texture") {
//								// Local Placeholder to Extract Data
//								string texture_filename{ 0 };
//								k.second() >> texture_filename;
//
//								// Check Filename
//								ifstream ifs_02(texture_filename);
//								if (!ifs_02.good()) {
//									texture_filename = "." + texture_filename;
//									ifs_02.open(texture_filename);
//								}
//
//								// Set Object Texture and assert message if failed
//								AE_ASSERT_MESG(OBJ->pTex = AEGfxTextureLoad(texture_filename.c_str()), "Failed to load texture");
//								ifs_02.close();
//							}
//
//							// If Node is "Width"
//							if (object_data_type == "Width") {
//								//k.second() >> OBJ->width;
//							}
//
//							// If Node is "Length"
//							if (object_data_type == "Length") {
//								//k.second() >> OBJ->length;
//							}
//
//							// If Node is "Height"
//							if (object_data_type == "Height") {
//								//k.second() >> OBJ->height;
//							}
//						}// END For-Loop Through Specific Object
//
//						// Push into Vector
//						vO.push_back(*OBJ);
//
//					}// END If Specific Object Exist
//				}// END For-Loop Through Object
//			}// END If key is Object
//		}// END For-Loop Through YAML File
//
//		delete OBJ;				// Delete Temporary Struct
//		ifs.close();			// Close File Stream
//		return &vO;		// Return New Vector
//
//	}// END LoadShapeFromYAML
//
//	/*!***********************************************************************
//	  \brief Load transform data from YAML file
//	  
//	  \param level_number 
//	  \return vector<OM::ObjectInst>* 
//	*************************************************************************/
//	vector<OM::ObjectInst>* Import::Load_Transform_From_YAML(const string level_number) {
//
//		// Strings for Filtering through the YAML file
//		string
//			find_object			{ "Object_Instance" },
//			object_types		{ "00_Player 01_Floor 02_Wall 03_Decoration 04_Portrait 05_Landscape 06_Platform" },
//			object_type			{ 0 },
//			object_type_number	{ 0 },
//			object_data_type	{ 0 };
//
//		// YAML file to read from
//		string file_name{ "./Resource/Data/Level_" + level_number + "_Transform.yml" };
//		ifstream ifs(file_name);
//		if (!ifs.good())
//			ifs.open("." + file_name);
//
//		// Vector to load data into
//		OM::ObjectInst* OBJ_INST = new OM::ObjectInst;
//
//		// Parse YAML File
//		YAML::Parser			parser(ifs);
//		YAML::Node				yaml_document;
//		parser.GetNextDocument(yaml_document);
//
//		// Iterate through YAML File
//		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
//			string		key	{ 0 };
//			long		type{ 0 };
//			i.first() >> key;
//
//			// If key is 'Object'
//			if (key == find_object) {
//
//				// Iterate through 'Object' List
//				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
//					j.first() >> object_type;								// Get Object Type String
//
//					// If  Object is matches list of existing object (e.g. '02_Wall', '01_Floor', '04_Portrait', etc.)
//					if (object_types.find(object_type) != string::npos) {
//
//						// Iterate through specific 'Object' List
//						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
//							k.first() >> object_type_number;				// Get the Number of the Object	String
//
//							// If Numbered Object is part of Object (e.g. '02_Wall_00' is under '02_Wall')
//							if (object_type_number.find(object_type) != string::npos) {
//
//								// Iterate through Numbered Object
//								for (YAML::Iterator l = k.second().begin(); l != k.second().end(); l++) {
//									l.first() >> object_data_type;			// Get the Data Type String
//
//									// If Node is "Type"
//									if (object_data_type == "Type") {
//										l.second() >> type;
//										for (int m{ 0 }; m < vO.size(); m++)
//											if (vO[m].type == static_cast<unsigned long>(type))
//												OBJ_INST->pO = &vO[m];
//									}
//
//									// If Node is "Flag"
//									if (object_data_type == "Flag") {
//										long tflag{ 0 };
//										l.second() >> tflag;
//										OBJ_INST->flag = static_cast<unsigned long>(tflag);
//									}
//
//									// If Node is "Texture_Offset"
//									if (object_data_type == "Texture_Offset") {
//										l.second()["x_offset"]		>> OBJ_INST->texture.x;
//										l.second()["y_offset"]		>> OBJ_INST->texture.y;
//									}
//
//									// If Node is "Transformation"
//									if (object_data_type == "Transformation") {
//
//										l.second()["scale_x"]		>> OBJ_INST->transf.m[0][0];
//										l.second()["shear_x"]		>> OBJ_INST->transf.m[0][1];
//										l.second()["position_x"]	>> OBJ_INST->transf.m[0][2];
//										l.second()["shear_y"]		>> OBJ_INST->transf.m[1][0];
//										l.second()["scale_y"]		>> OBJ_INST->transf.m[1][1];
//										l.second()["position_y"]	>> OBJ_INST->transf.m[1][2];
//										l.second()["elapsed"]		>> OBJ_INST->transf.m[2][0];
//										l.second()["empty"]			>> OBJ_INST->transf.m[2][1];
//										l.second()["position_z"]	>> OBJ_INST->transf.m[2][2];
//									}
//								}// END For-Loop Through Numbered Object_Instance
//
//								// Push into Vector
//								vOI.push_back(*OBJ_INST);
//
//							}// END If Numbered Object Belong to Specific Object
//						}// END For-Loop Through Specific Object Type
//					}// END If Specific Object Exist
//				}// END For-Loop Through Object_Instance
//			}// END If key is Object_Instance
//		}// END For-Loop Through YAML File
//
//		delete OBJ_INST;				// Delete Temporary Struct
//		ifs.close();					// Close File Stream
//		return &vOI;		// Return New Vector
//
//	}// END LoadTransformFromYAML
//
//	/*!***********************************************************************
//	  \brief Loads the player stats from a YAML file
//	  
//	  \param level_number 
//	  \return OM::Character* 
//	*************************************************************************/
//	OM::Character* Import::Load_Player_Stats_From_YAML(const string level_number) {
//		// Strings for Filtering through the YAML file
//		string
//			find_object			{ "Object_Instance" },
//			object_types		{ "00_Player" },
//			object_type			{ 0 },
//			object_type_number	{ 0 },
//			object_data_type	{ 0 };
//
//		// YAML file to read from
//		string file_name{ "./Resource/Data/Level_" + level_number + "_Transform.yml" };
//		ifstream ifs(file_name);
//		if (!ifs.good())
//			ifs.open("." + file_name);
//
//		// Struct to load data into
//		OM::Character* sCHARACTER = new  OM::Character;
//
//		// Parse YAML File
//		YAML::Parser parser(ifs);
//		YAML::Node yaml_document;
//		parser.GetNextDocument(yaml_document);
//
//		// Iterate through YAML File
//		for (YAML::Iterator i = yaml_document.begin(); i != yaml_document.end(); i++) {
//			string		key{ 0 };
//			i.first() >> key;
//
//			// If key is 'ObjectInstance'
//			if (key == find_object) {
//
//				// Iterate through 'Object_Instance' List
//				for (YAML::Iterator j = i.second().begin(); j != i.second().end(); j++) {
//					j.first() >> object_type;								// Get Object Type String
//
//					// If  Object matches list of existing object ("00_Player")
//					if (object_types.find(object_type) != string::npos) {
//
//						// Iterate through specific 'Object' List
//						for (YAML::Iterator k = j.second().begin(); k != j.second().end(); k++) {
//							k.first() >> object_type_number;				// Get the Number of the Object	String
//
//							// If Numbered Object is part of Object (e.g. '00_Player_00' is under '00_Player')
//							if (object_type_number.find(object_type) != string::npos) {
//
//								// Iterate through Numbered Object
//								for (YAML::Iterator l = k.second().begin(); l != k.second().end(); l++) {
//									l.first() >> object_data_type;			// Get the Data Type String
//
//									// If Node is "Direction"
//									if (object_data_type == "Direction") {
//										l.second()["direction_x"] >> sCHARACTER->dir.x;
//										l.second()["direction_y"] >> sCHARACTER->dir.y;
//									}
//
//									// If Node is "Input"
//									if (object_data_type == "Input") {
//										l.second()["input_x"] >> sCHARACTER->input.x;
//										l.second()["input_y"] >> sCHARACTER->input.y;
//									}
//
//									// If Node is "Z_Velocity"
//									if (object_data_type == "Z_Velocity") {
//										l.second() >> sCHARACTER->zVel;
//									}
//
//									// If Node is "Sprite_Iteration"
//									if (object_data_type == "Sprite_Iteration") {
//										l.second() >> sCHARACTER->iter;
//									}
//								}// END For-Loop Through Numbered Object_Instance
//							}// END If Numbered Object Belong to Specific Object
//						}// END For-Loop Through Specific Object Type
//					}// END If Specific Object Exist
//				}// END For-Loop Through Object_Instance
//			}// END If key is Object_Instance
//		}// END For-Loop Through YAML File
//
//		ifs.close();				// Close File Stream
//		return sCHARACTER;			// Return New Struct
//
//	}// END Load_Player_Stats_From_YAML
//
//
//
//}// End namespace Load_Data_From_File

/*!***********************************************************************
___________4857784_ 75___49_ 654933__ __586___ 242553__ 633792____________
___________82______ 763_664_ 48___28_ _47_46__ 98___62_ __62______________
___________62572___ _42424__ 25___94_ 35___29_ 73___39_ __36______________
___________78______ _27567__ 492745__ 62___38_ 368929__ __76______________
___________89______ 557_489_ 77______ _27_67__ 42___85_ __32______________
___________6328975_ 35___96_ 49______ __585___ 24___77_ __47______________
*************************************************************************/
namespace FM
{
	using namespace std;

	void Set_Object_Transform_Type(vector<OM::ObjectInst>& vOBJ_INST, string& object_type, int& object_count, int& index, ofstream& data_file);
	void Print_To_Transform_YAML(vector<OM::ObjectInst>& vOBJ_INST, OM::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file);

	/*!***********************************************************************
	  \brief Extracts the transform data from the object instances and
	  exports it to a YAML file

	  \param vOI
	  \param p_player
	  \param level_number
	*************************************************************************/
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
			data_file << "Level: " + level_number << endl;													// first line is level number
			data_file << "Object_Instance:" << endl;														// second line is 'Object_Instance: '

			// iterate through data vector
			for (int i{ 0 }, object_count{ 0 }; i < vOI.size(); i++, object_count++) {
				type = vOI[i].pO->type;																	// set type enum for object type

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

	/*!***********************************************************************
	  \brief Sets the object type and prints the header for the object type

	  \param vOI
	  \param object_type
	  \param object_count
	  \param index
	  \param data_file
	*************************************************************************/
	void Set_Object_Transform_Type(vector<OM::ObjectInst>& vOI, string& object_type, int& object_count, int& index, ofstream& data_file) {
		object_count = 0;												// Reset Object Count
		if (vOI[index].pO->type == Enum::TYPE::PLAYER) {
			object_type = "00_Player";									// Set to Player
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::FLOOR) {
			object_type = "01_Floor";									// Set to Floor
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::WALL) {
			object_type = "02_Wall";									// Set to Wall
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::DECO) {
			object_type = "03_Decoration";								// Set to Decoration
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::PORTRAIT) {
			object_type = "04_Portrait";								// Set to Portrait
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::LANDSCAPE) {
			object_type = "05_Landscape";								// Set to Landscape
			data_file << "  " << object_type << ":" << endl;
		}
		else if (vOI[index].pO->type == Enum::TYPE::PLATFORM) {
			object_type = "06_Platform";								// Set to Platform
			data_file << "  " << object_type << ":" << endl;
		}
	}// END Set_Object_Transform_Type

	/*!***********************************************************************
	  \brief Prints the data of the object to the YAML file

	  \param vOI
	  \param p_player
	  \param object_type
	  \param object_type_number
	  \param index
	  \param data_file
	*************************************************************************/
	void Print_To_Transform_YAML(vector<OM::ObjectInst>& vOI, OM::Character p_player, string& object_type, stringstream& object_type_number, int& index, ofstream& data_file) {

		// Print data of object to file
		data_file << "    " << object_type << "_" << object_type_number.str() << ":" << endl;
		object_type_number.str(string());
		data_file << "      " << "Type: " << vOI[index].pO->type << endl;
		data_file << "      " << "Flag: " << vOI[index].flag << endl;
		data_file << "      " << "Texture_Offset:" << endl;
		data_file << "        " << "x_offset: " << vOI[index].texture.x << endl;
		data_file << "        " << "y_offset: " << vOI[index].texture.y << endl;
		data_file << "      " << "Transformation:" << endl;
		data_file << "        " << "scale_x: " << vOI[index].transf.m[0][0] << endl;
		data_file << "        " << "shear_x: " << vOI[index].transf.m[0][1] << endl;
		data_file << "        " << "position_x: " << vOI[index].transf.m[0][2] << endl;
		data_file << "        " << "shear_y: " << vOI[index].transf.m[1][0] << endl;
		data_file << "        " << "scale_y: " << vOI[index].transf.m[1][1] << endl;
		data_file << "        " << "position_y: " << vOI[index].transf.m[1][2] << endl;
		data_file << "        " << "elapsed: " << vOI[index].transf.m[2][0] << endl;
		data_file << "        " << "empty: " << vOI[index].transf.m[2][1] << endl;
		data_file << "        " << "position_z: " << vOI[index].transf.m[2][2] << endl;

		// Player Stats
		if (vOI[index].pO->type == Enum::TYPE::PLAYER) {
			data_file << "      " << "Direction:" << endl;
			data_file << "        " << "direction_x: " << p_player.dir.x << endl;
			data_file << "        " << "direction_y: " << p_player.dir.y << endl;
			data_file << "      " << "Input:" << endl;
			data_file << "        " << "input_x: " << p_player.input.x << endl;
			data_file << "        " << "input_y: " << p_player.input.y << endl;
			data_file << "      " << "Z_Velocity: " << p_player.zVel << endl;
			data_file << "      " << "Sprite_Iteration: " << p_player.iter << endl;
		}

		data_file << endl;

	}// END Print_To_Transform_YAML
}