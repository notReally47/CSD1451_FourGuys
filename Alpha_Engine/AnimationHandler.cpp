#include "pch.h"
#include "AnimationHandler.h"
#include "GSM.h"
#include <iostream>

namespace AnimationHandler {
	const static f32 JUMP_SPRITE = 0.3636f;
	using namespace GameObjects;

	/*Get direction the player is facing and set according to the spritesheet row.*/
	void setTextureOffsetY(ObjectInst& player, AEVec2& dir) {
		if (checkDirection(dir, 1, 1)) {			//FACING RIGHT
			player.tex_offset.y = 0.125f;
		}
		else if (checkDirection(dir, 1, 0)) {	//FACING DOWNRIGHT
			player.tex_offset.y = 0.25f;
		}
		else if (checkDirection(dir, 1, -1)) {	//FACING DOWN
			player.tex_offset.y = 0.375f;
		}
		else if (checkDirection(dir, 0, -1)) {	//FACING DOWNLEFT
			player.tex_offset.y = 0.5f;
		}
		else if (checkDirection(dir, -1, -1)) {	//FACING LEFT
			player.tex_offset.y = 0.625f;
		}
		else if (checkDirection(dir, -1, 0)) {	//FACING UPLEFT
			player.tex_offset.y = 0.75f;
		}
		else if (checkDirection(dir, -1, 1)) {	//FACING UP
			player.tex_offset.y = 0.875f;
		}
		else if (checkDirection(dir, 0, 1)) {	//FACING UPRIGHT
			player.tex_offset.y = 0.0f;
		}
	}

	/*Iterates through the spritesheets columns if the player is moving*/
	void setTextureOffsetX(ObjectInst& player, int& spriteIter) {
		if (player.flag & Enum::FLAG::JUMPING) 
			player.tex_offset.x = JUMP_SPRITE;

		else if (player.flag & Enum::FLAG::ACTIVE) {
			if (GSM::gameTime >= 0.1f) {
				spriteIter = (++spriteIter % 10) ? spriteIter : 1;
				GSM::gameTime = .0f;
			}
			player.tex_offset.x = 1.0f / 11.0f * static_cast<f32>(spriteIter);
		}
		else {
			player.tex_offset.x = .0f;
		}
	}

	/*Helper function to compare the x and y coordinates with 2 respective values.*/
	bool checkDirection(AEVec2& dir, int a, int b) {
		return (static_cast<int>(dir.x) == a && static_cast<int>(dir.y) == b);
	}

	/*Set the texture offset and render the player. This will create the animation.*/
	void AnimateCharacter(Character& player) {
		/*Set texture*/
		setTextureOffsetX(*player.pObjInst, player.spriteIteration);
		setTextureOffsetY(*player.pObjInst, player.dir);
		AEGfxTextureSet(player.pObjInst->pObj->pTex,
						player.pObjInst->tex_offset.x,
						player.pObjInst->tex_offset.y);

		AEGfxSetTransform(GameObjects::ConvertIsometric(*player.pObjInst).m);

		/*DRAW MESH*/
		AEGfxMeshDraw(player.pObjInst->pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}