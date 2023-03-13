/*!***********************************************************************
  \file   FileManager.cpp
  \authors	muhammadfaliq.b@digipen.edu
  
  \brief 
  This file contains the implementation of the FileManager class

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"					// For Precompiled Headers
#include "FileManager.h"			// For Class GameData
#include <string>					// For std::string
#include <sstream>					// For std::stringstream
#include <fstream>					// For std::istream/std::ostream
#include <vector>					// For std::vector
#include <yaml-cpp/yaml.h>			// For Parsing YAML Files

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

vector<OM::Object>		FM::GameData::vO;
vector<OM::ObjectInst>	FM::GameData::vOI;
vector<OM::ObjectLayer> FM::GameData::vOL;
vector<OM::Platform>	FM::GameData::platforms;
vector<OM::Portraits>	FM::GameData::portraits;
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

	using enum LAYER;
	using enum TYPE;


	// Load Shape From Data Functions
	void operator >> (const YAML::Node& node, OM::Object& Object) {
		string	type{}, flag{};
		f32		uv01{ 0 }, uv02{ 0 }, uv03{ 0 }, uv04{ 0 }, uv05{ 0 }, uv06{ 0 };

		// Extract Object Type
		node["Type"] >> type;
		if (type == "Player")
			Object.type = PLAYER;
		else if (type == "Floor")
			Object.type = FLOOR;
		else if (type == "Wall")
			Object.type = WALL;
		else if (type == "Decoration")
			Object.type = DECO;
		else if (type == "Portrait")
			Object.type = PORTRAIT;
		else if (type == "Landscape")
			Object.type = LANDSCAPE;
		else if (type == "Stairs")
			Object.type = STAIRS;
		else if (type == "Bridge")
			Object.type = BRIDGE;

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
		string file_name{ "./Resource/Data/Start_Data/Shape_Data.yml" };
		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);

		OM::Object Object;

		for (unsigned i = 0; i < doc.size(); i++) {
			doc[i] >> Object;
			FM::GameData::vO.push_back(Object);
		}
	}// END LoadShapeFromFile



	// Load Transform From Data Functions
	void operator >> (const YAML::Node& node, OM::ObjectInst& ObjectInstance) {
		string			type_string{};
		TYPE			type{ PLAYER };

		// Extract Object Type
		node["Type"] >> type_string;
		if (type_string == "Player")
			type = PLAYER;
		else if (type_string == "Floor")
			type = FLOOR;
		else if (type_string == "Wall")
			type = WALL;
		else if (type_string == "Decoration")
			type = DECO;
		else if (type_string == "Portrait")
			type = PORTRAIT;
		else if (type_string == "Landscape")
			type = LANDSCAPE;
		else if (type_string == "Stairs")
			type = STAIRS;
		else if (type_string == "Bridge")
			type = BRIDGE;

		// Set Object
		for (size_t i{ 0 }; i < FM::GameData::vO.size(); i++)
			if (FM::GameData::vO[i].type == type)
				ObjectInstance.pO = &FM::GameData::vO[i];

		// Extract Flag
		node["Layer"] >> ObjectInstance.layer;
		node["Flag"] >> ObjectInstance.flag;

		// Extract Texture Offset
		node["Texture_Offset"]["x_offset"]		>> ObjectInstance.texture.x;
		node["Texture_Offset"]["y_offset"]		>> ObjectInstance.texture.y;

		// Extract Transformation
		node["Transformation"]["scale_x"]		>> ObjectInstance.transf.m[0][0];
		node["Transformation"]["shear_x"]		>> ObjectInstance.transf.m[0][1];
		node["Transformation"]["position_x"]	>> ObjectInstance.transf.m[0][2];
		node["Transformation"]["shear_y"]		>> ObjectInstance.transf.m[1][0];
		node["Transformation"]["scale_y"]		>> ObjectInstance.transf.m[1][1];
		node["Transformation"]["position_y"]	>> ObjectInstance.transf.m[1][2];
		node["Transformation"]["elapsed"]		>> ObjectInstance.transf.m[2][0];
		node["Transformation"]["empty"]			>> ObjectInstance.transf.m[2][1];
		node["Transformation"]["position_z"]	>> ObjectInstance.transf.m[2][2];
		//node["Pair"] >> ObjectInstance.pair;

	}// END operator >> overload for Load Transform



	void GameData::LoadTransformFromFile() {
		// YAML file to read from
		string file_name{};

		switch (GSM::current) {
		case GAME_STATES::LEVEL1:
			file_name = "./Resource/Data/Start_Data/Transform_Data.yml";
			break;
		case GAME_STATES::LOAD:
			file_name = "./Resource/Data/Saved_Data/HopWards_Saved_Data.yml";
			break;
		}

		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);

		OM::Platform	Platform{};
		OM::Portraits	Portraits{};
		OM::ObjectInst	ObjectInstance{};

		for (unsigned i = 0; i < doc.size(); i++) {
			doc[i] >> ObjectInstance;
			FM::GameData::vOI.push_back(ObjectInstance);
			if (ObjectInstance.pO->type == STAIRS) {
				Platform.pOI = &FM::GameData::vOI[i];
				FM::GameData::platforms.push_back(Platform);
			}
			
			if (ObjectInstance.pO->type == PORTRAIT) {
				Portraits.pOI = &FM::GameData::vOI[i];
				FM::GameData::portraits.push_back(Portraits);
			}

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
		string file_name{};

		switch (GSM::current) {
		case GAME_STATES::LEVEL1:
			file_name = "./Resource/Data/Start_Data/Transform_Data.yml";
			break;
		case GAME_STATES::LOAD:
			file_name = "./Resource/Data/Saved_Data/HopWards_Saved_Data.yml";
			break;
		}

		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);
		OM::Character Player{};
		doc[0] >> Player;

		GameData::player = Player;
	}// END LoadPlayerStatsFromFile



	// Load Layer From Data Functions
	void operator >> (const YAML::Node& node, OM::ObjectLayer& ObjectLayer) {

		string layer{};

		// Extract Layer Data
		node["Layer"] >> layer;
		if (layer == "Ground")
			ObjectLayer.layer = GROUND;
		else if (layer == "Floor01")
			ObjectLayer.layer = FLOOR01;
		else if (layer == "Floor02")
			ObjectLayer.layer = FLOOR02;
		else if (layer == "Floor03")
			ObjectLayer.layer = FLOOR03;
		else if (layer == "Floor04")
			ObjectLayer.layer = FLOOR04;
		else if (layer == "Floor05")
			ObjectLayer.layer = FLOOR05;
		else if (layer == "Floor06")
			ObjectLayer.layer = FLOOR06;
		else if (layer == "Floor07")
			ObjectLayer.layer = FLOOR07;
		else if (layer == "Floor08")
			ObjectLayer.layer = FLOOR08;
		else if (layer == "Floor09")
			ObjectLayer.layer = FLOOR09;
		else if (layer == "Floor10")
			ObjectLayer.layer = FLOOR10;
		else if (layer == "Floor11")
			ObjectLayer.layer = FLOOR11;
		else if (layer == "Floor12")
			ObjectLayer.layer = FLOOR12;
		else if (layer == "Floor13")
			ObjectLayer.layer = FLOOR13;
		else if (layer == "Floor14")
			ObjectLayer.layer = FLOOR14;
		else if (layer == "Floor15")
			ObjectLayer.layer = FLOOR15;
		else if (layer == "Floor16")
			ObjectLayer.layer = FLOOR16;

		// Extract Grid Data
		for (size_t i{ 0 }; i < 36; ++i)
			node["Grid"][i] >> ObjectLayer.data[i];

	}// END operator >> overload Object Layer



	void GameData::LoadLayersFromFile() {
		// YAML file to read from
		string file_name{};

		switch (GSM::current) {
		case GAME_STATES::LEVEL1:
			file_name = "./Resource/Data/Start_Data/Layer_Data.yml";
			break;
		case GAME_STATES::LOAD:
			file_name = "./Resource/Data/Saved_Data/HopWards_Saved_Grid.yml";
			break;
		}

		ifstream ifs(file_name);
		if (!ifs.good())
			ifs.open("." + file_name);

		YAML::Parser parser(ifs);
		YAML::Node doc;
		parser.GetNextDocument(doc);
		for (unsigned i = 0; i < doc.size(); i++) {
			OM::ObjectLayer ObjectLayer{};
			doc[i] >> ObjectLayer;
			FM::GameData::vOL.push_back(ObjectLayer);
		}
	}// END LoadLayersFromFile



}// END Import



/*!***********************************************************************
           4857784  75   49  654933     586    242553   633792            
           82       763 664  48   28   47 46   98   62    62             
           62572     42424   25   94  35   29  73   39    36              
           78        27567   492745   62   38  368929     76              
           89       557 489  77        27 67   42   85    32              
           6328975  35   96  49         585    24   77    47              
*************************************************************************/
namespace FM
{



