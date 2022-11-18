#include "../../myIncludes/game.hpp"

void	ftResetPlayerStrPanSideDown(Game *game);
void	ftResetItemsStrPanSideDown(Game *game);
void	ftResetPropsStrPanSideDown(Game *game);
void	ftEnterVarsPlayer(Game *game);
void	ftEnterVarsProp(Game *game);
void	ftEnterVarsItem(Game *game);

//*** Fon write on select box right down panel, in build mode
//                                Collision Box   /    Visual Box     /               / Affichable/ Variable Struct/ Nbr to put/ nbr in array
void    ftSelectBox(Game *Game, Rectangle textBox1, Rectangle textBox2, Vector2 posText, char *name, char *varName, char *nbr, int ct)
{
	// static Rectangle textBox1;
	static bool mouseOnText[512];
	static int 	letterCount[512];
	static int 	framesCounter[512];

	if (!name && !varName && !nbr)
	{
		framesCounter[ct] = 0;
		letterCount[ct] = 0;
		return;
	}

	mouseOnText[ct] = false;
	if (!letterCount[ct] || !framesCounter[ct])
	{
		letterCount[ct] = 0;
	}

	if (CheckCollisionPointRec(Game->mouse.pos, textBox1))
		mouseOnText[ct] = true;
	else
		mouseOnText[ct] = false;
	if (mouseOnText[ct])
	{
		// Set the window's cursor to the Box
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount[ct] < MAX_INPUT_CHARS))
			{
				varName[letterCount[ct]] = (char)key;
				varName[letterCount[ct] + 1] = '\0';
				letterCount[ct]++;
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount[ct]--;
			if (letterCount[ct] < 0)
				letterCount[ct] = 0;
			varName[letterCount[ct]] = '\0';
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
	if (mouseOnText[ct])
		framesCounter[ct]++;

	// Draw on screen
	DrawText(name, posText.x, posText.y, 14, LIGHTGRAY);
	DrawRectangleRec(textBox2, LIGHTGRAY);
	if (mouseOnText[ct])
		DrawRectangleLines((int)textBox2.x - 2, (int)textBox2.y - 2, (int)textBox2.width + 2, (int)textBox2.height + 2, MYDARKGREEN);
	else
		DrawRectangleLines((int)textBox2.x, (int)textBox2.y, (int)textBox2.width, (int)textBox2.height, LIGHTGRAY);
	DrawText(varName, (int)textBox2.x + 5, (int)textBox2.y + 4, 14, DARKGREEN);
	if (mouseOnText[ct])
	{
		if (letterCount[ct] < MAX_INPUT_CHARS)
		{
			if (((framesCounter[ct] / 20) % 2) == 0)
				DrawText("_", (int)textBox2.x + MeasureText(varName, 14), (int)textBox2.y + 12, 14, MYDARKGREEN);
		}
	}
	else if (varName[0] == '\0')
	{
		DrawText(nbr, (int)textBox2.x + MeasureText(varName, 14) + 2, (int)textBox2.y + 4, 14, DARKPURPLE);
	}
}

