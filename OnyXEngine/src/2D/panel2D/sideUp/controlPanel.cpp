#include "../../../../myIncludes/game.hpp"
#include <iostream>

char	*ft_ftoa(float f, int *status)
{
	static char buf[17];
	char *cp = buf;
	unsigned long l, rem;

	if (f < 0)
	{
		*cp++ = '-';
		f = -f;
	}
	l = (unsigned long)f;
	f -= (float)l;
	rem = (unsigned long)(f * 1e6);
	sprintf(cp, "%lu.%6.6lu", l, rem);
	return (buf);
}

void	ftMousePos(Game *Game)
{
	char *ret;
	static Vector2 lastPos;
	Game->mouse.pos = GetMousePosition();

	DrawRectangle(0, 0, 300, 30, DARKGRAY);

	if (Game->mouse.pos.x >= 0 && Game->mouse.pos.x <= Game->screenWidth
		&& Game->mouse.pos.y >= 0 && Game->mouse.pos.y <= Game->screenHeight)
	{
		ret = ft_ftoa(Game->mouse.pos.x, 0);
		DrawText("Mouse pos X:", 10, 10, 14, LIGHTGRAY);
		DrawText(ret, 110, 10, 12, LIGHTGRAY);

		ret = ft_ftoa(Game->mouse.pos.y, 0);
		DrawText("Y:", 190, 10, 14, LIGHTGRAY);
		DrawText(ret, 210, 10, 12, LIGHTGRAY);

		// lastPos = Game->mouse.pos;
	}
	else
	{
		ret = ft_ftoa(lastPos.x, 0);
		DrawText("Mouse pos X:", 10, 10, 14, LIGHTGRAY);
		DrawText(ret, 110, 10, 12, LIGHTGRAY);

		ret = ft_ftoa(lastPos.y, 0);
		DrawText("Y:", 190, 10, 14, LIGHTGRAY);
		DrawText(ret, 210, 10, 12, LIGHTGRAY);
	}
	lastPos = Game->mouse.pos;
}


void	ftMouseControl(Game *Game)
{
	ftMousePos(Game);

//--------------------------------------------------------------------------------------//
//** Select Box **//

	static Rectangle textBox1;
	static bool mouseOnText = false;
	static int letterCount;
	static int framesCounter;
	if (!letterCount || !framesCounter)
	{
		letterCount = 0;
		framesCounter = 0;
	}
	textBox1 = {1320, 70, 100, 20};
	if (CheckCollisionPointRec(Game->mouse.pos, textBox1))
		mouseOnText = true;
	else
		mouseOnText = false;
	if (mouseOnText)
	{
		// Set the window's cursor to the Box
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
			{
				Game->rotation[letterCount] = (char)key;
				Game->rotation[letterCount + 1] = '\0';
				letterCount++;
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount--;
			if (letterCount < 0)
				letterCount = 0;
			Game->rotation[letterCount] = '\0';
		}
	}
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	if (mouseOnText)
		framesCounter++;
}

//*** For change item color in side up panel ***//
void	ftWitchPanelIsSelected(Game *game, Player *player, Menu *menu)
{
	Vector2 mousePos = GetMousePosition();

	if (game->ctMenuUpButtons == 1)
	{
		if (game->selected2D.type == 2) // prop
		{
			DrawTextureRec(game->textCercleChrom, game->rectCercleChrom, {130, 100}, WHITE);
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x > 1330 && game->mouse.pos.x < 1480
				&& game->mouse.pos.y > 140 && game->mouse.pos.y < 280)
			{
				if (game->colorCt == false)
					game->colorCt = true;
				else
				{
					Color *colors = LoadImageColors(game->imgCercleChrom);
					int index = ((mousePos.y - 140) * game->imgCercleChrom.height) + mousePos.x - 1330;
					Color pixel = colors[index];
					game->selected2D.prop->ftChangeColor(pixel);
				}
			}
			DrawRectangle(38, 143, 68, 68, BLACK);
			DrawRectangle(40, 145, 64, 64, game->selected2D.prop->ftReturnColor());
		}
		else if (game->selected2D.type == 3) // item
		{
			DrawTextureRec(game->textCercleChrom, game->rectCercleChrom, {130, 100}, WHITE);
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && game->mouse.pos.x > 1330 && game->mouse.pos.x < 1480
				&& game->mouse.pos.y > 140 && game->mouse.pos.y < 280)
			{
				if (game->colorCt == false)
					game->colorCt = true;
				else
				{
					Color *colors = LoadImageColors(game->imgCercleChrom);
					int index = ((mousePos.y - 140) * game->imgCercleChrom.height) + mousePos.x - 1330;
					Color pixel = colors[index];
					game->selected2D.item->ftChangeColor(pixel);
				}
			}
			DrawRectangle(38, 143, 68, 68, BLACK);
			DrawRectangle(40, 145, 64, 64, game->selected2D.item->ftReturnColor());
		}
	}
	else if (game->ctMenuUpButtons == 0)
	{
		ftSideUpControlMenu2D(game, player, menu);
	}
}