	// Save Progress Functions
	ostream& operator <<(ostream& saveFile, OM::ObjectInst const& objectInstance) {

		// Print data of object to file
		switch (objectInstance.pO->type) {
		case PLAYER:
			saveFile << "- " << "Type: " << "Player" << endl;
			break;
		case FLOOR:
			saveFile << "- " << "Type: " << "Floor" << endl;
			break;
		case WALL:
			saveFile << "- " << "Type: " << "Wall" << endl;
			break;
		case DECO:
			saveFile << "- " << "Type: " << "Decoration" << endl;
			break;
		case PORTRAIT:
			saveFile << "- " << "Type: " << "Portrait" << endl;
			break;
		case LANDSCAPE:
			saveFile << "- " << "Type: " << "Landscape" << endl;
			break;
		case STAIRS:
			saveFile << "- " << "Type: " << "Stairs" << endl;
			break;
		case BRIDGE:
			saveFile << "- " << "Type: " << "Bridge" << endl;
			break;
		case BUTTON:
			saveFile << "- " << "Type: " << "Button" << endl;
			break;
		case BACKGROUND:
			saveFile << "- " << "Type: " << "Background" << endl;
			break;
		case BUBBLE:
			saveFile << "- " << "Type: " << "Bubble" << endl;
			break;
		}
		
		saveFile << "  "	<< "Layer: "			<< objectInstance.layer				<< endl;
		saveFile << "  "	<< "Flag: "				<< objectInstance.flag				<< endl;
		saveFile << "  "	<< "Texture_Offset:"										<< endl;
		saveFile << "    "	<< "x_offset: "			<< objectInstance.texture.x			<< endl;
		saveFile << "    "	<< "y_offset: "			<< objectInstance.texture.y			<< endl;
		saveFile << "  "	<< "Transformation:"										<< endl;
		saveFile << "    "	<< "scale_x: "			<< objectInstance.transf.m[0][0]	<< endl;
		saveFile << "    "	<< "shear_x: "			<< objectInstance.transf.m[0][1]	<< endl;
		saveFile << "    "	<< "position_x: "		<< objectInstance.transf.m[0][2]	<< endl;
		saveFile << "    "	<< "shear_y: "			<< objectInstance.transf.m[1][0]	<< endl;
		saveFile << "    "	<< "scale_y: "			<< objectInstance.transf.m[1][1]	<< endl;
		saveFile << "    "	<< "position_y: "		<< objectInstance.transf.m[1][2]	<< endl;
		saveFile << "    "	<< "elapsed: "			<< objectInstance.transf.m[2][0]	<< endl;
		saveFile << "    "	<< "empty: "			<< objectInstance.transf.m[2][1]	<< endl;
		saveFile << "    "	<< "position_z: "		<< objectInstance.transf.m[2][2]	<< endl;
		saveFile << "  "	<< "Pair: "				<< 0								<< endl;

		// Player Stats
		if (objectInstance.pO->type == PLAYER) {
			saveFile << "  "	<< "Direction:"											<< endl;
			saveFile << "    "	<< "direction_x: "		<< FM::GameData::player.dir.x	<< endl;
			saveFile << "    "	<< "direction_y: "		<< FM::GameData::player.dir.y	<< endl;
			saveFile << "  "	<< "Input:"												<< endl;
			saveFile << "    "	<< "input_x: "			<< FM::GameData::player.input.x << endl;
			saveFile << "    "	<< "input_y: "			<< FM::GameData::player.input.y << endl;
			saveFile << "  "	<< "Z_Velocity: "		<< FM::GameData::player.zVel	<< endl;
			saveFile << "  "	<< "Sprite_Iteration: " << FM::GameData::player.iter	<< endl;
		}

		saveFile << endl;

		return saveFile;

	}// END operator << overload Object Instance



