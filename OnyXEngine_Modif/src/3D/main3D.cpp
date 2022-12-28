#include "../../myIncludes/game.hpp"

void	ftSideUpMenu3D(Game *game)
{
	DrawText("Side Up menu 3D", 10, 10, 14, LIGHTGRAY);
}

void	ftSideDownMenu3D(Game *Game)
{
	DrawText("Panel Side down 3D", 10, 10, 20, BLACK);
}

void	ftUpMenu3D(Game *game)
{
	DrawText("Panel Up 3D", 10, 10, 20, WHITE);
}

void ftMode3D(Game *game)
{
	// Initialization
	//--------------------------------------------------------------------------------------

	// Init Camera and windows

	MultipleCam3D	*allCameras = new MultipleCam3D;

	allCameras = ftInitCameras3D(game, allCameras);

	Texture text;
	CUBE3D	cube01;
	cube01.ftInitCube({0.0f, 1.0f, 0.0f}, {2.0f, 2.0f, 2.0f}, text, "Cube00");

	SetCameraMode(allCameras->camera00.camera3D, CAMERA_FREE); // Set a free camera mode

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

	//----------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())
	{
		game->mouse.pos = GetMousePosition();
		//--------------------------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&allCameras->camera00.camera3D);
		//** Drawning **//

		// Draw Workspace
		BeginTextureMode(allCameras->camera00.textForCam);
			ClearBackground(LIGHTGRAY);
			BeginMode3D(allCameras->camera00.camera3D);
	
				ftControlMainPanel(game, &cube01, allCameras);

			EndMode3D();

		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side up
		BeginTextureMode(allCameras->camera01.textForCam);
			ClearBackground(DARKGRAY);
			BeginMode2D(allCameras->camera01.camera2D);

				ftSideUpMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side down
		BeginTextureMode(allCameras->camera02.textForCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(allCameras->camera02.camera2D);

				ftSideDownMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel Up
		BeginTextureMode(allCameras->camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras->camera03.camera2D);

				ftUpMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw render textures to the screen for all cameras
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTextureRec(allCameras->camera00.textForCam.texture, allCameras->camera00.rectForCam, (Vector2){0, 40}, WHITE);
			DrawTextureRec(allCameras->camera01.textForCam.texture, allCameras->camera01.rectForCam, (Vector2){(float)game->screenWidth - 300.0f, 40}, WHITE);
			DrawTextureRec(allCameras->camera02.textForCam.texture, allCameras->camera02.rectForCam, (Vector2){(float)game->screenWidth - 300.0f, (float)game->screenHeight / 3 + 40}, WHITE);
			DrawTextureRec(allCameras->camera03.textForCam.texture, allCameras->camera03.rectForCam, (Vector2){0, 0}, WHITE);
			ftDrawBoarders(game);
			if (IsKeyDown(KEY_I))
			{
				DrawText("Free camera default controls:", 20, 60, 10, BLACK);
				DrawText("- Mouse Wheel to Zoom in-out", 20, 90, 10, BLACK);
				DrawText("- Mouse Wheel Pressed to Pan", 20, 100, 10, BLACK);
				DrawText("- Alt + Mouse Wheel Pressed to Rotate", 20, 120, 10, BLACK);
				DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 20, 140, 10, BLACK);
				DrawText("- Z to zoom to (0, 0, 0)", 20, 160, 10, BLACK);
			}
		EndDrawing();
	}
}
