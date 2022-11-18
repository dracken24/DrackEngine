#include "../../../myIncludes/game.hpp"

void	ftGravityX(Game *Game, Player *player, Props *blocks)
{
	Rectangle	plyCollBox = player->ftReturnCollisionBox();
	float		speed = PLAYER_HOR_SPD * Game->delta;

	for (int j = 0; j < blocks->ftReturnNbr(); j++)
	{
		Rectangle propRect1 = blocks->ftReturnRectangleSqPr(j);
		for (int k = 0; k < blocks->ftReturnNbr(); k++)
		{
			if (j == k)
				k++;

			Rectangle propRect2 = blocks->ftReturnRectangleSqPr(k);
			if (CheckCollisionRecs(propRect1, plyCollBox)) // Collision player
			{
				if (propRect1.x - propRect1.width / 2 > plyCollBox.x + 0./(2)) // Right
				{
					blocks->ftChangeSpeedModifier(speed / 4.0f, 'X', j);
				}
				else // Left
				{
					blocks->ftChangeSpeedModifier(-speed / 4.0f, 'X', j);
				}
			}
			if (CheckCollisionRecs(propRect1, player->ftReturnWeaponCollRect()) && player->ftReturnDoAttack() == true) // Collision weapon
			{
				if (player->ftReturnFace() == 0) // Right
				{
					blocks->ftChangeSpeedModifier(speed * 2.0f, 'X', j);
				}
				else // Left
				{
					blocks->ftChangeSpeedModifier(-speed * 2.0f, 'X', j);
				}
			}

			if (CheckCollisionRecs(propRect1, propRect2)) // Collision block to block
			{
				if (propRect1.y <= propRect2.y + propRect2.height || propRect2.y <= propRect1.y + propRect1.height)
				{
					blocks->ftMoveSquareProp((Vector2){1, 0.0f}, k);
					blocks->ftMoveSquareProp((Vector2){-1, 0.0f}, j);
				}

				if (propRect1.x > propRect2.x)
				{
					blocks->ftMoveSquareProp((Vector2){-speed / 2, 0.0f}, k);
					blocks->ftChangeSpeedModifier(speed * 0.5, 'X', j);
				}
				else
				{
					blocks->ftMoveSquareProp((Vector2){speed / 2, 0.0f}, k);
					blocks->ftChangeSpeedModifier(-speed * 0.5, 'X', j);
				}
			}
			if (CheckCollisionRecs(propRect2, propRect1)) // Collision block to block ajust
			{
				if (propRect1.x > propRect2.x)
				{
					blocks->ftMoveSquareProp((Vector2){speed / 2, 0.0f}, j);
					blocks->ftChangeSpeedModifier(-speed * 0.5, 'X', k);

				}
				else
				{
					blocks->ftMoveSquareProp((Vector2){-speed / 2, 0.0f}, j);
					blocks->ftChangeSpeedModifier(speed * 0.5, 'X', k);
				}
			}
			
		}
	}
	player->ftChangeDoAttack(false);
}

void	ftGravityGestion(Game *Game, Player *player, Props *blocks)
{
	ftGravityX(Game, player, blocks);
}

void	ftUsePlayerGravity(Player *player, EnvItems *envItems, float delta, int envItemsLength)
{
	int			hitObstacle = 0;
	Rectangle	tmpCollBox = player->ftReturnCollisionBox();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems->ftReturnEnvitemPtr(i);
		Vector2 *p = player->ftReturnPlayerPositionPtr();

		if (ei->blocking &&             							// Stop Player falling
			ei->rect.x <= tmpCollBox.x + tmpCollBox.width &&
			ei->rect.x + ei->rect.width >= tmpCollBox.x &&
			ei->rect.y >= p->y &&
			ei->rect.y <= p->y + player->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			player->ftSetSpeed(0);
			p->y = ei->rect.y;
		}
		else if (ei->blocking &&         							// Hit plafond
				 ei->rect.x <= p->x &&
				 ei->rect.x + ei->rect.width >= tmpCollBox.x + tmpCollBox.width &&
				 ei->rect.y + ei->rect.height > tmpCollBox.y &&
				 CheckCollisionRecs(ei->rect, tmpCollBox))
		{
			player->ftSetSpeed(25);
		}
		else if (CheckCollisionRecs(ei->rect, tmpCollBox) && ei->blocking)
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

void	ftUseGravity(SquareProps *prop, EnvItems *envItems, float delta, int envItemsLength)
{
	int 		hitObstacle = 0;
	Rectangle tmpProp = prop->ftReturnRectangle();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems->ftReturnEnvitemPtr(i);
		Vector2 *p = prop->ftReturnPositionPtr();
		if (ei->blocking &&
			ei->rect.x - tmpProp.width <= p->x &&
			ei->rect.x + ei->rect.width >= p->x &&
			ei->rect.y - tmpProp.height >= p->y &&
			ei->rect.y - tmpProp.height<= p->y + prop->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			prop->ftSetSpeed(prop->ftReturnSpeed() * -1 / 2); // Rebound on ground
			p->y = ei->rect.y;
			prop->ftInitPosition((Vector2){tmpProp.x, p->y - tmpProp.height});
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') / 1.25, 'X'); // Friction in x on ground
		}
		else if (CheckCollisionRecs(ei->rect, tmpProp) && ei->blocking)
		{
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') * - 1./(2), 'X');
		}
	}

	if (!hitObstacle)
	{
		prop->ftMovePosition(0, prop->ftReturnSpeed() * delta / 1.1);
		prop->ftChangeSpeed(G * delta);
	}
}

