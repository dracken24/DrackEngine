/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		routine2D.hpp         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../myIncludes/game.hpp"

void ftRoutine(Game *game, Player *player, Menu *menu, Camera2D *camera,
	std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems)
{
	static int lastAction;
	static int cameraOption = 0;

	lastAction = player->ftReturnCt();
	if (game->ct_action >= 60 || lastAction != player->ftReturnCt())
		game->ct_action = 0;
	game->delta = GetFrameTime();

	game->cameraUpdaters[cameraOption](game, camera, player, envItems->size(), game->delta, game->screenWidth, game->screenHeight);
	ftUpdatePlayer(game, player, menu, envItems, envItems->size(), game->delta);
	if (lastAction != player->ftReturnCt())
		game->ct_action = 0;

	if (game->mouse.pos.x > 0 && game->mouse.pos.x < game->screenWidth - 300
		&& game->mouse.pos.y > 40 && game->mouse.pos.y < game->screenHeight)
	{
		camera->zoom += ((float)GetMouseWheelMove() * 0.05f);
		if (camera->zoom > 3.0f)
			camera->zoom = 3.0f;
		else if (camera->zoom < 0.25f)
			camera->zoom = 0.25f;
	}

	/*********************************************** Gravity ***************************************************/
	ftGravityGestion(game, player, blocks);

	for (int i = 0; i < blocks->size(); i++)
	{
		ftUseGravity(&blocks->at(i), envItems, game->delta, envItems->size());
	}

	/********************************************** Collision **************************************************/

	Rectangle	plyCollBox = player->ftReturnCollisionBox();
	Vector2		AdjCollBox = player->ftReturnAjustCollisionBox();
	Vector2		plyPos = player->ftReturnPlayerPosition();

	ftGestionProps(game, blocks, envItems, game->delta, envItems->size());
	player->ftSetCollosionBox((Vector2){plyPos.x + AdjCollBox.x, plyPos.y - AdjCollBox.y},
		(Vector2){plyCollBox.width, plyCollBox.height}, (Vector2){AdjCollBox.x, AdjCollBox.y});

	// DrawRectangleRec(plyCollBox, BLACK); 	// Player collision box
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
		for (int i = 0; i < blocks->size(); i++)
		{
			blocks->at(i).ftSetPos((Vector2){200 - dist, 200});
			dist += 50;
		}
	}
	else if (IsKeyPressed(KEY_P))
	{
		float dist = 0;
		camera->zoom = 1.0f;
		player->ftSetPosition((Vector2){500.0f, 300.0f});
		for (int i = 0; i < blocks->size(); i++)
		{
			blocks->at(i).ftSetPos((Vector2){200 - dist, 200});
			blocks->at(i).ftSetSpeed(0);
			blocks->at(i).ftSetSpeedModifier(0, 'X');

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
	ftKeyGestion(game, player, menu, game->delta);
}

/*******************************************************************************************
	Gestion Des objets (Plateforms wlakable, objets du decor ...)
*******************************************************************************************/
void	ftGestionProps(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, float deltaTime, int envItemsLength)
{
	static float k;
	if (!k || k > 360)
		k = 0;
	for (int i = 0; i < envItemsLength; i++)
		DrawRectangleRec(envItems->at(i).ftReturnRectangle(), envItems->at(i).ftReturnColor());
	
	for (int i = 0; i < blocks->size(); i++)
	{
		blocks->at(i).ftMovePos((Vector2){blocks->at(i).ftReturnSpeedModifier('X'), 0});

			DrawRectanglePro(blocks->at(i).ftReturnRectangle(), (Vector2){0, 0}, k, blocks->at(i).ftReturnColor()); 

		blocks->at(i).ftSetSpeedModifier(blocks->at(i).ftReturnSpeedModifier('X') / 1.01, 'X');
	}
	k += atof(game->rotation);
}
/******************************************************************************************/

void	ftUpdatePlayer(Game *game, Player *player, Menu *menu,
			std::vector<EnvItems> *envItems, int envItemsLength, float delta)
{
	player->ftChangeLastY(player->ftReturnPlayerPositionY());
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