//*** Draw variables on side right down panel ***//
void	ftDrawVarsRiDownPanel(Game *game)
{
	int nbr = game->selected2D.nbr;

	if (game->selected2D.nbr != game->selected2D.lastNbr || game->selected2D.type != game->selected2D.lastType)
	{
		if (game->selected2D.lastType == 1) // Player
		{
			ftResetPlayerStrPanSideDown(game);
			for (int i = 0; i < 8; i++)
			{
				ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, i);
			}
			
			game->selected2D.lastNbr = game->selected2D.nbr;
			game->selected2D.lastType= game->selected2D.type;
		}
		else if (game->selected2D.lastType == 2) // Items Blocks Props
		{
			ftResetPropsStrPanSideDown(game);

			for (int i = 0; i < 4; i++)
			{
				ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, i + 100);
			}
			
			game->selected2D.lastNbr = game->selected2D.nbr;
			game->selected2D.lastType = game->selected2D.type;
		}
		else if (game->selected2D.lastType == 3) // Platforms
		{
			ftResetItemsStrPanSideDown(game);

			for (int i = 0; i < 4; i++)
			{
				ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, i + 200);
			}

			game->selected2D.lastNbr = game->selected2D.nbr;
			game->selected2D.lastType = game->selected2D.type;
		}
	}

	TrioBox		box0 = game->textBoxSideUp.RightBox0;
	TrioBox		box1 = game->textBoxSideUp.LeftBox0;
	TrioBox		box2 = game->textBoxSideUp.RightBox1;
	TrioBox		box3 = game->textBoxSideUp.LeftBox1;

	if (game->selected2D.type == 1) // Player selected
	{
		Rectangle   recPlayer = game->selected2D.player->FtReturnRectanglePlayer();
		VarChar     *varsPlayer = game->selected2D.player->ftReturnVarsChar();

		char *tmp = ft_ftoa(recPlayer.x, 0);
		ftSelectBox(game, box0.hitBox, box0.writeBox, box0.posTextBox, "Pos X:", varsPlayer->plyPosX, tmp, 0);
		
		tmp = ft_ftoa(recPlayer.y, 0);
		ftSelectBox(game, box1.hitBox, box1.writeBox, box1.posTextBox, "Pos Y:", varsPlayer->plyPosY, tmp, 1);
		
		tmp = ft_ftoa(recPlayer.width, 0);
		ftSelectBox(game, box2.hitBox, box2.writeBox, box2.posTextBox, "Width:", varsPlayer->plyWidth, tmp, 2);

		tmp = ft_ftoa(recPlayer.height, 0);
		ftSelectBox(game, box3.hitBox, box3.writeBox, box3.posTextBox, "Height:", varsPlayer->plyHeight, tmp, 3);
	}
	else if (game->selected2D.type == 2) // Items Blocks Props
	{
		VarCharPr	*varsProp = game->selected2D.prop->ftReturnVarsProp();
		Rectangle   recProp = game->selected2D.prop->ftReturnRectangle();

		char *tmp = ft_ftoa(recProp.x, 0);
		ftSelectBox(game, box0.hitBox, box0.writeBox, box0.posTextBox, "Pos X:", varsProp->propPosX, tmp, 100);

		tmp = ft_ftoa(recProp.y, 0);
		ftSelectBox(game, box1.hitBox, box1.writeBox, box1.posTextBox, "Pos Y:", varsProp->propPosY, tmp, 101);

		tmp = ft_ftoa(recProp.width, 0);
		ftSelectBox(game, box2.hitBox, box2.writeBox, box2.posTextBox, "Width:", varsProp->propWidth, tmp, 102);

		tmp = ft_ftoa(recProp.height, 0);
		ftSelectBox(game, box3.hitBox, box3.writeBox, box3.posTextBox, "Height:", varsProp->propHeight, tmp, 103);
	}
	else if (game->selected2D.type == 3) // Platforms
	{
		VarCharEnvi	*varsEnvi = &game->selected2D.item->_varCharEnvi;
		Rectangle   recEnvi = game->selected2D.item->rect;

		char *tmp = ft_ftoa(recEnvi.x, 0);
		ftSelectBox(game, box0.hitBox, box0.writeBox, box0.posTextBox, "Pos X:", varsEnvi->enviPosX, tmp, 200);
		
		tmp = ft_ftoa(recEnvi.y, 0);
		ftSelectBox(game, box1.hitBox, box1.writeBox, box1.posTextBox, "Pos Y:", varsEnvi->enviPosY, tmp, 201);
		
		tmp = ft_ftoa(recEnvi.width, 0);
		ftSelectBox(game, box2.hitBox, box2.writeBox, box2.posTextBox, "Width:", varsEnvi->enviWidth, tmp, 202);
		
		tmp = ft_ftoa(recEnvi.height, 0);
		ftSelectBox(game, box3.hitBox, box3.writeBox, box3.posTextBox, "Height:", varsEnvi->enviHeight, tmp, 203);
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		// std::cout << "";
		if (game->selected2D.type == 1)
		{
			ftEnterVarsPlayer(game);
		}
		else if (game->selected2D.type == 2)
		{
			ftEnterVarsProp(game);
		}
		else if (game->selected2D.type == 3)
		{
			ftEnterVarsItem(game);
		}
	}
}

