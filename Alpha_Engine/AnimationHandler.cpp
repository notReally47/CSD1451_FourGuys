#include "pch.h"
#include "AnimationHandler.h"
#include "GSM.h"

namespace AnimationHandler {
	using namespace GameObjects;

	/*Get direction the player is facing and set according to the spritesheet row.*/
	void setTextureOffsetY(Character& player) {
		if (checkDirection(player, 1, 1)) {			//UPRIGHT
			player.pObjInst.tex_offset.y = 1.0f;
		}
		else if (checkDirection(player, 1, 0)) {	//UP
			player.pObjInst.tex_offset.y = 2.0f;
		}
		else if (checkDirection(player, 1, -1)) {	//UPLEFT
			player.pObjInst.tex_offset.y = 3.0f;
		}
		else if (checkDirection(player, 0, -1)) {	//LEFT
			player.pObjInst.tex_offset.y = 4.0f;
		}
		else if (checkDirection(player, -1, -1)) {	//DOWNLEFT
			player.pObjInst.tex_offset.y = 5.0f;
		}
		else if (checkDirection(player, -1, 0)) {	//DOWN
			player.pObjInst.tex_offset.y = 6.0f;
		}
		else if (checkDirection(player, -1, 1)) {	//DOWNRIGHT
			player.pObjInst.tex_offset.y = 7.0f;
		}
		else if (checkDirection(player, 0, 1)) {	//RIGHT
			player.pObjInst.tex_offset.y = 8.0f;
		}
	}

	/*Iterates through the spritesheets columns if the player is moving*/
	void setTextureOffsetX(Character& player) {
		if (player.pObjInst.flag) {
			if (GSM::gameTime >= 0.1f) {
				player.spriteIteration = (++player.spriteIteration % 10) ? player.spriteIteration : 0;
				GSM::gameTime = .0f;
			}
			player.pObjInst.tex_offset.x = static_cast<f32>(player.spriteIteration + 1);
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
			(player.pObjInst.tex_offset.x / 11.0f),
			(player.pObjInst.tex_offset.y / 8.0f));

		/*TRANSFORMATION (TRS)*/
		AEGfxSetTransform(player.pObjInst.transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(player.pObjInst.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}