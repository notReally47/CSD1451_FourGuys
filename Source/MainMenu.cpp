#include "PCH.h"
#include "InputManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace GSM
{
	AEGfxVertexList* pMesh1{ 0 }, * pMesh2{ 0 }, * pMesh3{ 0 };

	s32 mouseX{}, mouseY{};
	char strBuffer[10];
	char strBuffer2[10];
	char strBuffer3[10];

	/*LOAD ASSETS*/
	void MainMenu::MainMenu_Load()
	{

	}
	/*LOAD INITIAL DATA*/
	void MainMenu::MainMenu_Init()
	{
		memset(strBuffer, 0, 10 * sizeof(char));
		sprintf_s(strBuffer, "Start");
		memset(strBuffer2, 0, 10 * sizeof(char));
		sprintf_s(strBuffer2, "Option");
		memset(strBuffer3, 0, 10 * sizeof(char));
		sprintf_s(strBuffer3, "Exit");

		AESysSetWindowTitle("Main Menu");

		// Informing the library that we're about to start adding triangles
		AEGfxMeshStart();
		// This shape has 2 triangles that makes up a square
		// Color parameters represent colours as ARGB
		// UV coordinates to read from loaded textures
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);

		// Saving the mesh (list of triangles) in pMesh
		pMesh1 = AEGfxMeshEnd();

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		pMesh2 = AEGfxMeshEnd();

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		pMesh3 = AEGfxMeshEnd();
	}

	void MainMenu::MainMenu_Update()
	{
		using namespace Enum;
		/*UPDATE LOGIC*/
		IM::ExitGame(GSM::next);
		if (IM::buttonClick(mouseX, mouseY, 350.f, 175.f))
		{
			std::cout << "hi\n";
			GSM::next = GAME_STATES::LEVEL2;
		}
		if (IM::buttonClick(mouseX, mouseY, 350.f, 375.f))
		{
			GSM::next = Enum::GS_QUIT;
		}
	}

	/*RENDERING*/
	void MainMenu::MainMenu_Draw()
	{
		// Set the background to black.
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set the tint to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 100.f, 50.f);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0.f);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 0.f, 0.f);
		// Concatenate the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to apply onto the vertices
		// of the mesh that we are choose to draw in the next line.
		AEGfxSetTransform(transform.m);
		// With the above settings, draw the mesh.
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate2 = { 0 };
		AEMtx33Trans(&translate2, 0.f, 100.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate2, &transform);
		// Choose the transform to apply onto the vertices
		// of the mesh that we are choose to draw in the next line.
		AEGfxSetTransform(transform.m);
		// With the above settings, draw the mesh.
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);

		AEMtx33 translate3 = { 0 };
		AEMtx33Trans(&translate3, 0.f, -100.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate3, &transform);
		// Choose the transform to apply onto the vertices
		// of the mesh that we are choose to draw in the next line.
		AEGfxSetTransform(transform.m);
		// With the above settings, draw the mesh.
		AEGfxMeshDraw(pMesh3, AE_GFX_MDM_TRIANGLES);

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(fontId, strBuffer, -0.055f, 0.3f, 2.0f, 0.0f, 0.f, 0.f);
		AEGfxPrint(fontId, strBuffer2, -0.08f, -0.02f, 2.0f, 0.0f, 0.f, 0.f);
		AEGfxPrint(fontId, strBuffer3, -0.05f, -0.35f, 2.0f, 0.0f, 0.0f, 0.0f);
	}

	/*CLEAN UP DATA (SAVE/RESET ETC)*/
	void MainMenu::MainMenu_Free()
	{
		AEGfxMeshFree(pMesh1);
		AEGfxMeshFree(pMesh2);
		AEGfxMeshFree(pMesh3);
	}

	/*UNLOADS ASSETS*/
	void MainMenu::MainMenu_Unload()
	{
	}
}
