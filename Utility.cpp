#include "../vendor/raylib/src/raylib.h"
#include "../vendor/raylib/src/raymath.h"
#include "../myIncludes/class/player.hpp"
#include "../myIncludes/class/props.hpp"
#include "../myIncludes/class/menu.hpp"

#define G 800 // Gravity

typedef struct Vector2 {
    float x;              
    float y;              
}	Vector2;

// Vector3, 3 components
typedef struct Vector3 {
    float x;              
    float y;              
    float z;              
}	Vector3;

// Vector4, 4 components
typedef struct Vector4 {
    float x;              
    float y;              
    float z;              
    float w;              
}	Vector4;

typedef struct Rectangle {
	float x;	  // Rectangle top-left corner position x
	float y;	  // Rectangle top-left corner position y
	float width;  // Rectangle width
	float height; // Rectangle height
}	Rectangle;

typedef struct Color {
	unsigned char t; // Color alpha value
	unsigned char r; // Color red value
	unsigned char g; // Color green value
	unsigned char b; // Color blue value
}	Color;

typedef struct EnvItem {
	Rectangle rect;
	int blocking;
	Color color;
}	EnvItem;

void	ftUseGravity(Player *player, EnvItem *envItems, float delta, int envItemsLength)
{
	int hitObstacle = 0;

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems + i;
		Vector2 *p = player->ftReturnPlayerPositionPtr();
		if (ei->blocking &&
			ei->rect.x <= p->x &&
			ei->rect.x + ei->rect.width >= p->x &&
			ei->rect.y >= p->y &&
			ei->rect.y <= p->y + player->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			player->ftSetSpeed(0);
			p->y = ei->rect.y;
		}
	}
	if (!hitObstacle)
	{
		player->ftMovePosition(0, player->ftReturnSpeed() * delta);
		player->ftChangeSpeed(G * delta);
		player->ftChangeJump(false);
	}
	else
		player->ftChangeJump(true);
}

