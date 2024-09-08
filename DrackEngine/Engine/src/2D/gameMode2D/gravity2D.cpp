/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   gravity2D.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../myIncludes/game.hpp"

void	ftGravityX(Game *game, Player *player, std::vector<SquareProps> *blocks)
{
	Rectangle	plyCollBox = player->ftReturnCollisionBox();
	float		speed = PLAYER_HOR_SPD * game->delta;

	for (int j = 0; j < blocks->size(); j++)
	{
		Rectangle propRect1 = blocks->at(j).ftReturnRectangle();
		float totalForce = 0.0f;

		for (int k = 0; k < blocks->size(); k++)
		{
			if (j == k) continue;

			Rectangle propRect2 = blocks->at(k).ftReturnRectangle();
			if (CheckCollisionRecs(propRect1, propRect2))
			{
				float overlap = 0.0f;
				if (propRect1.x < propRect2.x)
				{
					overlap = (propRect1.x + propRect1.width) - propRect2.x;
					totalForce -= overlap;
				}
				else
				{
					overlap = (propRect2.x + propRect2.width) - propRect1.x;
					totalForce += overlap;
				}
			}
		}

		// Appliquer la force totale au bloc
		float forceMultiplier = 0.5f; // Ajustez ce multiplicateur selon vos besoins
		blocks->at(j).ftChangeSpeedModifier(totalForce * forceMultiplier, 'X');
	

		if (CheckCollisionRecs(propRect1, plyCollBox)) // Collision player
		{
			if (propRect1.x - propRect1.width / 2 > plyCollBox.x + 0./(2)) // Right
			{
				blocks->at(j).ftChangeSpeedModifier(speed / 4.0f, 'X');
			}
			else // Left
			{
				blocks->at(j).ftChangeSpeedModifier(-speed / 4.0f, 'X');
			}
		}
		if (CheckCollisionRecs(propRect1, player->ftReturnWeaponCollRect()) && player->ftReturnDoAttack() == true) // Collision weapon
		{
			if (player->ftReturnFace() == 0) // Right
			{
				blocks->at(j).ftChangeSpeedModifier(speed * 5.0f, 'X');
			}
			else // Left
			{
				blocks->at(j).ftChangeSpeedModifier(-speed * 5.0f, 'X');
			}
		}
	}
	player->ftChangeDoAttack(false);
}

void	ftGravityGestion(Game *Game, Player *player, std::vector<SquareProps> *blocks)
{
	ftGravityX(Game, player, blocks);
}

void	ftUsePlayerGravity(Player *player, std::vector<EnvItems> *envItems, float delta, int envItemsLength)
{
	int			hitObstacle = 0;
	Rectangle	tmpCollBox = player->ftReturnCollisionBox();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItems	*ei(&envItems->at(i));
		Rectangle	rect = ei->ftReturnRectangle();
		Vector2		*p = player->ftReturnPlayerPositionPtr();

		if (ei->ftReturnBlocking() &&             							// Stop Player falling
			rect.x <= tmpCollBox.x + tmpCollBox.width &&
			rect.x + rect.width >= tmpCollBox.x &&
			rect.y >= p->y &&
			rect.y <= p->y + player->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			player->ftSetSpeed(0);
			p->y = rect.y;
		}
		else if (ei->ftReturnBlocking() &&         							// Hit plafond
			rect.x <= p->x &&
			rect.x + rect.width >= tmpCollBox.x + tmpCollBox.width &&
			rect.y + rect.height > tmpCollBox.y &&
			CheckCollisionRecs(rect, tmpCollBox))
		{
			player->ftSetSpeed(25);
		}
		else if (CheckCollisionRecs(rect, tmpCollBox) && ei->ftReturnBlocking())
		{
			if (player->ftReturnFace() == 0 && player->ftReturnCollX() == false)
			{
				player->ftMovePosition(-PLAYER_HOR_SPD * delta, 0);
			}
			else if (player->ftReturnFace() == 1 && player->ftReturnCollX() == false)
			{
				player->ftMovePosition(PLAYER_HOR_SPD * delta, 0);
			}
			player->ftChangeCollX(true);
		}
	}
	if (!hitObstacle)
	{
		player->ftMovePosition(0, player->ftReturnSpeed() * delta);
		player->ftChangeSpeed(G * delta);
		player->ftChangeJump(false);
	}
	else
	{
		player->ftChangeJump(true);
	}
}

void	ftUseGravity(SquareProps *prop, std::vector<EnvItems> *envItems, float delta, int envItemsLength)
{
	int 		hitObstacle = 0;
	Rectangle	tmpProp = prop->ftReturnRectangle();
	Vector2 p	= prop->ftReturnPos();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItems *ei(&envItems->at(i));
		Rectangle rect = ei->ftReturnRectangle();
		if (ei->ftReturnBlocking() &&
			rect.x - tmpProp.width <= p.x &&
			rect.x + rect.width >= p.x &&
			rect.y - tmpProp.height >= p.y &&
			rect.y - tmpProp.height<= p.y + prop->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			prop->ftSetSpeed(prop->ftReturnSpeed() * -1 / 2); // Rebound on ground
			p.y = rect.y;
			prop->ftSetPos((Vector2){tmpProp.x, p.y - tmpProp.height});
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') / 1.25, 'X'); // Friction in x on ground
		}
		else if (CheckCollisionRecs(rect, tmpProp) && ei->ftReturnBlocking())
		{	
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') * - 1./(2), 'X');
		}
	}

	if (!hitObstacle)
	{
		prop->ftMovePos({0, prop->ftReturnSpeed() * delta / (float)1.1});
		prop->ftChangeSpeed(G * delta);
	}
}

