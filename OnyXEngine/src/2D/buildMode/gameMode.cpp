#include "../../../myIncludes/game.hpp"

void	ftRunGameMode(Game *Game, Menu menu, Player player, EnvItems envItems,
			Props blocks, MultipleCam2D allCameras)
{
	Camera2D *tmpCam = &allCameras.camera00.camera;
	allCameras.camera00.camera.target = player.ftReturnPlayerPosition();

	// InitWindow(Game->screenWidth, Game->screenHeight, "Play");
	// SetTargetFPS(60);
	while (!WindowShouldClose() && Game->ctMode == -1)
	{
		//** Drawning **//
		// Draw Play screen
		BeginTextureMode(allCameras.camera00.textForCam);
			ClearBackground(LIGHTGRAY);
			BeginMode2D(allCameras.camera00.camera);
				
				ftRoutine(Game, &player, &menu, tmpCam, &blocks, &envItems);
				// ftKeyGestionBuildMode(Game);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel side up
		BeginTextureMode(allCameras.camera01.textForCam);
			ClearBackground(DARKGRAY);
			BeginMode2D(allCameras.camera01.camera);

				ftSideUpMenu2D(Game, &player, &menu, &allCameras);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel side down
		BeginTextureMode(allCameras.camera02.textForCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(allCameras.camera02.camera);

				ftSideDownMenu2D(Game, &allCameras.camera02.camera);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel Up
		BeginTextureMode(allCameras.camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras.camera03.camera);

			ftUpMenu2D(Game, &allCameras.camera03.camera);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw both views render textures to the screen side by side
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureRec(allCameras.camera00.textForCam.texture, allCameras.camera00.rectForCam, (Vector2){0, 40}, WHITE);
		DrawTextureRec(allCameras.camera01.textForCam.texture, allCameras.camera01.rectForCam, (Vector2){(float)Game->screenWidth - 300.0f, 40}, WHITE);
		DrawTextureRec(allCameras.camera02.textForCam.texture, allCameras.camera02.rectForCam, (Vector2){(float)Game->screenWidth - 300.0f, (float)Game->screenHeight / 3 + 40}, WHITE);
		DrawTextureRec(allCameras.camera03.textForCam.texture, allCameras.camera03.rectForCam, (Vector2){0, 0}, WHITE);
		ftDrawBoarders(Game);
		EndDrawing();
		ftSelectItemsTop(Game, &allCameras.camera03.camera);
		Game->ctStopAttack = 0;
	}
	//--------------------------------------------------------------------------------------//
	// CloseWindow();
	Game->ctStopAttack = 1;
}