void	ftGravityX(Game *Game, Player *player, Props *blocks)
{
	for (int j = 0; j < blocks->ftReturnNbr(); j++)
	{
		Rectangle rect = blocks->ftReturnRectangleSqPr(j);

		for (int k = 0; k < blocks->ftReturnNbr(); k++)
		{
			if (j == k)
				k++;

			if (CheckCollisionRecs(blocks->ftReturnRectangleSqPr(j), player->ftReturnCollisionBox())) // Collision player
			{
				if (rect.x - rect.width / 2 > player->ftReturnCollBoxPos('X') + player->ftReturnCollBoxSize('X') / 2) // Right
				{
					blocks->ftMoveSquareProp({PLAYER_HOR_SPD * Game->delta, 0}, j);
					blocks->ftChangeSpeedModifier(PLAYER_HOR_SPD * Game->delta * 1.15, 'X', j);
				}
				else
				{
					blocks->ftMoveSquareProp({-PLAYER_HOR_SPD * Game->delta, 0}, j);
					blocks->ftChangeSpeedModifier(-PLAYER_HOR_SPD * Game->delta * 1.15, 'X', j);
				}
			}
			if(CheckCollisionRecs(blocks->ftReturnRectangleSqPr(j), player->ftReturnWeaponCollRect()) && player->ftReturnDoAttack() == true) // Collision weapon
			{
				if (player->ftReturnFace() == 0) // Right
				{
					blocks->ftChangeSpeedModifier(PLAYER_HOR_SPD * Game->delta * 2, 'X', j);
				}
				else
				{
					blocks->ftChangeSpeedModifier(-PLAYER_HOR_SPD * Game->delta * 2, 'X', j);
				}
			}

			if (CheckCollisionRecs(blocks->ftReturnRectangleSqPr(j), blocks->ftReturnRectangleSqPr(k))) // Collision block to block
			{
				if (blocks->ftReturnSqurtPos('X', j) > blocks->ftReturnSqurtPos('X', k))
				{
					blocks->ftMoveSquareProp({-PLAYER_HOR_SPD * Game->delta, 0}, k);
					blocks->ftChangeSpeedModifier(PLAYER_HOR_SPD * Game->delta * 1.075, 'X', j);
				}
				else
				{
					blocks->ftMoveSquareProp({PLAYER_HOR_SPD * Game->delta, 0}, k);
					blocks->ftChangeSpeedModifier(-PLAYER_HOR_SPD * Game->delta * 1.075, 'X', j);
				}
			}
			if (CheckCollisionRecs(blocks->ftReturnRectangleSqPr(k), blocks->ftReturnRectangleSqPr(j))) // Collision block to block
			{
				if (blocks->ftReturnSqurtPos('X', j) > blocks->ftReturnSqurtPos('X', k))
				{
					blocks->ftMoveSquareProp({PLAYER_HOR_SPD * Game->delta, 0}, j);
					blocks->ftChangeSpeedModifier(-PLAYER_HOR_SPD * Game->delta * 1.075, 'X', k);

				}
				else
				{
					blocks->ftMoveSquareProp({-PLAYER_HOR_SPD * Game->delta, 0}, k);
					blocks->ftChangeSpeedModifier(PLAYER_HOR_SPD * Game->delta * 1.075, 'X', k);

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

void	ftUsePlayerGravity(Player *player, EnvItem *envItems, float delta, int envItemsLength)
{
	int hitObstacle = 0;

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems + i;
		Vector2 *p = player->ftReturnPlayerPositionPtr();

		if (ei->blocking &&
			ei->rect.x <= player->ftReturnCollBoxPos('X') + player->ftReturnCollBoxSize('W') &&
			ei->rect.x + ei->rect.width >= player->ftReturnCollBoxPos('X') &&
			ei->rect.y >= p->y &&
			ei->rect.y <= p->y + player->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			player->ftSetSpeed(0);
			p->y = ei->rect.y;
		}
		else if (ei->blocking &&
			ei->rect.x <= p->x &&
			ei->rect.x + ei->rect.width >= player->ftReturnCollBoxPos('X') + player->ftReturnCollBoxSize('W') &&
			ei->rect.y + ei->rect.height > player->ftReturnCollBoxPos('Y') &&
			CheckCollisionRecs(ei->rect, player->ftReturnCollisionBox()))
		{
			player->ftSetSpeed(25);
		}
		else if (CheckCollisionRecs(ei->rect, player->ftReturnCollisionBox()) && ei->blocking)
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

void	ftUseGravity(SquareProps *prop, EnvItem *envItems, float delta, int envItemsLength)
{
	// static int	rebound;
	int 		hitObstacle = 0;

	// if (!rebound)
	// 	rebound = 0;

	for (int i = 0; i < envItemsLength; i++)
	{
		EnvItem *ei = envItems + i;
		Vector2 *p = prop->ftReturnPositionPtr();
		if (ei->blocking &&
			ei->rect.x - prop->ftReturnWideorHigh('W') <= p->x &&
			ei->rect.x + ei->rect.width >= p->x &&
			ei->rect.y - prop->ftReturnWideorHigh('H') >= p->y &&
			ei->rect.y - prop->ftReturnWideorHigh('H') <= p->y + prop->ftReturnSpeed() * delta)
		{
			hitObstacle = 1;
			prop->ftSetSpeed(0);
			p->y = ei->rect.y;
			Rectangle tmp = prop->ftReturnRectangle();
			prop->ftInitPosition({tmp.x, p->y - tmp.height});
			prop->ftSetSpeedModifier(prop->ftReturnSpeedModifier('X') / 1.1, 'X');
			// break ;
		}
		else if (CheckCollisionRecs(ei->rect, prop->ftReturnRectangle()) && ei->blocking)
		{
			// std::cout << "Collision 2: " << i << std::endl;
			prop->ftSetSpeedModifier(0, 'X');
		}
	}

	if (!hitObstacle)
	{
		prop->ftMovePosition(0, prop->ftReturnSpeed() * delta);
		prop->ftChangeSpeed(G * delta);
	}
}

