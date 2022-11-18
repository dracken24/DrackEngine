#include "../../../myIncludes/game.hpp"

void ftRoutine(Game *Game, Player *player, Menu *menu, Camera2D *camera, Props *blocks, EnvItems *envItems)
{
	static int lastAction;
	static int cameraOption = 0;

	int envItemsLength = envItems->ftReturnEnviAllNbr();
	lastAction = player->ftReturnCt();
	if (Game->ct_action >= 60 || lastAction != player->ftReturnCt())
		Game->ct_action = 0;
	Game->delta = GetFrameTime();

	Game->cameraUpdaters[cameraOption](Game, camera, player, envItemsLength, Game->delta, Game->screenWidth, Game->screenHeight);
	ftUpdatePlayer(Game, player, menu, envItems, envItemsLength, Game->delta);
	if (lastAction != player->ftReturnCt())
		Game->ct_action = 0;

	camera->zoom += ((float)GetMouseWheelMove() * 0.05f);
	if (camera->zoom > 3.0f)
		camera->zoom = 3.0f;
	else if (camera->zoom < 0.25f)
		camera->zoom = 0.25f;

	// ftKeyGestion(Game, player, menu, Game->delta);

	/*********************************************** Gravity ***************************************************/
	ftGravityGestion(Game, player, blocks);
	for (int i = 0; i < blocks->ftReturnNbr(); i++)
	{
		ftUseGravity(blocks->ftReturnSquareProp(i), envItems, Game->delta, envItemsLength);
	}

	/********************************************** Collision **************************************************/

	Rectangle	plyCollBox = player->ftReturnCollisionBox();
	Vector2		AdjCollBox = player->ftReturnAjustCollisionBox();
	Vector2		plyPos = player->ftReturnPlayerPosition();

	ftGestionProps(Game, blocks, envItems, Game->delta, envItemsLength);
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

	ftImgsGestion(Game, player);

	/***********************************************************************************************************/

	if (IsKeyPressed(KEY_R))
	{
		float dist = 0;
		for (int i = 0; i < blocks->ftReturnNbr(); i++)
		{
			blocks->ftSetPosSquareProp((Vector2){200, 200 - dist}, i);
			blocks->ftSetPosSquareProp((Vector2){200 - dist , 200}, i);
			dist += 50;
		}
	}
	if (IsKeyPressed(KEY_P))
	{
		float dist = 0;
		camera->zoom = 1.0f;
		player->ftSetPosition((Vector2){500.0f, 300.0f});
		for (int i = 0; i < blocks->ftReturnNbr(); i++)
		{
			blocks->ftSetPosSquareProp((Vector2){200 - dist, 200}, i);
			blocks->ftSetSpeed(0, i);
			blocks->ftSetSpeedModifier(0, 'X', i);

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
	ftKeyGestion(Game, player, menu, Game->delta);
}

/*******************************************************************************************
	Gestion Des objets (Plateforms wlakable, objets du decor ...)
*******************************************************************************************/
void	ftGestionProps(Game *Game, Props *blocks, EnvItems *envItems, float deltaTime, int envItemsLength)
{
	static float k;
	if (!k || k > 360)
		k = 0;
	for (int i = 0; i < envItemsLength; i++)
		DrawRectangleRec(envItems->ftReturnRectangle(i), envItems->ftReturnEnviColor(i));
	
	for (int i = 0; i < blocks->ftReturnNbr(); i++)
	{
		Rectangle	block = blocks->ftReturnRectangleSqPr(i);

		blocks->ftMoveSquareProp((Vector2){blocks->ftReturnSpeedModifier('X', i) + block.width / 2, blocks->ftReturnSpeedModifier('Y', i) + block.height / 2}, i);
		block = blocks->ftReturnRectangleSqPr(i);
		DrawRectanglePro(block, (Vector2){block.width / 2, block.height / 2}, k, blocks->ftReturnRecColorSqPr(i));
		blocks->ftMoveSquareProp((Vector2){-block.width / 2, -block.height / 2}, i);
		blocks->ftSetSpeedModifier(blocks->ftReturnSpeedModifier('X', i) / 1.01, 'X', i);
	}
	k += atof(Game->rotation);
}
/******************************************************************************************/

void	ftUpdatePlayer(Game *Game,Player *player, Menu *menu, EnvItems *envItems, int envItemsLength, float delta)
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

void ftUpdateCameraCenter(Game *Game, Camera2D *camera, Player *player, int envItemsLength, float delta, int width, int height)
{
	camera->offset = (Vector2){Game->screenWidth / 2.0f - 150, Game->screenHeight / 2.0f};
	camera->target = player->ftReturnPlayerPosition();
}
