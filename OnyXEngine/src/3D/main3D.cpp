#include "../../myIncludes/game.hpp"

// Fonction Raylib modified for change grid color
static void ftDrawGrid(int slices, float spacing)
{
	int halfSlices = slices / 2;

	rlBegin(RL_LINES);
	for (int i = -halfSlices; i <= halfSlices; i++)
	{
		if (i == 0)
		{
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
		}
		else
		{
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
		}

		rlVertex3f((float)i * spacing, 0.0f, (float)-halfSlices * spacing);
		rlVertex3f((float)i * spacing, 0.0f, (float)halfSlices * spacing);

		rlVertex3f((float)-halfSlices * spacing, 0.0f, (float)i * spacing);
		rlVertex3f((float)halfSlices * spacing, 0.0f, (float)i * spacing);
	}
	rlEnd();
}

void	ftSideMenu3D(Game *Game)
{
	// ftMouseControl(Game);
	DrawText("Side menu 3D", 10, 10, 14, LIGHTGRAY);
}

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

	// Define the camera to look into our 3d world
	Camera3D	camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
	RenderTexture	playing = LoadRenderTexture(game->screenWidth - 300, game->screenHeight - 40);
	Rectangle		splitScreenRectPlay = {0.0f, 0.0f, (float)playing.texture.width, (float)-playing.texture.height};

	// Camera panel side up
	Camera2D	camSideUp = { 0 };
	camSideUp = {0};
	camSideUp.target = {0, 0};
	camSideUp.offset = (Vector2){0.0f, 0.0f};
	camSideUp.rotation = 0.0f;
	camSideUp.zoom = 1.0f;
	RenderTexture	textSideUpCam = LoadRenderTexture(300, game->screenHeight / 3);
	Rectangle 		rectSideUpCam = {0.0f, 0.0f, (float)textSideUpCam.texture.width, (float)-textSideUpCam.texture.height};

	// Camera panel side down
	Camera2D	camSideDown = { 0 };
	camSideDown = {0};
	camSideDown.target = {0, 0};
	camSideDown.offset = (Vector2){0.0f, 0.0f};
	camSideDown.rotation = 0.0f;
	camSideDown.zoom = 1.0f;
	RenderTexture	textSideDownCam = LoadRenderTexture(300, game->screenHeight / 3* 2 - 40);
	Rectangle 		rectSideDownCam = {0.0f, 0.0f, (float)textSideDownCam.texture.width, (float)-textSideDownCam.texture.height};

	// Camera panel up
	Camera2D	camUp = { 0 };
	camUp = {0};
	camUp.target = {0, 0};
	camUp.offset = (Vector2){0.0f, 0.0f};
	camUp.rotation = 0.0f;
	camUp.zoom = 1.0f;
	RenderTexture	textUpCam = LoadRenderTexture(game->screenWidth, 40);
	Rectangle 		rectUpCam = {0.0f, 0.0f, (float)textUpCam.texture.width, (float)-textUpCam.texture.height};

	Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
	Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

	Ray 			ray = {0}; // Picking line ray

	RayCollision	collision = {0};

	SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode


	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

	//----------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())
	{
		//--------------------------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera);
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (!collision.hit)
			{
				Vector2 pos = GetMousePosition();
				pos.x += 150;
				pos.y -= 23;
				ray = GetMouseRay(pos, camera);

				// Check collision between ray and box
				collision = GetRayCollisionBox(ray,
				(BoundingBox){(Vector3){cubePosition.x - cubeSize.x / 2, cubePosition.y - cubeSize.y / 2, cubePosition.z - cubeSize.z / 2},
				(Vector3){cubePosition.x + cubeSize.x / 2, cubePosition.y + cubeSize.y / 2, cubePosition.z + cubeSize.z / 2}});
			}
			else
			collision.hit = false;
		}

		if (IsKeyDown('Z'))
			camera.target = (Vector3){0.0f, 0.0f, 0.0f};
		//** Drawning **//

		// Draw Workspace
		BeginTextureMode(playing);
			ClearBackground(LIGHTGRAY);

			BeginMode3D(camera);
				if (collision.hit)
                {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

                    DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
                }
                else
                {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, PURPLE);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
                }

				ftDrawGrid(10, 1.0f);

			EndMode3D();
			if (IsKeyDown(KEY_I))
			{
				DrawRectangle(10, 10, 320, 133, Fade(DARKGRAY, 0.5f));
				DrawRectangleLines(10, 10, 320, 133, DARKGRAY);
			}

		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side up
		BeginTextureMode(textSideUpCam);
			ClearBackground(DARKGRAY);
			BeginMode2D(camSideUp);

				ftSideUpMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side down
		BeginTextureMode(textSideDownCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(camSideDown);

				ftSideDownMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel Up
		BeginTextureMode(textUpCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(camUp);

				ftUpMenu3D(game);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw render textures to the screen for all cameras
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTextureRec(playing.texture, splitScreenRectPlay, (Vector2){0, 40}, WHITE);
			DrawTextureRec(textSideUpCam.texture, rectSideUpCam, (Vector2){(float)game->screenWidth - 300.0f, 40}, WHITE);
			DrawTextureRec(textSideDownCam.texture, rectSideDownCam, (Vector2){(float)game->screenWidth - 300.0f, (float)game->screenHeight / 3 + 40}, WHITE);
			DrawTextureRec(textUpCam.texture, rectUpCam,(Vector2){0, 0}, WHITE);
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