//*** Draw a list of items in side up panel in list panel ***//
void	ftDrawListPanel(Game *game, Player *player, std::vector<SquareProps> *blocks,
			EnvItems **envItems, Camera2D *camera)
{
	if (game->ctMenuUpButtons == 2)
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		std::string 	name = player->ftReturnPlayerName();
		int 			nbr = 0;
		static float	mouseWheel = 0; //	Slide panel Up/Down
		static float	lastMouseWheel;
		Rectangle		box;

		lastMouseWheel = mouseWheel;
		if (game->mouse.pos.x >= game->screenWidth - 300 && game->mouse.pos.x <= game->screenWidth
			&& game->mouse.pos.y >= 40 && game->mouse.pos.y <= game->screenHeight / 3 + 40)
		{
			mouseWheel += ((float)GetMouseWheelMove() * 8);
		}

		if (mouseWheel > 0)
		{
			mouseWheel = 0;
		}

//------------------------------------------------------------------------------//
// Draw text for player in side up panel //

		DrawText("--Players--", 10, 30 + mouseWheel, 16, PURPLE);

		const char	*tmp = name.c_str();
		box = {(float)game->screenWidth - 300, 55 + mouseWheel + 40, 290, 12};

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionPointRec(rayPos, box))
			{
				game->selected2D.lastType = game->selected2D.type;
				game->selected2D.lastPlayer = game->selected2D.player;
				game->selected2D.lastNbr = game->selected2D.nbr;
				game->selected2D.type = 1;
				game->selected2D.nbr = 0;
				game->selected2D.player = player->ftReturnPlayer();
				game->mouse.clickName = 1;
				game->colorCt = false;
			}
		}
		else if (game->mouse.clickName != 1)
			DrawText(tmp, 10, 55 + mouseWheel, 12, LIGHTGRAY);
		else
			DrawText(tmp, 10, 55 + mouseWheel, 12, GREEN);

//------------------------------------------------------------------------------//
// Draw text for blocks in side up panel //

		DrawText("--Blocks--", 10, 75 + mouseWheel, 16, PURPLE);
		for (int i = 0; i < blocks->size(); i ++)
		{
			name = blocks->at(i).ftReturnName();
			tmp = name.c_str();
			box = {(float)game->screenWidth - 300, 100 + nbr + mouseWheel + 40, 290, 12};

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (CheckCollisionPointRec(rayPos, box))
				{
					game->selected2D.lastType = game->selected2D.type;
					game->selected2D.lastProp = game->selected2D.prop;
					game->selected2D.lastNbr = game->selected2D.nbr;
					game->selected2D.type = 2;
					game->selected2D.nbr = i;
					game->selected2D.prop = &blocks->at(i);
					game->mouse.clickName = 600 + i;
					game->colorCt = false;
				}
			}
			else if (game->mouse.clickName != 600 + i)
				DrawText(tmp, 10, 100 + nbr + mouseWheel, 12, LIGHTGRAY);
			else
				DrawText(tmp, 10, 100 + nbr + mouseWheel, 12, GREEN);
			nbr += 15;
		}

//------------------------------------------------------------------------------//
// Draw text for platforms in side up panel //

		DrawText("--Platforms--", 10, 105 + nbr + mouseWheel, 16, PURPLE);
		nbr += 25;
		for (int i = 0; i < game->nbrEnvi; i++)
		{
			name = envItems[i]->ftReturnName();
			tmp = name.c_str();
			box = {(float)game->screenWidth - 300, 147 + nbr + mouseWheel, 290, 12};

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (CheckCollisionPointRec(mousePos, box))
				{
					game->selected2D.lastType = game->selected2D.type;
					game->selected2D.lastItem = game->selected2D.item;
					game->selected2D.lastNbr = game->selected2D.nbr;
					game->selected2D.type = 3;
					game->selected2D.nbr = i;
					game->selected2D.item = envItems[i];
					game->colorCt = false;
					game->mouse.clickName = 300 + i;
				}
			}
			else if (game->mouse.clickName != 300 + i)
				DrawText(tmp, 10, 105 + nbr + mouseWheel, 12, LIGHTGRAY);
			else
				DrawText(tmp, 10, 105 + nbr + mouseWheel, 12, GREEN);
			nbr += 15;
		}
		if (105 + nbr + mouseWheel < 250)
		{
			mouseWheel = lastMouseWheel;
		}
	}
}

void	ftSideUpMenu2D(Game *game, Player *player, std::vector<SquareProps> *blocks,
			EnvItems **envItems, Menu *menu, MultipleCam2D *allCameras)
{
	ftWitchPanelIsSelected(game, player, menu);
	ftDrawListPanel(game, player, blocks, envItems, &allCameras->camera01.camera);
	ftMouseControl(game);
}

//*** 	Init position and size for box andt text for enter	***//
//***	text for move objet on screen                 		***//
void	ftInitTextBoxSideUp(Game *game)
{
	game->textBoxSideUp.RightBox0.hitBox = {1260, 80, 75, 20};
	game->textBoxSideUp.RightBox0.writeBox = {60, 38, 75, 20};
	game->textBoxSideUp.RightBox0.posTextBox = {10, 42};

	game->textBoxSideUp.LeftBox0.hitBox = {1400, 80, 75, 20};
	game->textBoxSideUp.LeftBox0.writeBox = {200, 38, 75, 20};
	game->textBoxSideUp.LeftBox0.posTextBox = {150, 42};

	game->textBoxSideUp.RightBox1.hitBox = {1260, 110, 75, 20};
	game->textBoxSideUp.RightBox1.writeBox = {60, 68, 75, 20};
	game->textBoxSideUp.RightBox1.posTextBox = {10, 72};

	game->textBoxSideUp.LeftBox1.hitBox = {1400, 110, 75, 20};
	game->textBoxSideUp.LeftBox1.writeBox = {200, 68, 75, 20};
	game->textBoxSideUp.LeftBox1.posTextBox = {150, 72};
}
