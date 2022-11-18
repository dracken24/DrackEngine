#include "../../myIncludes/game.hpp"
#include "../../myIncludes/link.h"
#include <string.h>

using namespace obj;
using namespace std;

void	ftDrawSideDownButtons(Game *game);
void	ftChangeSidedownPanel(Game *game, Camera2D *camera);

// void	(*cameraUpdaters[])(Game *, Camera2D *, Player *, int, float, int, int);


// void	ftInitBlocks(Props *blocks, EnvItems *envItems)
// {
// 	Texture tmp;

// 	blocks->ftInitSquareProps(5, "blocks");
// 	blocks->ftAddProps((Vector2){200, 200}, (Vector2){24, 24}, BLUE, true, 0, "blocks");
// 	blocks->ftAddProps((Vector2){160, 200}, (Vector2){24, 24}, RED, true, 1, "blocks");
// 	blocks->ftAddProps((Vector2){120, 200}, (Vector2){24, 24}, YELLOW, true, 2, "blocks");
// 	blocks->ftAddProps((Vector2){240, 200}, (Vector2){24, 24}, PINK, true, 3, "blocks");
// 	blocks->ftAddProps((Vector2){80, 200}, (Vector2){24, 24}, PURPLE, true, 4, "blocks");

// 	envItems->ftNewEnvItem(9);
// 	envItems->ftInitEnvitem((Vector2){0, 0}, (Vector2){1000, 400}, 0, LIGHTGRAY, tmp, 0);
// 	envItems->ftInitEnvitem((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 1);
// 	envItems->ftInitEnvitem((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 2);
// 	envItems->ftInitEnvitem((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3);
// 	envItems->ftInitEnvitem((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 4);
// 	envItems->ftInitEnvitem((Vector2){-850, 350}, (Vector2){700, 205}, 1, GRAY, tmp, 5);
// 	envItems->ftInitEnvitem((Vector2){1100, 380}, (Vector2){400, 13}, 1, GRAY, tmp, 6);
// 	envItems->ftInitEnvitem((Vector2){700, 100}, (Vector2){150, 10}, 1, GRAY, tmp, 7);
// 	envItems->ftInitEnvitem((Vector2){450, 500}, (Vector2){180, 15}, 1, GRAY, tmp, 8);
// }

