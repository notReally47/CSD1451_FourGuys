#include "pch.h"
#include "AnimationHandler.h"
#include "GSM.h"

namespace AnimationHandler {
	using namespace GameObjects;

	/*Get direction the player is facing and set according to the spritesheet row.*/
	void setTextureOffsetY(Character& player) {
		if (checkDirection(player, 1, 1)) {			//FACING RIGHT
			player.pObjInst.tex_offset.y = 0.125f;
		}
		else if (checkDirection(player, 1, 0)) {	//FACING DOWNRIGHT
			player.pObjInst.tex_offset.y = 0.25f;
		}
		else if (checkDirection(player, 1, -1)) {	//FACING DOWN
			player.pObjInst.tex_offset.y = 0.375f;
		}
		else if (checkDirection(player, 0, -1)) {	//FACING DOWNLEFT
			player.pObjInst.tex_offset.y = 0.5f;
		}
		else if (checkDirection(player, -1, -1)) {	//FACING LEFT
			player.pObjInst.tex_offset.y = 0.625f;
		}
		else if (checkDirection(player, -1, 0)) {	//FACING UPLEFT
			player.pObjInst.tex_offset.y = 0.75f;
		}
		else if (checkDirection(player, -1, 1)) {	//FACING UP
			player.pObjInst.tex_offset.y = 0.875f;
		}
		else if (checkDirection(player, 0, 1)) {	//FACING UPRIGHT
			player.pObjInst.tex_offset.y = 0.0f;
		}
	}

	/*Iterates through the spritesheets columns if the player is moving*/
	void setTextureOffsetX(Character& player) {
		if (player.pObjInst.flag) {
			if (GSM::gameTime >= 0.1f) {
				player.spriteIteration = (++player.spriteIteration % 10) ? player.spriteIteration : 1;
				GSM::gameTime = .0f;
			}
			player.pObjInst.tex_offset.x = 1.0f / 11.0f * static_cast<f32>(player.spriteIteration);
		}
		else {
			player.pObjInst.tex_offset.x = .0f;
		}
	}

	/*Helper function to compare the x and y coordinates with 2 respective values.*/
	bool checkDirection(Character player, int a, int b) {
		int x = static_cast<int>(player.input.x);
		int y = static_cast<int>(player.input.y);
		return (x == a && y == b);
	}

	/*Set the texture offset and render the player. This will create the animation.*/
	void AnimateCharacter(Character& player) {
		/*Set texture*/
		setTextureOffsetX(player);
		setTextureOffsetY(player);
		AEGfxTextureSet(player.pObjInst.pObj->pTex,
			player.pObjInst.tex_offset.x,
			player.pObjInst.tex_offset.y);

		/*TRANSFORMATION (TRS)*/
		AEGfxSetTransform(player.pObjInst.transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(player.pObjInst.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}