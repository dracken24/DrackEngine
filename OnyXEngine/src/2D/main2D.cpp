#include "../../myIncludes/class2D/squareProps.hpp"
#include "../../myIncludes/class2D/envitems.hpp"
#include "../../myIncludes/game.hpp"
#include "../../myIncludes/class/buttons.hpp"
#include <string.h>
#include <stdlib.h>

void	ftDeleteAndFree(Game *game, Player *player, std::vector<SquareProps> *blocks,
			EnvItems **envItems, MultipleCam2D *allCameras);

void	ftInitBlocks(Game *game, std::vector<SquareProps> *blocks, EnvItems **envItems)
{
	Texture tmp;
	std::string name;

	for (int i = 0; i < 5; i++)
	{
		name = "Block";
		name.insert(name.length(), std::to_string(i));
		blocks->push_back(SquareProps((Vector2){(float)(200 + (i * 50)), 200}, (Vector2){24, 24}, 0, BLUE, tmp, i, name));
	}

	envItems[0] = new EnvItems((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 1, "Platform0");
	envItems[1] = new EnvItems((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 2, "Platform1");
	envItems[2] = new EnvItems((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3, "Platform2");
	envItems[3] = new EnvItems((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 4, "Platform3");
	game->nbrEnvi = 4;
}

void	ftInitButtons(Game *game)
{
	game->buttonsMenuUp.play.ftInitButton({(float)game->screenWidth - 385, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/play_00.png"), 0);
	game->buttonsMenuUp.stop.ftInitButton({(float)game->screenWidth - 345, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/stop_00.png"), 1);

	game->buttonsMenuUp.buttonColorOpen.ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpSelected.png"), 0);
	game->buttonsMenuUp.buttonColorClose.ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpUnSelected.png"), 1);
	game->buttonsMenuUp.buttonControlClose.ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonControlOpen.ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpSelected.png"), 1);
	game->buttonsMenuUp.buttonListClose.ftInitButton({(float)game->screenWidth - 305, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/listSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonListOpen.ftInitButton({(float)game->screenWidth - 305, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/listSideUpSelected.png"), 1);

	game->buttonsMenuSideDown.buttonRightOpen.ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonMiddleOpen.ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonLeftOpen.ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpSelected.png"), 0);

	game->buttonsMenuSideDown.buttonRightClose.ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonMiddleClose.ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonLeftClose.ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpUnSelected.png"), 1);

	// Drag and Drop //
	game->dragDrop.square = new EnvItems((Vector2){20, 80}, (Vector2){54, 54}, 0, WHITE,		// Square
		LoadTexture("./imgs/shapes/square00.png"), 1, "Square0");

	game->dragDrop.squareSelect = new EnvItems((Vector2){20, 80}, (Vector2){54, 54}, 0, WHITE,	// Square
		LoadTexture("./imgs/shapes/squareSelected00.png"), 1, "Square1");

	game->dragDrop.triangle = new EnvItems((Vector2){120, 80}, (Vector2){54, 54}, 0, WHITE, 		// Triangle
		LoadTexture("./imgs/shapes/triangle00.png"), 1, "Triangle0");
	game->dragDrop.triangleSelect = new EnvItems((Vector2){120, 80}, (Vector2){54, 54}, 0, WHITE,	// Triangle
		LoadTexture("./imgs/shapes/triangleSelected00.png"), 1, "Triangle1");

	game->dragDrop.circle = new EnvItems((Vector2){220, 80}, (Vector2){54, 54}, 0, WHITE, 	// Circle
		LoadTexture("./imgs/shapes/circle00.png"), 1, "Circle0");
	game->dragDrop.circleSelect = new EnvItems((Vector2){220, 80}, (Vector2){54, 54}, 0, WHITE,	// Circle
		LoadTexture("./imgs/shapes/circleSelected00.png"), 1, "Circle1");

	game->dragDrop.other = new EnvItems((Vector2){20, 180}, (Vector2){54, 54}, 0, WHITE, 	// Others
		LoadTexture("./imgs/shapes/other00.png"), 1, "Other0");
	game->dragDrop.otherSelect = new EnvItems((Vector2){20, 180}, (Vector2){54, 54}, 0, WHITE,	// Others
		LoadTexture("./imgs/shapes/otherSelected00.png"), 1, "Other1");

	game->dragDrop.platform = new EnvItems((Vector2){120, 180},(Vector2) {154, 54}, 0, WHITE, 	// Platform
		LoadTexture("./imgs/shapes/platform00.png"), 1, "Platform0");
	game->dragDrop.platformSelect = new EnvItems((Vector2){120, 180},(Vector2) {154, 54}, 0, WHITE,	// Platform
		LoadTexture("./imgs/shapes/platformSelected00.png"), 1, "Platform1");
}

void	ftMode2D(Game *game, Menu *menu)
{
	Player	*player = new Player;
	player->ftSetPosition((Vector2){500, 300});
	player->ftInitVarChar();

	std::vector<SquareProps> blocks;
	EnvItems *envItems[256];

	game->imgCercleChrom = LoadImage("./imgs/wheelcolor.png");
	game->textCercleChrom = LoadTexture("./imgs/wheelcolor.png");
	game->rectCercleChrom = {0, 0, 150, 150};

	ftInitBlocks(game, &blocks, envItems);
	ftInitTextBoxSideUp(game);

//--------------------------------------------------------------------------------------//
	// Init Camera and windows

	MultipleCam2D	*allCameras = new MultipleCam2D;

	ftInitCameras(game, allCameras);
	allCameras->camera00.camera.target = player->ftReturnPlayerPosition();

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

				switch (menu->ftReturnStart())
				{
					case 0:
						ftChooseMenu(menu);
						DrawTextEx(game->font1 ,"Untitled Adventure Game", {250, 100}, 40, 2, BLACK);
						DrawText("Choose Your Character", 250, 200, 20, DARKGRAY);
						DrawText("Start Game", 250, 250, 20, DARKGRAY);
						break;
					case 1:
						ftMenuChooseCharacter(game, player, menu);
						break;
					case 2:
						switch (game->ctMode)
						{
							case 1:
								allCameras->camera00.camera.target = game->posCam;
								ftRunBuildMode(game, player, envItems, &blocks, &allCameras->camera00.camera);
								ftControlItems(game, player, envItems, &blocks);
								break;
							case -1:
								int tmpEnvi = game->nbrEnvi;

								Menu			tmpMenu;
								Player			tmpPlayer;
								EnvItems		*tmpEnvItems[256];
								MultipleCam2D	tmpAllCameras;

								tmpMenu = *menu;
								tmpPlayer = *player;
								for (int i = 0; i < game->nbrEnvi; i++)
								{
									tmpEnvItems[i] = envItems[i];
								}

								tmpAllCameras = *allCameras;
								allCameras->camera00.camera.target = player->ftReturnPlayerPosition();

								ftRunGameMode(game, tmpMenu, tmpPlayer, tmpEnvItems,
									blocks, tmpAllCameras);
									
								game->nbrEnvi = tmpEnvi;
								game->ctMode = 1;
								break;
						}
					break;
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
					ftSideUpMenu2D(game, player, &blocks, envItems, menu, allCameras);
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
					ftSideDownMenu2D(game, &blocks, envItems, allCameras);
				}

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel Up
		BeginTextureMode(allCameras->camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras->camera03.camera);

				ftUpMenu2D(game, player, &blocks, envItems, &allCameras->camera03.camera);

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

	ftDeleteAndFree(game, player, &blocks, envItems, allCameras);
}

void	ftDeleteAndFree(Game *game, Player *player, std::vector<SquareProps> *blocks,
			EnvItems **envItems, MultipleCam2D *allCameras)
{
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);

	player->ftDeleteVarChar();
	blocks->clear();

	for (int i = 0; i < game->nbrEnvi; i++)
	{
		envItems[i]->ftDeleteVarsChar();
		delete envItems[i];
	}

	if (player->ftReturnNbr() == 1)
	{
		player->ftDestroyImgs1();
	}
	if (player->ftReturnNbr() == 2)
	{
		player->ftDestroyImgs2();
	}
	if (player->ftReturnNbr() == 3)
	{
		player->ftDestroyImgs3();
	}

	UnloadImage(game->imgCercleChrom);
	UnloadTexture(game->textCercleChrom);
	game->buttonsMenuUp.play.ftUnloadTexture();
	game->buttonsMenuUp.stop.ftUnloadTexture();
	game->buttonsMenuUp.buttonColorOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonColorClose.ftUnloadTexture();
	game->buttonsMenuUp.buttonControlOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonControlClose.ftUnloadTexture();
	game->buttonsMenuUp.buttonListOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonListClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonRightOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonMiddleOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonLeftOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonRightClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonMiddleClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonLeftClose.ftUnloadTexture();
	
	game->dragDrop.square->ftDeleteVarsChar();
	game->dragDrop.square->ftUnloadTexture();
	delete game->dragDrop.square;
	game->dragDrop.squareSelect->ftDeleteVarsChar();
	game->dragDrop.squareSelect->ftUnloadTexture();
	delete game->dragDrop.squareSelect;
	game->dragDrop.triangle->ftDeleteVarsChar();
	game->dragDrop.triangle->ftUnloadTexture();
	delete game->dragDrop.triangle;
	game->dragDrop.triangleSelect->ftDeleteVarsChar();
	game->dragDrop.triangleSelect->ftUnloadTexture();
	delete game->dragDrop.triangleSelect;
	game->dragDrop.circle->ftDeleteVarsChar();
	game->dragDrop.circle->ftUnloadTexture();
	delete game->dragDrop.circle;
	game->dragDrop.circleSelect->ftDeleteVarsChar();
	game->dragDrop.circleSelect->ftUnloadTexture();
	delete game->dragDrop.circleSelect;
	game->dragDrop.other->ftDeleteVarsChar();
	game->dragDrop.other->ftUnloadTexture();
	delete game->dragDrop.other;
	game->dragDrop.otherSelect->ftDeleteVarsChar();
	game->dragDrop.otherSelect->ftUnloadTexture();
	delete game->dragDrop.otherSelect;
	game->dragDrop.platform->ftDeleteVarsChar();
	game->dragDrop.platform->ftUnloadTexture();
	delete game->dragDrop.platform;
	game->dragDrop.platformSelect->ftDeleteVarsChar();
	game->dragDrop.platformSelect->ftUnloadTexture();
	delete game->dragDrop.platformSelect;

	delete player;
	delete allCameras;
}

//*** Move items on Build Mode ***/
void	ftControlItems(Game *game, Player *player, EnvItems **envItems, std::vector<SquareProps> *blocks)
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
			game->selected2D.prop->ftMovePos({-forMove.x / game->mouse.camZoom, -forMove.y / game->mouse.camZoom});
		}
	}
	else if (game->selected2D.type == 3) // Platforms
	{
		Rectangle	posWalkable = game->selected2D.item->ftReturnRectangle();

		posWalkable.x -= 4;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // Up
		posWalkable.y += posWalkable.height + 6;
		DrawLineEx({posWalkable.x, posWalkable.y}, {posWalkable.x + posWalkable.width + 7, posWalkable.y}, 2, RED); // down
		posWalkable = game->selected2D.item->ftReturnRectangle();
		posWalkable.x -= 3;
		posWalkable.y -= 3;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Left
		posWalkable.x += posWalkable.width + 6;
		DrawLineEx({posWalkable.x, posWalkable.y - 1}, {posWalkable.x, posWalkable.y + posWalkable.height + 7}, 2, RED); // Right
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x < game->screenWidth - 300 && game->mouse.pos.y > 40)
		{
			Vector2 pos;
			pos.x = (int)(forMove.x / game->mouse.camZoom);
			pos.y = (int)(forMove.y / game->mouse.camZoom);
			game->selected2D.item->ftMovePos({-pos.x, -pos.y});
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
