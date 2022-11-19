#include "../../myIncludes/game.hpp"
#include <string.h>

void	ftDeleteAndFree(Game *game, Player *player, Props *blocks,
			EnvItems *envItems, MultipleCam2D *allCameras);

void	ftInitBlocks(Props *blocks, EnvItems *envItems)
{
	Texture tmp;

	blocks->ftInitSquareProps(5, "blocks");
	blocks->ftAddProps((Vector2){200, 200}, (Vector2){24, 24}, BLUE, true, 0, "blocks", "blocks0");
	blocks->ftAddProps((Vector2){160, 200}, (Vector2){24, 24}, RED, true, 1, "blocks", "blocks1");
	blocks->ftAddProps((Vector2){120, 200}, (Vector2){24, 24}, YELLOW, true, 2, "blocks", "blocks2");
	blocks->ftAddProps((Vector2){240, 200}, (Vector2){24, 24}, PINK, true, 3, "blocks", "blocks3");
	blocks->ftAddProps((Vector2){80, 200}, (Vector2){24, 24}, PURPLE, true, 4, "blocks", "blocks4");

	envItems->ftNewEnvItem(9);
	envItems->ftInitEnvitem((Vector2){0, 0}, (Vector2){1000, 400}, 0, LIGHTGRAY, tmp, 0, "Platform0");
	envItems->ftInitEnvitem((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 1, "Platform1");
	envItems->ftInitEnvitem((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 2, "Platform2");
	envItems->ftInitEnvitem((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3, "Platform3");
	envItems->ftInitEnvitem((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 4, "Platform4");
	envItems->ftInitEnvitem((Vector2){-850, 350}, (Vector2){700, 205}, 1, GRAY, tmp, 5, "Platform5");
	envItems->ftInitEnvitem((Vector2){1100, 380}, (Vector2){400, 13}, 1, GRAY, tmp, 6, "Platform6");
	envItems->ftInitEnvitem((Vector2){700, 100}, (Vector2){150, 10}, 1, GRAY, tmp, 7, "Platform7");
	envItems->ftInitEnvitem((Vector2){450, 500}, (Vector2){180, 15}, 1, GRAY, tmp, 8, "Platform8");
}

void	ftInitButtons(Game *game)
{
	game->buttonsMenuUp.play.ftInitOneEnvitem({(float)game->screenWidth - 385, 5}, {30, 30}, 0, WHITE,
		LoadTexture("./imgs/buttons/play_00.png"), 0);
	game->buttonsMenuUp.stop.ftInitOneEnvitem({(float)game->screenWidth - 345, 5}, {30, 30}, 0, WHITE,
		LoadTexture("./imgs/buttons/stop_00.png"), 1);

	game->buttonsMenuUp.buttonColorOpen.ftInitOneEnvitem({(float)game->screenWidth - 106, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpSelected.png"), 0);
	game->buttonsMenuUp.buttonColorClose.ftInitOneEnvitem({(float)game->screenWidth - 106, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpUnSelected.png"), 1);
	game->buttonsMenuUp.buttonControlClose.ftInitOneEnvitem({(float)game->screenWidth - 206, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonControlOpen.ftInitOneEnvitem({(float)game->screenWidth - 206, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpSelected.png"), 1);
	game->buttonsMenuUp.buttonListClose.ftInitOneEnvitem({(float)game->screenWidth - 305, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/listSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonListOpen.ftInitOneEnvitem({(float)game->screenWidth - 305, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/listSideUpSelected.png"), 1);

	game->buttonsMenuSideDown.buttonRightOpen.ftInitOneEnvitem({197, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonMiddleOpen.ftInitOneEnvitem({97, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonLeftOpen.ftInitOneEnvitem({-3, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpSelected.png"), 0);

	game->buttonsMenuSideDown.buttonRightClose.ftInitOneEnvitem({197, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonMiddleClose.ftInitOneEnvitem({97, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonLeftClose.ftInitOneEnvitem({-3, 0}, {100, 40}, 0, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpUnSelected.png"), 1);

	// Drag and Drop //
	game->dragDrop.square.ftInitOneEnvitem({20, 80}, {54, 54}, 0, WHITE,		// Square
		LoadTexture("./imgs/shapes/square00.png"), 1);
	game->dragDrop.squareSelect.ftInitOneEnvitem({20, 80}, {54, 54}, 0, WHITE,	// Square
		LoadTexture("./imgs/shapes/squareSelected00.png"), 1);

	game->dragDrop.triangle.ftInitOneEnvitem({120, 80}, {54, 54}, 0, WHITE, 		// Triangle
		LoadTexture("./imgs/shapes/triangle00.png"), 1);
	game->dragDrop.triangleSelect.ftInitOneEnvitem({120, 80}, {54, 54}, 0, WHITE,	// Triangle
		LoadTexture("./imgs/shapes/triangleSelected00.png"), 1);

	game->dragDrop.circle.ftInitOneEnvitem({220, 80}, {54, 54}, 0, WHITE, 	// Circle
		LoadTexture("./imgs/shapes/circle00.png"), 1);
	game->dragDrop.circleSelect.ftInitOneEnvitem({220, 80}, {54, 54}, 0, WHITE,	// Circle
		LoadTexture("./imgs/shapes/circleSelected00.png"), 1);

	game->dragDrop.other.ftInitOneEnvitem({20, 180}, {54, 54}, 0, WHITE, 	// Others
		LoadTexture("./imgs/shapes/other00.png"), 1);
	game->dragDrop.otherSelect.ftInitOneEnvitem({20, 180}, {54, 54}, 0, WHITE,	// Others
		LoadTexture("./imgs/shapes/otherSelected00.png"), 1);

	game->dragDrop.platform.ftInitOneEnvitem({120, 180}, {154, 54}, 0, WHITE, 	// Platform
		LoadTexture("./imgs/shapes/platform00.png"), 1);
	game->dragDrop.platformSelect.ftInitOneEnvitem({120, 180}, {154, 54}, 0, WHITE,	// Platform
		LoadTexture("./imgs/shapes/platformSelected00.png"), 1);
}

void	ftMode2D(Game *game, Menu *menu)
{
	Player	*player;
	player = new Player;
	player->ftSetPosition((Vector2){500, 300});
	player->ftInitVarChar();

	Props	*blocks;
	blocks = new Props;
	// obj::
	EnvItems *envItems;
	envItems = new EnvItems;

	game->imgCercleChrom = LoadImage("./imgs/wheelcolor.png");
	game->textCercleChrom = LoadTexture("./imgs/wheelcolor.png");
	game->rectCercleChrom = {0, 0, 150, 150};

	ftInitBlocks(blocks, envItems);
	ftInitTextBoxSideUp(game);

	//--------------------------------------------------------------------------------------//
	// Init Camera and windows

	MultipleCam2D	*allCameras = new MultipleCam2D;
	// Camera player
	allCameras->camera00.camera = {0};
	allCameras->camera00.camera.target = player->ftReturnPlayerPosition();
	allCameras->camera00.camera.offset = (Vector2){game->screenWidth / 2.0f - 150, game->screenHeight / 2.0f - 40};
	allCameras->camera00.camera.rotation = 0.0f;
	allCameras->camera00.camera.zoom = 1.0f;
	allCameras->camera00.textForCam = LoadRenderTexture(game->screenWidth - 300, game->screenHeight - 40);
	allCameras->camera00.rectForCam = {0.0f, 0.0f, (float)allCameras->camera00.textForCam.texture.width, (float)-allCameras->camera00.textForCam.texture.height};

	// Camera panel side up
	allCameras->camera01.camera = {0};
	allCameras->camera01.camera.target = {0, 0};
	allCameras->camera01.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera.rotation = 0.0f;
	allCameras->camera01.camera.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, game->screenHeight / 3);	// color panel
	allCameras->camera01.textForCam2 = LoadRenderTexture(300, game->screenHeight / 3);	// control panel
	allCameras->camera01.rectForCam = {0.0f, 0.0f, (float)allCameras->camera01.textForCam.texture.width, (float)-allCameras->camera01.textForCam.texture.height};
	// allCameras->camera01.image = LoadImage();

	// Camera panel side down
	allCameras->camera02.camera = {0};
	allCameras->camera02.camera.target = {0, 0};
	allCameras->camera02.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera.rotation = 0.0f;
	allCameras->camera02.camera.zoom = 1.0f;
	allCameras->camera02.textForCam = LoadRenderTexture(300, game->screenHeight / 3 * 2 - 40);
	allCameras->camera02.rectForCam = {0.0f, 0.0f, (float)allCameras->camera02.textForCam.texture.width, (float)-allCameras->camera02.textForCam.texture.height};

	// Camera panel up
	allCameras->camera03.camera = {0};
	allCameras->camera03.camera.target = {0, 0};
	allCameras->camera03.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera.rotation = 0.0f;
	allCameras->camera03.camera.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(game->screenWidth, 40);
	allCameras->camera03.rectForCam = {0.0f, 0.0f, (float)allCameras->camera03.textForCam.texture.width, (float)-allCameras->camera03.textForCam.texture.height};

	// Multiple camera
	// void (*cameraUpdaters[])(Camera2D *, Player *, EnvItem *, int, float, int, int) = {
	// 	ftUpdateCameraCenter};
	game->cameraUpdaters[0] = {ftUpdateCameraCenter};

//--------------------------------------------------------------------------------------//
	// buttons top

	ftInitButtons(game);

//--------------------------------------------------------------------------------------//
	int cameraUpdatersLength = sizeof(1) / sizeof(game->cameraUpdaters[0]);
	game->posCam = player->ftReturnPlayerPosition();

	// Main game loop
	while (!WindowShouldClose())
	{
		//** Drawning **//

		//Draw Play screen
		BeginTextureMode(allCameras->camera00.textForCam);
			ClearBackground(LIGHTGRAY);
			BeginMode2D(allCameras->camera00.camera);

				if (menu->ftReturnStart() == 0) // Menu intro
				{
					ftChooseMenu(menu);
					DrawTextEx(game->font1 ,"Untitled Adventure Game", {250, 100}, 40, 2, BLACK);
					// DrawText("Untitled Adventure Game", 100, 100, 40, BLACK);
					DrawText("Choose Your Character", 250, 200, 20, DARKGRAY);
					DrawText("Start Game", 250, 250, 20, DARKGRAY);
				}
				else if (menu->ftReturnStart() == 1)// Menu choose character
				{
					ftMenuChooseCharacter(game, player, menu);
				}
				else if (menu->ftReturnStart() == 2) // Main loop
				{
					// std::cout << "Help 00" << std::endl;
					if (game->ctMode == 1)
					{
						allCameras->camera00.camera.target = game->posCam;
						ftRunBuildMode(game, player, envItems, blocks, &allCameras->camera00.camera);
						ftControlItems(game, player, envItems, blocks);
					}
					else if (game->ctMode == -1)
					{
						Menu			tmpMenu;
						Player			tmpPlayer;
						EnvItems		tmpEnvItems(*envItems);
						Props			tmpBlocks;
						MultipleCam2D	tmpAllCameras;

						tmpMenu = *menu;
						tmpPlayer = *player;
						// tmpEnvItems = *envItems;
						tmpBlocks = blocks->ftReturnCopyProps();
						tmpAllCameras = *allCameras;

						// pid_t pid;
						// pid = fork();
						// if (pid == -1)
						// {
						// 	std::cout << "error" << std::endl;
						// 	exit(-1);
						// }
						// if (pid == 0)
						// {
						// 	allCameras->camera00.camera.target = player->ftReturnPlayerPosition();
						// 	ftRunGameMode(game, tmpMenu, tmpPlayer, tmpEnvItems, tmpBlocks, tmpAllCameras);
						// }
						// else
						// {
						// 	close(fd[1]);
						// 	dup2(fd[0], STDIN_FILENO);
						// 	waitpid(pid, NULL, 0);
						// }
						
						allCameras->camera00.camera.target = player->ftReturnPlayerPosition();
						ftRunGameMode(game, tmpMenu, tmpPlayer, tmpEnvItems,
							tmpBlocks, tmpAllCameras);
					
						game->ctMode = 1;
					}
					// ftKeyGestionBuildMode(game);
				}
			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side up
		BeginTextureMode(allCameras->camera01.textForCam);
			ClearBackground(DARKGRAY);
			BeginMode2D(allCameras->camera01.camera);

				if (menu->ftReturnStart() == 2)
				{
					ftSideUpMenu2D(game, player, menu, allCameras);
				}

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side down
		BeginTextureMode(allCameras->camera02.textForCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(allCameras->camera02.camera);

				if (menu->ftReturnStart() == 2)
				{
					ftSideDownMenu2D(game, blocks, envItems, allCameras);
				}

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel Up
		BeginTextureMode(allCameras->camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras->camera03.camera);

				ftUpMenu2D(game, &allCameras->camera03.camera);

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw render textures to the screen for all cameras
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTextureRec(allCameras->camera00.textForCam.texture, allCameras->camera00.rectForCam,
				(Vector2){0, 40}, WHITE);
			DrawTextureRec(allCameras->camera01.textForCam.texture, allCameras->camera01.rectForCam,
				(Vector2){(float)game->screenWidth - 300.0f, 40}, WHITE);
			DrawTextureRec(allCameras->camera02.textForCam.texture, allCameras->camera02.rectForCam,
				(Vector2){(float)game->screenWidth - 300.0f, (float)game->screenHeight / 3 + 40}, WHITE);
			DrawTextureRec(allCameras->camera03.textForCam.texture, allCameras->camera03.rectForCam,
				(Vector2){0, 0}, WHITE);
			ftDrawBoarders(game);
		EndDrawing();
	}
//--------------------------------------------------------------------------------------//
	// CloseWindow();

	ftDeleteAndFree(game, player, blocks, envItems, allCameras);
}

void	ftDeleteAndFree(Game *game, Player *player, Props *blocks,
			EnvItems *envItems, MultipleCam2D *allCameras)
{
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);

	player->ftDeleteVarChar();
	for (int i = 0; i < blocks->ftReturnNbr(); i++)
		blocks->ftDeleteVarsChar(i);
	for (int i = 0; i < envItems->ftReturnEnviAllNbr(); i++)
		envItems->ftDeleteVarChar(i);

	if (player->ftReturnNbr() == 1)
		player->ftDestroyImgs1();
	if (player->ftReturnNbr() == 2)
		player->ftDestroyImgs2();
	if (player->ftReturnNbr() == 3)
		player->ftDestroyImgs3();
	UnloadImage(game->imgCercleChrom);
	UnloadTexture(game->textCercleChrom);
	game->buttonsMenuUp.play.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.stop.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonColorOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonColorClose.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonControlOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonControlClose.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonListOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuUp.buttonListClose.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonRightOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonMiddleOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonLeftOpen.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonRightClose.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonMiddleClose.ftDestroyImgsPlayStop();
	game->buttonsMenuSideDown.buttonLeftClose.ftDestroyImgsPlayStop();
	game->dragDrop.square.ftDestroyImgsPlayStop();
	game->dragDrop.squareSelect.ftDestroyImgsPlayStop();
	game->dragDrop.triangle.ftDestroyImgsPlayStop();
	game->dragDrop.triangleSelect.ftDestroyImgsPlayStop();
	game->dragDrop.circle.ftDestroyImgsPlayStop();
	game->dragDrop.circleSelect.ftDestroyImgsPlayStop();
	game->dragDrop.other.ftDestroyImgsPlayStop();
	game->dragDrop.otherSelect.ftDestroyImgsPlayStop();
	game->dragDrop.platform.ftDestroyImgsPlayStop();
	game->dragDrop.platformSelect.ftDestroyImgsPlayStop();

	delete player;
	delete blocks;
	delete envItems;
	delete allCameras;
}

//*** Move items on Build Mode ***/
void	ftControlItems(Game *game, Player *player, EnvItems *envItems, Props *blocks)
{
	Vector2 mousePos = GetMousePosition();
	Vector2 lastPos = game->mouse.pos;
	Vector2 forMove = {lastPos.x - mousePos.x, lastPos.y - mousePos.y};

	if (game->selected2D.type == 1) // Player selected
	{
		Rectangle	posPly = game->selected2D.player->ftReturnRectangleCollBox();

		posPly.x -= 4;
		posPly.y -= 3;
		DrawLineEx({posPly.x, posPly.y}, {posPly.x + posPly.width + 7, posPly.y}, 2, RED); // Up
		posPly.y += posPly.height + 6;
		DrawLineEx({posPly.x, posPly.y}, {posPly.x + posPly.width + 7, posPly.y}, 2, RED); // down
		posPly = game->selected2D.player->ftReturnRectangleCollBox();
		posPly.x -= 3;
		posPly.y -= 3;
		DrawLineEx({posPly.x, posPly.y - 1}, {posPly.x, posPly.y + posPly.height + 7}, 2, RED); // Left
		posPly.x += posPly.width + 6;
		DrawLineEx({posPly.x, posPly.y - 1}, {posPly.x, posPly.y + posPly.height + 7}, 2, RED); // Right
		
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x < game->screenWidth - 300 && game->mouse.pos.y > 40)
		{
			player->ftMovePosition(-forMove.x / game->mouse.camZoom, -forMove.y / game->mouse.camZoom);
		}
	}
	else if (game->selected2D.type == 2) // Items Blocks Props
	{
		Rectangle	posBlock = game->selected2D.prop->ftReturnRectangle();

		posBlock.x -= 4;
		posBlock.y -= 3;
		DrawLineEx({posBlock.x, posBlock.y}, {posBlock.x + posBlock.width + 7, posBlock.y}, 2, RED); // Up
		posBlock.y += posBlock.height + 6;
		DrawLineEx({posBlock.x, posBlock.y}, {posBlock.x + posBlock.width + 7, posBlock.y}, 2, RED); // down
		posBlock = game->selected2D.prop->ftReturnRectangle();
		posBlock.x -= 3;
		posBlock.y -= 3;
		DrawLineEx({posBlock.x, posBlock.y - 1}, {posBlock.x, posBlock.y + posBlock.height + 7}, 2, RED); // Left
		posBlock.x += posBlock.width + 6;
		DrawLineEx({posBlock.x, posBlock.y - 1}, {posBlock.x, posBlock.y + posBlock.height + 7}, 2, RED); // Right
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x < game->screenWidth - 300 && game->mouse.pos.y > 40)
		{
			game->selected2D.prop->ftMovePosition(-forMove.x / game->mouse.camZoom, -forMove.y / game->mouse.camZoom);
		}
	}
	else if (game->selected2D.type == 3) // Platforms
	{
		Rectangle	posWalkable = game->selected2D.item->rect;

		posWalkable.x -= 4;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // Up
		posWalkable.y += posWalkable.height + 6;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // down
		posWalkable = game->selected2D.item->rect;
		posWalkable.x -= 3;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Left
		posWalkable.x += posWalkable.width + 6;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Right
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x < game->screenWidth - 300 && game->mouse.pos.y > 40)
		{
			game->selected2D.item->rect.x += (-(int)(forMove.x / game->mouse.camZoom));
			game->selected2D.item->rect.y += (-(int)(forMove.y / game->mouse.camZoom));
		}
	}
}

//*** Draw borders for menu ***//
void	ftDrawBoarders(Game *Game)
{
	DrawLineEx({(float)Game->screenWidth - 302, 40}, {(float)Game->screenWidth - 302, (float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 2, 0}, {(float)Game->screenWidth - 2, (float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight / 3 + 40}, {(float)Game->screenWidth, (float)Game->screenHeight / 3 + 40}, 5, DARKGRAY1);
	DrawLineEx({0, 40}, {(float)Game->screenWidth - 305, 40}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight - 2}, {(float)Game->screenWidth, (float)Game->screenHeight - 2}, 5, DARKGRAY1);
}
 

//*** Main fonction for control menu side down ***//
void	ftSideUpControlMenu2D(Game *game, Player *player, Menu *menu)
{
	ftDrawVarsRiDownPanel(game);
}