	ostream& operator << (ostream& saveFile, OM::ObjectLayer const& objectLayer) {
		int count{ 0 };

		saveFile << "- Layer: "; 
		switch (objectLayer.layer) {
		case 0:
			saveFile << "Ground" << endl;
			break;
		case 1:
			saveFile << "Floor01" << endl;
			break;
		case 2:
			saveFile << "Floor02" << endl;
			break;
		case 3:
			saveFile << "Floor03" << endl;
			break;
		case 4:
			saveFile << "Floor04" << endl;
			break;
		case 5:
			saveFile << "Floor05" << endl;
			break;
		}

		saveFile << "  Grid: [";
		for (auto i : objectLayer.data) {
			if (count == ((sizeof(objectLayer.data) / sizeof(i)) - 1)) {
				saveFile << i << ']' << endl;
				break;
			}
			else if (0 == ((count + 1)) % 6)
				saveFile << i << ',';
			else
				saveFile << i << ", ";

			if ((0 == ((count + 1) % 6)) && (count < (sizeof(objectLayer.data)))) {
				saveFile << endl;
				saveFile << "         ";
			}

			count++;
		}

		//saveFile << "  Offset: "		<< '[' << objectLayer.offset.x << ", " << objectLayer.offset.y << ']'	<< endl;
		//saveFile << "  Transparency: "	<< objectLayer.transp													<< endl;
		saveFile << endl;
		return saveFile;

	}// END operator << overload Object Layer