void	ftMode2D(Game *game, Menu *menu)
{
	Player	*player;
	player = new Player;
	player->ftSetPosition((Vector2){500, 300});
	player->ftInitVarChar();

	SquareProps *blocks = new SquareProps;
	EnvItems *envItems = new EnvItems;

	cout << "Debug: 0.00" << endl;

	game->imgCercleChrom = LoadImage("./imgs/wheelcolor.png");
	game->textCercleChrom = LoadTexture("./imgs/wheelcolor.png");
	game->rectCercleChrom = {0, 0, 150, 150};

	// blocks[0] = new SquareProps;
	blocks[0].obj::SquareProps::ftInitSquareprops((Vector2){200, 200}, (Vector2){24, 24}, BLUE, true, 0, "blocks0");
	blocks[1].obj::SquareProps::ftInitSquareprops((Vector2){160, 200}, (Vector2){24, 24}, RED, true, 1, "blocks1");
	blocks[2].obj::SquareProps::ftInitSquareprops((Vector2){120, 200}, (Vector2){24, 24}, YELLOW, true, 2, "blocks2");
	blocks[3].obj::SquareProps::ftInitSquareprops((Vector2){240, 200}, (Vector2){24, 24}, PINK, true, 3, "blocks3");
	blocks[4].obj::SquareProps::ftInitSquareprops((Vector2){80, 200}, (Vector2){24, 24}, PURPLE, true, 4, "blocks4");
	game->nbrSquareProps = 5;

	Texture2D	tmp;
	envItems[0].obj::EnvItems::ftInitOneEnvitem((Vector2){0, 0}, (Vector2){1000, 400}, 0, LIGHTGRAY, tmp, 0, "Platform0");
	envItems[1].obj::EnvItems::ftInitOneEnvitem((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 1, "Platform1");
	envItems[2].obj::EnvItems::ftInitOneEnvitem((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 2, "Platform1");
	envItems[3].obj::EnvItems::ftInitOneEnvitem((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3, "Platform3");
	envItems[4].obj::EnvItems::ftInitOneEnvitem((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 4, "Platform4");
	envItems[5].obj::EnvItems::ftInitOneEnvitem((Vector2){-850, 350}, (Vector2){700, 205}, 1, GRAY, tmp, 5, "Platform5");
	envItems[6].obj::EnvItems::ftInitOneEnvitem((Vector2){1100, 380}, (Vector2){400, 13}, 1, GRAY, tmp, 6, "Platform6");
	envItems[7].obj::EnvItems::ftInitOneEnvitem((Vector2){700, 100}, (Vector2){150, 10}, 1, GRAY, tmp, 7, "Platform7");
	envItems[8].obj::EnvItems::ftInitOneEnvitem((Vector2){450, 500}, (Vector2){180, 15}, 1, GRAY, tmp, 8, "Platform8");
	game->nbrEnvItems = 9;

	cout << "Debug: 0.10" << endl;
	ftInitTextBoxSideUp(game);
	cout << "Debug: 0.11" << endl;

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
	// game->cameraUpdaters[0](game, camera, player, envItemsLength, game->delta, game->screenWidth, game->screenHeight);

	//--------------------------------------------------------------------------------------//
	// buttons top
	game->buttonsMenuUp.play->ftInitButton({(float)game->screenWidth - 300, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/play_00.png"), 0, "Play");
	cout << "Debug: 0.11" << endl;
	game->buttonsMenuUp.stop->ftInitButton({(float)game->screenWidth - 260, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/stop_00.png"), 1, "Stop");
	cout << "Debug: 0.12" << endl;

	game->buttonsMenuUp.buttonColorOpen->ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40},
		WHITE, LoadTexture("./imgs/buttons/colorSideUpSelected.png"), 0, "SelectColorSideUp");
	game->buttonsMenuUp.buttonColorClose->ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40},
		WHITE, LoadTexture("./imgs/buttons/colorSideUpUnSelected.png"), 1, "UnSelectColorSideUp");
	game->buttonsMenuUp.buttonControlOpen->ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40},
		WHITE, LoadTexture("./imgs/buttons/controlSideUpSelected.png"), 2, "SelectControlSideUp");
	game->buttonsMenuUp.buttonControlClose->ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40},
		WHITE, LoadTexture("./imgs/buttons/controlSideUpUnSelected.png"), 3, "UnSelectControlSideUp");

	game->buttonsMenuSideDown.buttonRightOpen->ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpSelected.png"), 0, "shapesSideUpSelected");
	game->buttonsMenuSideDown.buttonMiddleOpen->ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpSelected.png"), 1, "untitledSideUpSelected");
	game->buttonsMenuSideDown.buttonLeftOpen->ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpSelected.png"), 2, "untitledSideUpSelected");

	game->buttonsMenuSideDown.buttonRightClose->ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpUnSelected.png"), 0, "shapesSideUpUnSelected");
	game->buttonsMenuSideDown.buttonMiddleClose->ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpUnSelected.png"), 1, "untitledSideUpUnSelected");
	game->buttonsMenuSideDown.buttonLeftClose->ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpUnSelected.png"), 2, "untitledSideUpUnSelected");


	// game->buttonsMenuUp.stop.ftInitOneEnvitem();

	// game->buttonsMenuUp.buttonColorOpen.ftInitOneEnvitem();
	// game->buttonsMenuUp.buttonColorClose.ftInitOneEnvitem();
	// game->buttonsMenuUp.buttonControlClose.ftInitOneEnvitem();
	// game->buttonsMenuUp.buttonControlOpen.ftInitOneEnvitem();

	// game->buttonsMenuSideDown.buttonRightOpen.ftInitOneEnvitem();
	// game->buttonsMenuSideDown.buttonMiddleOpen.ftInitOneEnvitem();
	// game->buttonsMenuSideDown.buttonLeftOpen.ftInitOneEnvitem();

	// 	game->buttonsMenuSideDown.buttonRightClose.ftInitOneEnvitem();
	// game->buttonsMenuSideDown.buttonMiddleClose.ftInitOneEnvitem();
	// game->buttonsMenuSideDown.buttonLeftClose.ftInitOneEnvitem();

	//--------------------------------------------------------------------------------------//
	// int cameraUpdatersLength = sizeof(1) / sizeof(cameraUpdaters[0]);
	game->posCam = player->ftReturnPlayerPosition();
	cout << "Debug: 0.20" << endl;

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
					cout << "Debug: 0.30" << endl;
					ftChooseMenu(menu);
					cout << "Debug: 0.31" << endl;
					DrawTextEx(game->font1 ,"Untitled Adventure Game", {250, 100}, 40, 2, BLACK);
					// DrawText("Untitled Adventure Game", 100, 100, 40, BLACK);
					DrawText("Choose Your Character", 250, 200, 20, DARKGRAY);
					DrawText("Start Game", 250, 250, 20, DARKGRAY);
					cout << "Debug: 0.32" << endl;
				}
				else if (menu->ftReturnStart() == 1)// Menu choose character
				{
					cout << "Debug: 0.40" << endl;
					ftMenuChooseCharacter(game, player, menu);
					cout << "Debug: 0.50" << endl;
				}
				else // Main loop
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
						EnvItems		*tmpEnvItems = new EnvItems;
						SquareProps		*tmpBlocks = new SquareProps;
						MultipleCam2D	tmpAllCameras;

						tmpMenu = *menu;
						tmpPlayer = *player;
						for (int i = 0; i< game->nbrEnvItems; i++)
							tmpEnvItems[i] = envItems[i];
						for (int i = 0; i < game->nbrSquareProps; i++)
							tmpBlocks[i] = blocks[i];
						// tmpBlocks = blocks->ftReturnCopyProps();
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
						delete tmpEnvItems;
						delete tmpBlocks;
					
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
								
				cout << "Debug: cam01 " << endl;
				ftSideUpMenu2D(game, player, menu, allCameras);
				cout << "Debug: cam01.1" << endl;


			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel side down
		BeginTextureMode(allCameras->camera02.textForCam);
			ClearBackground(DARKGRAY2);
			BeginMode2D(allCameras->camera02.camera);

				cout << "Debug: cam02 " << endl;
				ftSideDownMenu2D(game, &allCameras->camera02.camera);
				cout << "Debug: cam02.2 " << endl;

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

	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);

	player->ftDeleteVarChar();
	for (int i = 0; i < game->nbrSquareProps; i++)
		blocks[i].obj::SquareProps::ftDeleteVars();
	for (int i = 0; i < game->nbrEnvItems; i++)
		envItems[i].obj::EnvItems::ftDeleteVarChar();

	if (player->ftReturnNbr() == 1)
		player->ftDestroyImgs1();
	if (player->ftReturnNbr() == 2)
		player->ftDestroyImgs2();
	if (player->ftReturnNbr() == 3)
		player->ftDestroyImgs3();
	UnloadImage(game->imgCercleChrom);
	UnloadTexture(game->textCercleChrom);
	game->buttonsMenuUp.play->ftDeleteButtonTexture();
	game->buttonsMenuUp.stop->ftDeleteButtonTexture();
	game->buttonsMenuUp.buttonColorOpen->ftDeleteButtonTexture();
	game->buttonsMenuUp.buttonColorClose->ftDeleteButtonTexture();
	game->buttonsMenuUp.buttonControlOpen->ftDeleteButtonTexture();
	game->buttonsMenuUp.buttonControlClose->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonRightOpen->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonMiddleOpen->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonLeftOpen->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonRightClose->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonMiddleClose->ftDeleteButtonTexture();
	game->buttonsMenuSideDown.buttonLeftClose->ftDeleteButtonTexture();

	delete player;
	delete blocks;
	delete envItems;
	delete allCameras;
}

