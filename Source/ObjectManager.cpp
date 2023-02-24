#include "PCH.h"
#include <vector>

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace OM
{
	/*DEFINES*/
	s8						fontId;
	const static f32		JUMP_SPRITE = 4.0f / 11.0f;
	using namespace			Enum;

	Object::Object()
	{
		this->pTex			= nullptr;
		this->pMesh			= nullptr;
		this->type			= 0;
		this->width			= .0f;
		this->length		= .0f;
		this->height		= .0f;
	}

	Object::~Object()
	{

	}

	// Scale of Object Instance in width
	f32& ObjectInst::GetScaleX()
	{ 
		return this->transform.m[0][0]; // check if this is used anywhere
	} 

	// Position X in world screen coordinates
	f32& ObjectInst::GetPosX()
	{ 
		return this->transform.m[0][2];
	}

	f32 ObjectInst::GetPosX() const
	{ 
		return this->transform.m[0][2];
	}

	// Scale of Object Instance in height
	f32& ObjectInst::GetScaleY()
	{ 
		return this->transform.m[1][1];
	}

	// Position Y in world screen coordinates
	f32& ObjectInst::GetPosY()
	{
		return this->transform.m[1][2];
	}

	f32 ObjectInst::GetPosY() const
	{ 
		return this->transform.m[1][2];
	}

	// Elapsed time of animation
	f32& ObjectInst::GetElapsed()
	{ 
		return this->transform.m[2][0];
	}

	// Speed of the player's movement
	f32& ObjectInst::GetPlayerSpeed()
	{ 
		return this->transform.m[2][1];
	}

	// Elevation of the Object Instance
	f32& ObjectInst::GetPosZ()
	{ 
		return this->transform.m[2][2];
	}

	f32 ObjectInst::GetPosZ() const
	{ 
		return this->transform.m[2][2];
	}

	AEVec2 ObjectInst::GetPosXY()
	{ 
		return { this->GetPosX(), this->GetPosY() }; 
	}

	int Character::CheckDirection()
	{
		int x{ static_cast<int>(this->dir.x) }, y{ static_cast<int>(this->dir.y) };
		return	(x > 0) ? (y > 0) ? UP : (y) ? static_cast<int>(RIGHT) : UPRIGHT :
			(x) ? (y > 0) ? LEFT : (y) ? static_cast<int>(DOWN) : DOWNLEFT :
			(y > 0) ? static_cast<int>(UPLEFT) : DOWNRIGHT;
	}

	AEVec2& Character::GetOffset()
	{ 
		return this->pObjInst->tex_offset;
	}

	/*Get direction the player is facing and set according to the spritesheet row.*/
	void Character::SetOffsetY()
	{
		if (this->pObjInst->flag & ACTIVE)
			this->GetOffset().y = 0.125f * static_cast<f32>(this->CheckDirection());
	}

	/*Iterates through the spritesheets columns if the player is moving*/
	void Character::SetOffsetX()
	{
		this->pObjInst->GetElapsed() += gameTime;
		if (this->pObjInst->flag & JUMPING)
			this->GetOffset().x = JUMP_SPRITE;
		else if (this->pObjInst->flag & ACTIVE)
		{
			if (this->pObjInst->GetElapsed() >= 0.1f)
				this->spriteIteration = (this->pObjInst->GetElapsed() = .0f, ++this->spriteIteration % 10) ? this->spriteIteration : 1;
			this->GetOffset().x = static_cast<f32>(this->spriteIteration) / 11.0f;
		}
		else
			this->GetOffset().x = .0f;
	}

	AEVec2* GetVerticesXY(const ObjectInst& obj, int& count)
	{
		count = 4;

		AEVec2* xyCoords = { new AEVec2[count] };
		xyCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top right
		xyCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top left
		xyCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot right
		xyCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot left

		//TODO: Any rotatation 
		return xyCoords;
	}

	AEVec2* GetVerticesYZ(const ObjectInst& obj, int& count)
	{
		count = 4;
		AEVec2* yzCoords = { new AEVec2[count] };
		yzCoords[0] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top right
		yzCoords[1] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top left
		yzCoords[2] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot right
		yzCoords[3] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot left

		//TODO: Any rotatation 
		return yzCoords;
	}

	AEVec2* GetVerticesXZ(const ObjectInst& obj, int& count)
	{
		if (1) { //TODO: Change to check if not a staircase
			count = 4;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top right
			xzCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top left
			xzCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot right
			xzCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot left
			return xzCoords;
		}
		else {
			count = 3;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot left

			xzCoords[1] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() + (2 * obj.pObj->height) / 3 }; // top left

			xzCoords[2] = AEVec2{ obj.GetPosX() + (2 * obj.pObj->width) / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot right

			return xzCoords;
		}
	}

	AEMtx33 ConvertIsometric(const ObjectInst& obj)
	{
		AEMtx33 transform = obj.transform;
		transform.m[0][2] = obj.GetPosX() - obj.GetPosY();
		transform.m[1][2] = 0.5f * obj.GetPosX() + 0.5f * obj.GetPosY() + obj.GetPosZ();
		return transform;
	}
}
