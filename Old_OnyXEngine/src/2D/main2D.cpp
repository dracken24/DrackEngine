#include "../../myIncludes/class2D/squareProps.hpp"
#include "../../myIncludes/class2D/envitems.hpp"
#include "../../myIncludes/game.hpp"
#include "../../myIncludes/class/buttons.hpp"
#include <string.h>
#include <stdlib.h>

void	ftDeleteAndFree(Game *game, Player *player, std::vector<SquareProps> *blocks,
			std::vector<EnvItems> *envItems, MultipleCam2D *allCameras);

void	ftInitBlocks(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems)
{
	Texture tmp;
	std::string name;

	for (int i = 0; i < 5; i++)
	{
		name = "Block";
		name.insert(name.length(), std::to_string(i));
		blocks->push_back(SquareProps((Vector2){(float)(200 + (i * 50)), 200}, (Vector2){24, 24}, 0, BLUE, tmp, i, name));
	}

	envItems->push_back(EnvItems((Vector2){0, 400}, (Vector2){1000, 200}, 1, GRAY, tmp, 0, "Platform0"));
	envItems->push_back(EnvItems((Vector2){300, 150}, (Vector2){400, 10}, 1, GRAY, tmp, 1, "Platform1"));
	envItems->push_back(EnvItems((Vector2){250, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 2, "Platform2"));
	envItems->push_back(EnvItems((Vector2){650, 250}, (Vector2){100, 10}, 1, GRAY, tmp, 3, "Platform3"));
}

void	ftMode2D(Game *game, Menu *menu)
{
	Player	*player = new Player;
	player->ftSetPosition((Vector2){500, 300});
	player->ftInitVarChar();

	std::vector<SquareProps> blocks;
	std::vector<EnvItems> envItems;

	game->imgCercleChrom = LoadImage("./imgs/wheelcolor.png");
	game->textCercleChrom = LoadTexture("./imgs/wheelcolor.png");
	game->rectCercleChrom = {0, 0, 150, 150};

	ftInitBlocks(game, &blocks, &envItems);
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

	// std::cout << T_RED << "Size: " << envItems.size() << T_RESET << std::endl;
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
								ftRunBuildMode(game, player, &envItems, &blocks, &allCameras->camera00.camera);
								ftControlItems(game, player, &envItems, &blocks);
								break;
							case -1:
								Menu			tmpMenu;
								Player			tmpPlayer;
								MultipleCam2D	tmpAllCameras;

								tmpMenu = *menu;
								tmpPlayer = *player;

								tmpAllCameras = *allCameras;
								allCameras->camera00.camera.target = player->ftReturnPlayerPosition();

								ftRunGameMode(game, tmpMenu, tmpPlayer, envItems,
									blocks, tmpAllCameras);
									
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
					ftSideUpMenu2D(game, player, &blocks, &envItems, menu, allCameras);
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
					ftSideDownMenu2D(game, &blocks, &envItems, allCameras);
				}

			EndMode2D();
		EndTextureMode();

//--------------------------------------------------------------------------------------//

		// Draw Control Panel Up
		BeginTextureMode(allCameras->camera03.textForCam);
			ClearBackground(DARKGRAY1);
			BeginMode2D(allCameras->camera03.camera);

				ftUpMenu2D(game, player, &blocks, &envItems, &allCameras->camera03.camera);

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

	ftDeleteAndFree(game, player, &blocks, &envItems, allCameras);
}

//*** Move items on Build Mode ***/
void	ftControlItems(Game *game, Player *player, std::vector<EnvItems> *envItems, std::vector<SquareProps> *blocks)
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