//*** Move items on Build Mode ***/
void	ftControlItems(Game *game, Player *player, EnvItems *envItems, SquareProps *blocks)
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
		Rectangle	posWalkable = game->selected2D.item->obj::EnvItems::ftReturnOneRectangle();

		posWalkable.x -= 4;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // Up
		posWalkable.y += posWalkable.height + 6;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // down
		posWalkable = game->selected2D.item->obj::EnvItems::ftReturnOneRectangle();
		posWalkable.x -= 3;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Left
		posWalkable.x += posWalkable.width + 6;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Right
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x < game->screenWidth - 300 && game->mouse.pos.y > 40)
		{
			game->selected2D.item->obj::EnvItems::ftChangePosition(-(int)(forMove.x / game->mouse.camZoom), 0);
			game->selected2D.item->obj::EnvItems::ftChangePosition(0, -(int)(forMove.y / game->mouse.camZoom));
		}
	}
}

//*** Draw borders for menu ***//
void	ftDrawBoarders(Game *Game)
{
	DrawLineEx({(float)Game->screenWidth - 302, 40}, {(float)Game->screenWidth - 302,
		(float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 2, 0}, {(float)Game->screenWidth - 2,
		(float)Game->screenHeight}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight / 3 + 40},
		{(float)Game->screenWidth, (float)Game->screenHeight / 3 + 40}, 5, DARKGRAY1);
	DrawLineEx({0, 40}, {(float)Game->screenWidth - 206, 40}, 5, DARKGRAY1);
	DrawLineEx({(float)Game->screenWidth - 300, (float)Game->screenHeight - 2},
		{(float)Game->screenWidth, (float)Game->screenHeight - 2}, 5, DARKGRAY1);
}