void	ftEnterVarsItem(Game *game)
{
	if (game->selected2D.item->_varCharEnvi.enviPosX[0] != '\0')
	{
		game->selected2D.item->rect.x = atof(game->selected2D.item->_varCharEnvi.enviPosX);
		game->selected2D.item->_varCharEnvi.enviPosX[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 200);
	}
	if (game->selected2D.item->_varCharEnvi.enviPosY[0] != '\0')
	{
		game->selected2D.item->rect.y = atof(game->selected2D.item->_varCharEnvi.enviPosY);
		game->selected2D.item->_varCharEnvi.enviPosY[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 201);
	}
	if (game->selected2D.item->_varCharEnvi.enviWidth[0] != '\0')
	{
		game->selected2D.item->rect.width = atof(game->selected2D.item->_varCharEnvi.enviWidth);
		game->selected2D.item->_varCharEnvi.enviWidth[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 202);
	}
	if (game->selected2D.item->_varCharEnvi.enviHeight[0] != '\0')
	{
		game->selected2D.item->rect.height = atof(game->selected2D.item->_varCharEnvi.enviHeight);
		game->selected2D.item->_varCharEnvi.enviHeight[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 203);
	}
}

void	ftEnterVarsProp(Game *game)
{
	VarCharPr *vars = game->selected2D.prop->ftReturnVarsProp();
	Rectangle rec = game->selected2D.prop->ftReturnRectangle();
	if (vars->propPosX[0] != '\0')
	{
		game->selected2D.prop->ftInitPosition({(float)atof(vars->propPosX), 0});
		vars->propPosX[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 100);
	}
	if (vars->propPosY[0] != '\0')
	{
		game->selected2D.prop->ftInitPosition({0, (float)atof(vars->propPosY)});
		vars->propPosY[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 101);
	}
	if (vars->propWidth[0] != '\0')
	{
		game->selected2D.prop->ftChangeWorH(atof(vars->propWidth), 'W');
		vars->propWidth[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 102);
	}
	if (vars->propHeight[0] != '\0')
	{
		game->selected2D.prop->ftChangeWorH(atof(vars->propHeight), 'H');
		vars->propHeight[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 103);
	}
}

void	ftEnterVarsPlayer(Game *game)
{
	VarChar *vars = game->selected2D.player->ftReturnVarsChar();
	if (vars->plyPosX[0] != '\0')
	{
		game->selected2D.player->ftChangePosition(atof(vars->plyPosX), game->selected2D.player->ftReturnCollBoxPos('Y'));
		vars->plyPosX[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 0);
	}
	if (vars->plyPosY[0] != '\0')
	{
		game->selected2D.player->ftChangePosition(game->selected2D.player->ftReturnCollBoxPos('X'), atof(vars->plyPosY));
		vars->plyPosY[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 1);
	}
	if (vars->plyWidth[0] != '\0')
	{
		game->selected2D.player->ftChangeCollisionBoxSize({(float)atof(vars->plyWidth), (float)game->selected2D.player->ftReturnCollBoxSize('H')});
		vars->plyWidth[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 2);
	}
	if (vars->plyHeight[0] != '\0')
	{
		game->selected2D.player->ftChangeCollisionBoxSize({(float)game->selected2D.player->ftReturnCollBoxSize('W'), (float)atof(vars->plyHeight)});
		vars->plyHeight[0] = '\0';
		ftSelectBox(game, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}, NULL, NULL, NULL, 3);
	}
}

void	ftResetPropsStrPanSideDown(Game *game)
{
	VarCharPr	*varsProp = game->selected2D.prop->ftReturnVarsProp();

	varsProp->propHeight[0] = '\0';
	varsProp->propWidth[0] = '\0';
	varsProp->propPosX[0] = '\0';
	varsProp->propPosY[0] = '\0';
}

void	ftResetItemsStrPanSideDown(Game *game)
{
	VarCharEnvi	*varsEnvi = &game->selected2D.item->_varCharEnvi;

	varsEnvi->enviHeight[0] = '\0';
	varsEnvi->enviWidth[0] = '\0';
	varsEnvi->enviPosX[0] = '\0';
	varsEnvi->enviPosY[0] = '\0';
}

void	ftResetPlayerStrPanSideDown(Game *game)
{
	VarChar *varsPlayer = game->selected2D.player->ftReturnVarsChar();

	varsPlayer->collBoxHeight[0] = '\0';
	varsPlayer->collBoxWidth[0] = '\0';
	varsPlayer->collBoxPosY[0] = '\0';
	varsPlayer->collBoxPosX[0] = '\0';
	varsPlayer->plyHeight[0] = '\0';
	varsPlayer->plyWidth[0] = '\0';
	varsPlayer->plyPosY[0] = '\0';
	varsPlayer->plyPosX[0] = '\0';
}
