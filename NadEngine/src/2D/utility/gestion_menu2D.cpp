#include "../../../myIncludes/game.hpp"

void	ftChooseMenu(Menu *menu)
{
	static int	ct; 
	static int	warning;

	if (!ct)
		ct = 1;
	if (!warning || warning > 80)
		warning = 0;

	if (IsKeyPressed(KEY_W))
		ct--;
	else if (IsKeyPressed(KEY_S))
		ct++;
	if (ct > 2)
		ct = 1;
	else if (ct < 1)
	ct = 2;

	if (IsKeyPressed(KEY_ENTER))
	{
		if (ct == 1)
			menu->ftChangeStart(1);
		else if (ct == 2 && menu->ftReturnPlayer() != 0)
			menu->ftChangeStart(2);
		else
			warning = 1;
	}

	if (ct == 1)
	{
		DrawText("<---*", 550, 200, 20, DARKGRAY);
	}
	else if (ct == 2)
	{
		DrawText("<---*", 550, 250, 20, DARKGRAY);
	}

	if (warning >= 1)
	{
		DrawText("Please, Choose A Character First", 250, 0, 20, ORANGE);
		warning++;
	}
}

void	ftChooseCharacter(Menu *menu)
{
	static int ct;


	if (!ct)
		ct = 1;

	if (IsKeyPressed(KEY_W))
		ct--;
	else if (IsKeyPressed(KEY_S))
		ct++;
	if (ct > 3)
		ct = 1;
	else if (ct < 1)
		ct = 3;

	if (IsKeyPressed(KEY_ENTER))
	{
		if (ct == 1)
			menu->ftChangePlayer(1);
		else if (ct == 2)
			menu->ftChangePlayer(2);
		else if (ct == 3)
			menu->ftChangePlayer(3);
	}

	if (ct == 1)
	{
		DrawText("<---*", 550, 200, 20, DARKGRAY);
	}
	else if (ct == 2)
	{
		DrawText("<---*", 550, 250, 20, DARKGRAY);
	}
	else if (ct == 3)
	{
		DrawText("<---*", 550, 300, 20, DARKGRAY);
	}
}

void	ftMenuChooseCharacter(Game *Game, Player * player, Menu * menu)
{
	menu->ftChangePlayer(0);
	ftChooseCharacter(menu);
	DrawText("Choose Your Character", 250, 100, 40, BLACK);
	DrawText("Edward Elric", 250, 200, 20, DARKGRAY);
	DrawText("Ichigo Kurosaki", 250, 250, 20, DARKGRAY);
	DrawText("Meliodas Lostvayne", 250, 300, 20, DARKGRAY);

	if (menu->ftReturnPlayer() == 1) // Edward
	{
		player->ftInitPlayerImgs(1);
		player->ftSetCollosionBox({player->ftReturnPlayerPositionX(), player->ftReturnPlayerPositionY()}, {50, 100}, {-25, 100});
		player->ftInitWeapon("Automail", player->ftReturnPlayerPosition(), {60, (float)player->ftReturnCollBoxSize('H')});
		player->ftChangeCtIdle(15);
		player->ftChangeCtMove(10);
		player->ftChangeCtJump(25);
		player->ftChangeCtFall(10);
		player->ftInitCtMoveX(77);
		player->ftInitCtMoveY(120, "Idle");
		player->ftInitCtMoveY(120, "Move");
		player->ftChangeCtAttack(42 / 7);
		player->ftChangeMoveAttackLftX(20);
		player->ftChangeMoveAttackRiX(-20);
		player->ftChangeMoveAttackY(118);
		player->ftChangeMoveIdleX(0);
		player->ftInitRectanglePlayer(player->ftReturnPlayerPosition(),
		{(float)player->ftReturnCollBoxSize('W'), (float)player->ftReturnCollBoxSize('H')});
		menu->ftChangeStart(0);
	}
	else if (menu->ftReturnPlayer() == 2) // Ichigo
	{
		player->ftInitPlayerImgs(2);
		player->ftSetCollosionBox({player->ftReturnPlayerPositionX(), player->ftReturnPlayerPositionY()}, {50, 110}, {-20, 108});
		player->ftInitWeapon("Automail", player->ftReturnPlayerPosition(), {60, (float)player->ftReturnCollBoxSize('H')});
		player->ftChangeCtIdle(15);
		player->ftChangeCtMove(8);
		player->ftChangeCtJump(15);
		player->ftChangeCtFall(10);
		player->ftInitCtMoveX(70);
		player->ftInitCtMoveY(118, "Idle");
		player->ftInitCtMoveY(120, "Move");
		player->ftChangeCtAttack(42 / 7);
		player->ftChangeMoveAttackLftX(0);
		player->ftChangeMoveAttackRiX(0);
		player->ftChangeMoveAttackY(118);
		player->ftChangeMoveIdleX(-10);
		player->ftInitRectanglePlayer(player->ftReturnPlayerPosition(),
		{(float)player->ftReturnCollBoxSize('W'), (float)player->ftReturnCollBoxSize('H')});
		menu->ftChangeStart(0);
	}
	else if (menu->ftReturnPlayer() == 3) // Meliodas
	{
		player->ftInitPlayerImgs(3);
		player->ftSetCollosionBox({player->ftReturnPlayerPositionX(), player->ftReturnPlayerPositionY()}, {45, 95}, {-72, 115});
		player->ftInitWeapon("Brocken Sword", {(float)player->ftReturnCollBoxPos('X'), (float)player->ftReturnCollBoxPos('Y')}, {50, (float)player->ftReturnCollBoxSize('H')});
		player->ftChangeCtIdle(30);
		player->ftChangeCtMove(8);
		player->ftChangeCtJump(20);
		player->ftChangeCtFall(60);
		player->ftInitCtMoveX(70);
		player->ftInitCtMoveY(98, "Idle");
		player->ftInitCtMoveY(82, "Move");
		player->ftChangeCtAttack(9);
		player->ftChangeMoveAttackLftX(40);
		player->ftChangeMoveAttackRiX(40);
		player->ftChangeMoveAttackY(90);
		player->ftChangeMoveIdleX(-2);
		player->ftInitRectanglePlayer(player->ftReturnPlayerPosition(),
		{(float)player->ftReturnCollBoxSize('W'), (float)player->ftReturnCollBoxSize('H')});
		menu->ftChangeStart(0);
	}
}
