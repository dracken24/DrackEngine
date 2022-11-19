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

	// Draw on screen
	// textBox1 = {125, 36, 100, 20};
	// DrawText("Blocks Rotation:", 10, 40, 14, LIGHTGRAY);
	// DrawRectangleRec(textBox1, LIGHTGRAY);
	// if (mouseOnText)
	// 	DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, RED);
	// else
	// 	DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, LIGHTGRAY);
	// DrawText(Game->rotation, (int)textBox1.x + 5 , (int)textBox1.y + 4, 14, MAROON);
	// if (mouseOnText)
	// {
	// 	if (letterCount < MAX_INPUT_CHARS)
	// 	{
	// 		// Draw blinking underscore char
	// 		if (((framesCounter / 20) % 2) == 0)
	// 			DrawText("_", (int)textBox1.x + MeasureText(Game->rotation, 14), (int)textBox1.y + 12, 14, MAROON);
	// 	}
	// }
}

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
					game->selected2D.prop->ftInitColor(pixel);
				}
			}
			DrawRectangle(38, 143, 68, 68, BLACK);
			DrawRectangle(40, 145, 64, 64, game->selected2D.prop->ftReturnRecColor());
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
					game->selected2D.item->color = pixel;
				}
			}
			DrawRectangle(38, 143, 68, 68, BLACK);
			DrawRectangle(40, 145, 64, 64, game->selected2D.item->color);
		}
	}
	else if (game->ctMenuUpButtons == 0)
	{
		ftSideUpControlMenu2D(game, player, menu);
	}
}

void	ftDrawListPanel(Game *game, Player *player, Props *blocks, EnvItems *envItems, Camera2D *camera)
{
	if (game->ctMenuUpButtons == 2)
	{
		std::string 	name = player->ftReturnPlayerName();
		int 			nbr = 0;
		static float	mouseWheel = 0; //	Slide panel Up/Down

		if (game->mouse.pos.x >= game->screenWidth - 300 && game->mouse.pos.x <= game->screenWidth
			&& game->mouse.pos.y >= 40 && game->mouse.pos.y <= game->screenHeight / 3 + 40)
		{
			mouseWheel += ((float)GetMouseWheelMove() * 4);
		}

		DrawText("--Players--", 10, 30 + mouseWheel, 16, PURPLE);

		const char	*tmp = name.c_str();
		DrawText(tmp, 10, 55 + mouseWheel, 12, LIGHTGRAY);

		DrawText("--Blocks--", 10, 75 + mouseWheel, 16, PURPLE);
		for (int i = 0; i < blocks->ftReturnNbr(); i ++)
		{
			name = blocks->ftReturnSquareName(i);
			tmp = name.c_str();
			DrawText(tmp, 10, 100 + nbr + mouseWheel, 12, LIGHTGRAY);
			nbr += 15;
		}

		DrawText("--Platforms--", 10, 105 + nbr + mouseWheel, 16, PURPLE);
		nbr += 25;
		for (int i = 0; i < envItems->ftReturnEnviAllNbr(); i++)
		{
			name = envItems->ftReturnName(i);
			tmp = name.c_str();
			DrawText(tmp, 10, 105 + nbr + mouseWheel, 12, LIGHTGRAY);
			nbr += 15;
		}
	}
}

void	ftSideUpMenu2D(Game *game, Player *player, Props *blocks, EnvItems *envItems, Menu *menu, MultipleCam2D *allCameras)
{
	ftWitchPanelIsSelected(game, player, menu);
	ftDrawListPanel(game, player, blocks, envItems, &allCameras->camera01.camera);
	ftMouseControl(game);
}

//*** 	Init position and size for box andt text for enter	***//
//***	text for move objet on screen                 	***//
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