	void GameData::SaveProgress() {
		/* Save Object Data */

		// file name to extract to 
		string outFile{ "./Resource/Data/Saved_Data/HopWards_Saved_Data.yml" };

		// out file to extract data to
		ofstream dataFile(outFile);
		if (!dataFile.good())
			dataFile.open("." + outFile);

		// if out file successfully opened
		if (dataFile.is_open()) {

			// iterate through data vector
			for (size_t i{ 0 }; i < FM::GameData::vOI.size(); ++i)
				dataFile << FM::GameData::vOI[i];						// print data of object to file

			dataFile.close();											// close file
		}
		else {
			cout << "Error Opening File: " << outFile << endl;			// if out file can't be opened
			exit(1);													// exit program
		}

		
		dataFile.clear();


		/* Save Object Layer Data*/

		// file name to extract to 
		outFile = "./Resource/Data/Saved_Data/HopWards_Saved_Grid.yml";

		// out file to extract data to
		dataFile.open(outFile);
		if (!dataFile.good())
			dataFile.open("." + outFile);

		// if out file successfully opened
		if (dataFile.is_open()) {

			// iterate through data vector
			for (size_t i{ 0 }; i < FM::GameData::vOL.size(); ++i)
				dataFile << FM::GameData::vOL[i];						// print data of object to file

			dataFile.close();											// close file
		}
		else {
			cout << "Error Opening File: " << outFile << endl;			// if out file can't be opened
			exit(1);													// exit program
		}
	}// END SaveProgress



}// END Export




namespace FM {



	// Scaling Stuff
	void GameData::OptionChange() {
		// Scale Value
		f32 scaling = 1920.0f / static_cast<f32>(AEGetWindowWidth());
		size_t count = 3;

		//Set Object to ObjectInstance
		for (size_t i{ 0 }; i < FM::GameData::vOI.size(); i++)
			for (size_t j{ 0 }; j < count * 3; j++)
				FM::GameData::vOI[i].transf.m[j / count][j % count] /= scaling;

	}// END Init_Object_From_Vector



}// END Misc