void	ftSelectItemsTop(Game *game, Camera2D *camera)
{
	Vector2 mousePos = game->mouse.pos;
	Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Rectangle item = game->buttonsMenuUp.play->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != -1)
		{
			game->ctMode = -1;
		}
		item = game->buttonsMenuUp.stop->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != 1)
		{
			game->ctMode = 1;
		}
	}
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Game *game, Camera2D *camera)
{
	Vector2 mousePos = game->mouse.pos;
	Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Rectangle item = game->buttonsMenuUp.play->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != -1)
		{
			game->ctMode = -1;
		}
		item = game->buttonsMenuUp.stop->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != 1)
		{
			game->ctMode = 1;
		}
	}
	// ftSelectItemsTop(game, camera);
	DrawTextureEx(game->buttonsMenuUp.play->ftReturnTexture(), {(float)game->screenWidth - 300, 5}, 0, 1, WHITE);
	DrawTextureEx(game->buttonsMenuUp.stop->ftReturnTexture(), {(float)game->screenWidth - 260, 5}, 0, 1, WHITE);
	if (game->ctMenuUpButtons == 1) // Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonColorOpen->ftReturnTexture(),
			game->buttonsMenuUp.buttonColorOpen->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose->ftReturnTexture(),
			game->buttonsMenuUp.buttonControlClose->ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 0) // Second Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonControlOpen->ftReturnTexture(),
			game->buttonsMenuUp.buttonControlOpen->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose->ftReturnTexture(),
			game->buttonsMenuUp.buttonColorClose->ftReturnPosition(), 0, 1, WHITE);
	}
	DrawText("Panel Up", 10, 10, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		Rectangle item = game->buttonsMenuUp.buttonColorOpen->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuUpButtons = 1;
		}
		item = game->buttonsMenuUp.buttonControlOpen->ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuUpButtons = 0;
		}
	}
}

//*** Main fonction for control menu side down ***//
void	ftSideUpControlMenu2D(Game *game, Player *player, Menu *menu)
{
	ftDrawVarsRiDownPanel(game);
}

//*** All functions for side down panel ***//
void	ftSideDownMenu2D(Game *game, Camera2D *camera)
{
	ftDrawSideDownButtons(game);
	ftChangeSidedownPanel(game, camera);
}

//*** Put Button control panel for menu side down ***//
void	ftDrawSideDownButtons(Game *game)
{
	cout << game->ctMenuSideDownButtons << endl;
	if (game->ctMenuSideDownButtons == 0) // Right button side down
	{
		// Vector2 test = {0, 0};
		// Texture2D text = LoadTexture("./imgs/buttons/play_00.png");
		cout << "Debug: 3.010 " << endl;
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightOpen->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightOpen->ftReturnPosition(), 0, 1, WHITE);
		cout << "Debug: 3.011 " << endl;
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonMiddleClose->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftClose->ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuSideDownButtons == 1) // Middle button side down
	{
		cout << "Debug: 3.020 " << endl;
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightClose->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleOpen->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonMiddleOpen->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftClose->ftReturnPosition(), 0, 1, WHITE);
		cout << "Debug: 3.021 " << endl;
	}
	else if (game->ctMenuSideDownButtons == 2) // Left button side down
	{
		cout << "Debug: 3.030 " << endl;
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightClose->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleClose->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonMiddleClose->ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftOpen->ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftOpen->ftReturnPosition(), 0, 1, WHITE);
		cout << "Debug: 3.031 " << endl;
	}
	cout << "Debug: 3.10 " << endl;
}

//*** Change counter for change button side down panel ***//
void	ftChangeSidedownPanel(Game *game, Camera2D *camera)
{
	Vector2 pos1 = {(float)game->screenWidth - 97, (float)game->screenHeight / 3 + 40};
	Vector2 pos2 = {(float)game->screenWidth - 197, (float)game->screenHeight / 3 + 40};
	Vector2 pos3 = {(float)game->screenWidth - 297, (float)game->screenHeight / 3 + 40};

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		Rectangle item = game->buttonsMenuSideDown.buttonRightOpen->ftReturnRectangle(); // Right button
		item.x = pos1.x;
		item.y = pos1.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 0;
		}
		item = game->buttonsMenuSideDown.buttonMiddleOpen->ftReturnRectangle(); // Middle button
		item.x = pos2.x;
		item.y = pos2.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 1;
		}
		item = game->buttonsMenuSideDown.buttonLeftOpen->ftReturnRectangle(); // Left button
		item.x = pos3.x;
		item.y = pos3.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 2;
		}
	}
}