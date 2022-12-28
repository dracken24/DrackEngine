#include "../../../myIncludes/game.hpp"

void	ftRunGameMode(Game *game, Menu menu, Player player, EnvItems **envItems,
			SquareProps **blocks, MultipleCam2D allCameras)
{
	Camera2D *tmpCam = &allCameras.camera00.camera;
	allCameras.camera00.camera.target = player.ftReturnPlayerPosition();

	// InitWindow(Game->screenWidth, Game->screenHeight, "Play");
	// SetTargetFPS(60);
	while (!WindowShouldClose() && game->ctMode == -1)
	{
		//** Drawning **//
		// Draw Play screen
		BeginTextureMode(allCameras.camera00.textForCam);
			ClearBackground(LIGHTGRAY);
			BeginMode2D(allCameras.camera00.camera);
				
				ftRoutine(game, &player, &menu, tmpCam, blocks, envItems);
				// ftKeyGestionBuildMode(Game);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel side up
		BeginTextureMode(allCameras.camera01.textForCam);
			ClearBackground(DARKGRAY);
			BeginMode2D(allCameras.camera01.camera);

				ftSideUpMenu2D(game, &player, blocks, envItems, &menu, &allCameras);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel side down
		BeginTextureMode(allCameras.camera02.textForCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(allCameras.camera02.camera);

				ftSideDownMenu2D(game, blocks, envItems, &allCameras);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw Control Panel Up
		BeginTextureMode(allCameras.camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras.camera03.camera);

			ftUpMenu2D(game, &player, blocks, envItems, &allCameras.camera03.camera);

			EndMode2D();
		EndTextureMode();

		//--------------------------------------------------------------------------------------//
		// Draw both views render textures to the screen side by side
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureRec(allCameras.camera00.textForCam.texture, allCameras.camera00.rectForCam, (Vector2){0, 40}, WHITE);
		DrawTextureRec(allCameras.camera01.textForCam.texture, allCameras.camera01.rectForCam, (Vector2){(float)game->screenWidth - 300.0f, 40}, WHITE);
		DrawTextureRec(allCameras.camera02.textForCam.texture, allCameras.camera02.rectForCam, (Vector2){(float)game->screenWidth - 300.0f, (float)game->screenHeight / 3 + 40}, WHITE);
		DrawTextureRec(allCameras.camera03.textForCam.texture, allCameras.camera03.rectForCam, (Vector2){0, 0}, WHITE);
		ftDrawBoarders(game);
		EndDrawing();
		ftSelectItemsTop(game, &allCameras.camera03.camera);
		game->ctStopAttack = 0;
	}
	//--------------------------------------------------------------------------------------//
	// CloseWindow();
	game->ctStopAttack = 1;
}
