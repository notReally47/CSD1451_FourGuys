#pragma once
#include "PCH.h"
#include <string>					// For std::string
#include <vector>					// For std::vector

using namespace std;

namespace FM
{
	struct Export : public OM::ObjectInst, public OM::Character
	{
		void					Extract_Transform_Data_Out(vector<OM::ObjectInst> vOI, OM::Character p_player, const string level_number);
	};

	struct Import : public OM::ObjectInst, public OM::Character
	{
		vector<OM::Object>		vO;
		vector<OM::ObjectInst>	vOI;

		vector<OM::Object>*		Load_Shape_From_YAML(const string level_number);
		vector<OM::ObjectInst>* Load_Transform_From_YAML(const string level_number, vector<OM::Object>& vO);
		OM::Character*			Load_Player_Stats_From_YAML(const string level_number);
	};

	void Option_Change(vector<OM::ObjectInst>& vOI);
	void Init_Player(OM::ObjectInst* vOI, OM::Character* sCHARACTER, OM::Character& p_player);
}
