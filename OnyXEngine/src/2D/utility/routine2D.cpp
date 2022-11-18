#include "../../../myIncludes/game.hpp"

void ftRoutine(Game *game, Player *player, Menu *menu, Camera2D *camera, SquareProps *blocks, EnvItems *envItems)
{
	static int lastAction;
	static int cameraOption = 0;

	int envItemsLength = envItems->ftReturnEnviAllNbr();
	lastAction = player->ftReturnCt();
	if (game->ct_action >= 60 || lastAction != player->ftReturnCt())
		game->ct_action = 0;
	game->delta = GetFrameTime();

	game->cameraUpdaters[cameraOption](game, camera, player, envItemsLength, game->delta, game->screenWidth, game->screenHeight);
	ftUpdatePlayer(game, player, menu, envItems, envItemsLength, game->delta);
	if (lastAction != player->ftReturnCt())
		game->ct_action = 0;

	camera->zoom += ((float)GetMouseWheelMove() * 0.05f);
	if (camera->zoom > 3.0f)
		camera->zoom = 3.0f;
	else if (camera->zoom < 0.25f)
		camera->zoom = 0.25f;

	// ftKeyGestion(Game, player, menu, Game->delta);

	/*********************************************** Gravity ***************************************************/
	ftGravityGestion(game, player, blocks);
	for (int i = 0; i < game->nbrSquareProps; i++)
	{
		ftUseGravity(blocks[i].ftReturnCopySquareProp(), envItems, game->delta, envItemsLength);
	}

	/********************************************** Collision **************************************************/

	Rectangle	plyCollBox = player->ftReturnCollisionBox();
	Vector2		AdjCollBox = player->ftReturnAjustCollisionBox();
	Vector2		plyPos = player->ftReturnPlayerPosition();

	ftGestionProps(game, blocks, envItems, game->delta, envItemsLength);
	player->ftSetCollosionBox((Vector2){plyPos.x + AdjCollBox.x, plyPos.y - AdjCollBox.y},
							  (Vector2){plyCollBox.width, plyCollBox.height}, (Vector2){AdjCollBox.x, AdjCollBox.y});

	DrawRectangleRec(plyCollBox, BLACK); 	// Player collision box
	if (player->ftReturnFace() == 0) 		// Weapon collision box use
	{
		player->ftNewWeaponCollBoxPos(plyCollBox.x + plyCollBox.width, 'X');
		player->ftNewWeaponCollBoxPos(plyCollBox.y, 'Y');
	}
	else if (player->ftReturnFace() == 1) 	// Weapon collision box use
	{
		player->ftNewWeaponCollBoxPos(plyCollBox.x - plyCollBox.width - 5, 'X');
		player->ftNewWeaponCollBoxPos(plyCollBox.y, 'Y');
	}
	// DrawRectangleRec(player->ftReturnWeaponCollRect(), PURPLE); // Weapon collision box

	ftImgsGestion(game, player);

	/***********************************************************************************************************/

	if (IsKeyPressed(KEY_R))
	{
		float dist = 0;
		for (int i = 0; i < game->nbrSquareProps; i++)
		{
			blocks[i].ftInitPosition((Vector2){200, 200 - dist});
			blocks[i].ftInitPosition((Vector2){200 - dist , 200});
			dist += 50;
		}
	}
	if (IsKeyPressed(KEY_P))
	{
		float dist = 0;
		camera->zoom = 1.0f;
		player->ftSetPosition((Vector2){500.0f, 300.0f});
		for (int i = 0; i < game->nbrSquareProps; i++)
		{
			blocks[i].ftInitPosition((Vector2){200 - dist, 200});
			blocks[i].ftSetSpeed(0);
			blocks[i].ftSetSpeedModifier(0, 'X');

			dist += 50;
		}
	}
	else if (IsKeyDown(KEY_I))
	{
		DrawText("Controls:", 20, 20, 10, BLACK);
		DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
		DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
		DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
		DrawText("- Mouse Button Left to Attack", 40, 100, 10, DARKGRAY);
	}
	// ftSideMenu(Game, player);
	ftKeyGestion(game, player, menu, game->delta);
}

/*******************************************************************************************
	Gestion Des objets (Plateforms wlakable, objets du decor ...)
*******************************************************************************************/
void	ftGestionProps(Game *game, SquareProps *blocks, EnvItems *envItems, float deltaTime, int envItemsLength)
{
	static float k;
	if (!k || k > 360)
		k = 0;
	for (int i = 0; i < envItemsLength; i++)
		DrawRectangleRec(envItems->ftReturnRectangle(i), envItems->ftReturnEnviColor(i));
	
	for (int i = 0; i < game->nbrSquareProps; i++)
	{
		Rectangle	block = blocks[i].ftReturnRectangle();

		blocks[i].ftMovePositionVec((Vector2){blocks[i].ftReturnSpeedModifier('X') + block.width / 2, blocks[i].ftReturnSpeedModifier('Y') + block.height / 2});
		block = blocks[i].ftReturnRectangle();
		DrawRectanglePro(block, (Vector2){block.width / 2, block.height / 2}, k, blocks[i].ftReturnRecColor());
		blocks[i].ftMovePositionVec((Vector2){-block.width / 2, -block.height / 2});
		blocks[i].ftSetSpeedModifier(blocks[i].ftReturnSpeedModifier('X') / 1.01, 'X');
	}
	k += atof(game->rotation);
}
/******************************************************************************************/

void	ftUpdatePlayer(Game *game,Player *player, Menu *menu, EnvItems *envItems, int envItemsLength, float delta)
{
	player->ftChangeLastY(player->ftReturnPlayerPositionY());

	// ftKeyGestion(Game, player, menu, delta);
	ftUsePlayerGravity(player, envItems, delta, envItemsLength);

	if (player->ftReturnLastY() < player->ftReturnPlayerPositionY() && player->ftReturnAttackCt() == 0)
	{
		player->ftChangeCt(5);
	}
	else if (player->ftReturnLastY() == player->ftReturnPlayerPositionY() && player->ftReturnCt() == 5 && player->ftReturnAttackCt() == 0)
	{
		player->ftChangeCt(0);
	}
}

void ftUpdateCameraCenter(Game *game, Camera2D *camera, Player *player, int envItemsLength, float delta, int width, int height)
{
	camera->offset = (Vector2){game->screenWidth / 2.0f - 150, game->screenHeight / 2.0f};
	camera->target = player->ftReturnPlayerPosition();
}
