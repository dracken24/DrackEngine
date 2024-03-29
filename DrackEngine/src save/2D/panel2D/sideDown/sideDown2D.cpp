/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   sideDown2D.hpp         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../myIncludes/game.hpp"

void	ftChangeSidedownPanel(Game *game, Camera2D *camera);
void	ftDrawSideDownButtons(Game *game);
void	ftDragAndDrop(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, MultipleCam2D *allCameras);

//*** All functions for side down panel ***//
void	ftSideDownMenu2D(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, MultipleCam2D *allCameras)
{
	ftDrawSideDownButtons(game);
	ftChangeSidedownPanel(game, &allCameras->camera02.camera);

	if (game->ctMenuSideDownButtons == 0)
	{
		ftDragAndDrop(game, blocks, envItems, allCameras);
	}
	else if (game->ctMenuSideDownButtons == 1)
	{

	}
	else if (game->ctMenuSideDownButtons == 2)
	{

	}
}

//*** Draw shapes for drag and drop ***//
void	ftDragAndDrop(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, MultipleCam2D *allCameras)
{
	Vector2 mousePos = game->mouse.pos;
	Vector2 rayPos = GetScreenToWorld2D(mousePos, allCameras->camera02.camera);

	DrawText("Square", 12, 55, 20, DARKGRAY);
	Rectangle rec = {1221, 387, 54, 54};
	if (CheckCollisionPointRec(rayPos, rec))
	{
		DrawTextureEx(game->dragDrop.squareSelect->ftReturnTexture(),
			game->dragDrop.squareSelect->ftReturnPos(), 0, 1, WHITE); // Square
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2		pos = GetScreenToWorld2D(CENTER_SCREEN, allCameras->camera00.camera);
			Texture2D	text;
			std::string	name;

			name = "Block";
			name.insert(name.length(), std::to_string(blocks->size()));
			blocks->push_back(SquareProps(pos, (Vector2){24, 24}, 0, DARKGRAY, text, blocks->size() + 1, name));
			blocks->at(blocks->size() - 1).ftSetSpeed(0);
			blocks->at(blocks->size() - 1).ftSetSpeedModifier(0, 'X');
		}
	}
	else
	{
		DrawTextureEx(game->dragDrop.square->ftReturnTexture(),
			game->dragDrop.square->ftReturnPos(), 0, 1, WHITE);	// Square
	}

	DrawText("Triangle", 102, 55, 20, DARKGRAY);
	rec = {1321, 387, 54, 54};
	if (CheckCollisionPointRec(rayPos, rec))
	{
		DrawTextureEx(game->dragDrop.triangleSelect->ftReturnTexture(),
			game->dragDrop.triangleSelect->ftReturnPos(), 0, 1, WHITE); // Triangle
	}
	else
	{
		DrawTextureEx(game->dragDrop.triangle->ftReturnTexture(),
			game->dragDrop.triangle->ftReturnPos(), 0, 1, WHITE);	// Triangle
	}

	DrawText("Circle", 218, 55, 20, DARKGRAY);
	rec = {1421, 387, 54, 54};
	if (CheckCollisionPointRec(rayPos, rec))
	{
		DrawTextureEx(game->dragDrop.circleSelect->ftReturnTexture(),
			game->dragDrop.circleSelect->ftReturnPos(), 0, 1, WHITE); // Circle
	}
	else
	{
		DrawTextureEx(game->dragDrop.circle->ftReturnTexture(),
			game->dragDrop.circle->ftReturnPos(), 0, 1, WHITE);	// Circle
	}

	DrawText("Others", 12, 155, 20, DARKGRAY);
	rec = {1221, 487, 54, 54};
	if (CheckCollisionPointRec(rayPos, rec))
	{
		DrawTextureEx(game->dragDrop.otherSelect->ftReturnTexture(),
			game->dragDrop.otherSelect->ftReturnPos(), 0, 1, WHITE); // Others
	}
	else
	{
		DrawTextureEx(game->dragDrop.other->ftReturnTexture(),
			game->dragDrop.other->ftReturnPos(), 0, 1, WHITE);	// Others
	}

	DrawText("Platform", 150, 155, 20, DARKGRAY);
	rec = {1321, 487, 154, 54};
	if (CheckCollisionPointRec(rayPos, rec))
	{
		DrawTextureEx(game->dragDrop.platformSelect->ftReturnTexture(),
			game->dragDrop.platformSelect->ftReturnPos(), 0, 1, WHITE); // Platforms
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Texture2D	tex;
			Vector2 pos = GetScreenToWorld2D(CENTER_SCREEN, allCameras->camera00.camera);

			std::string	name;
			name = "Platform";

			name.insert(name.length(), std::to_string(envItems->size()));
			envItems->push_back(EnvItems(pos, {244, 56}, 1, DARKGRAY, tex, envItems->size() + 1, name));
		}
	}
	else
	{
		DrawTextureEx(game->dragDrop.platform->ftReturnTexture(),
			game->dragDrop.platform->ftReturnPos(), 0, 1, WHITE);	// Platforms
	}
}

//*** Put Button control panel for menu side down ***//
void	ftDrawSideDownButtons(Game *game)
{
	if (game->ctMenuSideDownButtons == 0) // Right panel side down
	{
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightOpen.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightOpen.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleClose.ftReturnTexture(),
			 game->buttonsMenuSideDown.buttonMiddleClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftClose.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftClose.ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuSideDownButtons == 1) // Middle panel side down
	{
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightClose.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleOpen.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonMiddleOpen.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftClose.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftClose.ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuSideDownButtons == 2) // Left panel side down
	{
		DrawTextureEx(game->buttonsMenuSideDown.buttonRightClose.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonRightClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonMiddleClose.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonMiddleClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuSideDown.buttonLeftOpen.ftReturnTexture(),
			game->buttonsMenuSideDown.buttonLeftOpen.ftReturnPosition(), 0, 1, WHITE);
	}
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

		Rectangle item = game->buttonsMenuSideDown.buttonRightOpen.ftReturnRectangle(); // Right button
		item.x = pos1.x;
		item.y = pos1.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 0;
		}
		item = game->buttonsMenuSideDown.buttonMiddleOpen.ftReturnRectangle(); // Middle button
		item.x = pos2.x;
		item.y = pos2.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 1;
		}
		item = game->buttonsMenuSideDown.buttonLeftOpen.ftReturnRectangle(); // Left button
		item.x = pos3.x;
		item.y = pos3.y;
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuSideDownButtons = 2;
		}
	}
}
