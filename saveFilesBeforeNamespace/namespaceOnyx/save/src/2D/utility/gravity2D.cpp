#include "../../../myIncludes/game.hpp"

using namespace obj;

void ftGravityX(Game *game, Player *player, SquareProps *blocks)
{
	Rectangle plyCollBox = player->ftReturnCollisionBox();
	float speed = PLAYER_HOR_SPD * game->delta;

	for (int j = 0; j < game->nbrSquareProps; j++)
	{
		Rectangle propRect1 = blocks[j].obj::SquareProps::ftReturnRectangle();
		for (int k = 0; k < game->nbrSquareProps; k++)
		{
			if (j == k)
				k++;

			Rectangle propRect2 = blocks[j].obj::SquareProps::ftReturnRectangle();
			if (CheckCollisionRecs(propRect1, plyCollBox)) // Collision player
			{
				if (propRect1.x - propRect1.width / 2 > plyCollBox.x + 0. / (2)) // Right
				{
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(speed / 4.0f, 'X');
				}
				else // Left
				{
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(-speed / 4.0f, 'X');
				}
			}
			if (CheckCollisionRecs(propRect1, player->ftReturnWeaponCollRect()) && player->ftReturnDoAttack() == true) // Collision weapon
			{
				if (player->ftReturnFace() == 0) // Right
				{
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(speed * 2.0f, 'X');
				}
				else // Left
				{
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(-speed * 2.0f, 'X');
				}
			}

			if (CheckCollisionRecs(propRect1, propRect2)) // Collision block to block
			{
				if (propRect1.y <= propRect2.y + propRect2.height || propRect2.y <= propRect1.y + propRect1.height)
				{
					blocks[k].obj::SquareProps::ftMovePosition(1, 0.0f);
					blocks[j].obj::SquareProps::ftMovePosition(-1, 0.0f);
				}

				if (propRect1.x > propRect2.x)
				{
					blocks[k].obj::SquareProps::ftMovePosition(-speed / 2, 0.0f);
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(speed * 0.5, 'X');
				}
				else
				{
					blocks[k].obj::SquareProps::ftMovePosition(speed / 2, 0.0f);
					blocks[j].obj::SquareProps::ftChangeSpeedModifier(-speed * 0.5, 'X');
				}
			}
			if (CheckCollisionRecs(propRect2, propRect1)) // Collision block to block ajust
			{
				if (propRect1.x > propRect2.x)
				{
					blocks[j].obj::SquareProps::ftMovePosition(speed / 2, 0.0f);
					blocks[k].obj::SquareProps::ftChangeSpeedModifier(-speed * 0.5, 'X');
				}
				else
				{
					blocks[j].obj::SquareProps::ftMovePosition(-speed / 2, 0.0f);
					blocks[k].obj::SquareProps::ftChangeSpeedModifier(speed * 0.5, 'X');
				}
			}
		}
	}
	player->ftChangeDoAttack(false);
}

void ftGravityGestion(Game *Game, Player *player, SquareProps *blocks)
{
	ftGravityX(Game, player, blocks);
}

void ftUsePlayerGravity(Player *player, EnvItems *envItems, float delta, int envItemsLength)
{
	int hitObstacle = 0;
	Rectangle tmpCollBox = player->ftReturnCollisionBox();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems[i].obj::EnvItems::ftReturnOneEnvitemPtr();
		Vector2 *p = player->ftReturnPlayerPositionPtr();

		if (ei->blocking && // Stop Player falling
			ei->rect.x <= tmpCollBox.x + tmpCollBox.width &&
			ei->rect.x + ei->rect.width >= tmpCollBox.x &&
			ei->rect.y >= p->y &&
			ei->rect.y <= p->y + player->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			player->ftSetSpeed(0);
			p->y = ei->rect.y;
		}
		else if (ei->blocking && // Hit plafond
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

void ftUseGravity(SquareProps *prop, EnvItems *envItems, float delta, int envItemsLength)
{
	int hitObstacle = 0;
	Rectangle tmpProp = prop->ftReturnRectangle();

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems[i].obj::EnvItems::ftReturnOneEnvitemPtr();
		Vector2 *p = prop->ftReturnPositionPtr();
		if (ei->blocking &&
			ei->rect.x - tmpProp.width <= p->x &&
			ei->rect.x + ei->rect.width >= p->x &&
			ei->rect.y - tmpProp.height >= p->y &&
			ei->rect.y - tmpProp.height <= p->y + prop->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			prop->ftSetSpeed(prop->ftReturnSpeed() * -1 / 2); // Rebound on ground
			p->y = ei->rect.y;
			prop->ftInitPosition((Vector2){tmpProp.x, p->y - tmpProp.height});
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') / 1.25, 'X'); // Friction in x on ground
		}
		else if (CheckCollisionRecs(ei->rect, tmpProp) && ei->blocking)
		{
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') * -1. / (2), 'X');
		}
	}

	if (!hitObstacle)
	{
		prop->ftMovePosition(0, prop->ftReturnSpeed() * delta / 1.1);
		prop->ftChangeSpeed(G * delta);
	}
}
