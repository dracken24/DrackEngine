#include "../../../myIncludes/game.hpp"

void	ftImgsGestion(Game *Game, Player *player)
{
	player->ftMovePosition(-player->ftReturnCtMoveX(), 0);

	if (player->ftReturnAttackCt() == 0)
	{
		if (player->ftReturnCt() == 0 && player->ftReturnFace() == 0) // Idle right
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Idle"));
			DrawTextureEx(player->ftReturnGoodImage("Idle Ri", Game->ct_action
					/ player->ftReturnCtIdle()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Idle"));
		}
		else if (player->ftReturnCt() == 0 && player->ftReturnFace() == 1) // Idle left
		{
			player->ftMovePosition(-player->ftReturnMoveIdleX(), -player->ftReturnctMoveY("Idle"));
			DrawTextureEx(player->ftReturnGoodImage("Idle Lft", Game->ct_action
					/ player->ftReturnCtIdle()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(player->ftReturnMoveIdleX(), player->ftReturnctMoveY("Idle"));
		}
		else if (player->ftReturnCt() == 1 && player->ftReturnFace() == 0) // move right
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Move Ri", Game->ct_action
					/ player->ftReturnCtMove()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
		}
		else if (player->ftReturnCt() == 1 && player->ftReturnFace() == 1) // move lft
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Move Lft", Game->ct_action
					/ player->ftReturnCtMove()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
		}
		else if (player->ftReturnCt() == 4 && player->ftReturnFace() == 0) // Jump right
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Jump Ri", Game->ct_action
					/ player->ftReturnCtJump()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
		}
		else if (player->ftReturnCt() == 4 && player->ftReturnFace() == 1) // Jump left
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Jump Lft", Game->ct_action
					/ player->ftReturnCtJump()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
		}
		else if (player->ftReturnCt() == 5 && player->ftReturnFace() == 0) // Fall right
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Fall Ri", Game->ct_action
					/ player->ftReturnCtFall()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
			if (Game->ct_action >= 19)
				Game->ct_action = 0;
		}
		else if (player->ftReturnCt() == 5 && player->ftReturnFace() == 1) // Fall left
		{
			player->ftMovePosition(0, -player->ftReturnctMoveY("Move"));
			DrawTextureEx(player->ftReturnGoodImage("Fall Lft", Game->ct_action
					/ player->ftReturnCtFall()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
			player->ftMovePosition(0, player->ftReturnctMoveY("Move"));
			if (Game->ct_action >= 19)
				Game->ct_action = 0;
		}
	}

	if (player->ftReturnAttackCt() == 1 && player->ftReturnFace() == 1) // Attack left
	{
		player->ftMovePosition(-player->ftReturnMoveAttackLftX(), -player->ftReturnMoveAttackY());
		DrawTextureEx(player->ftReturnGoodImage("Attack 00 Lft", Game->ct_action
				/ player->ftReturnCtAttack()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
		player->ftMovePosition(player->ftReturnMoveAttackLftX(), player->ftReturnMoveAttackY());
		if (Game->ct_action >= 35)
		{
			player->ftChangeAttackCt(0);
			player->ftChangeCt(0);
			Game->ct_action = 0;
		}
	}
	else if (player->ftReturnAttackCt() == 1 && player->ftReturnFace() == 0) // Attack right
	{
		player->ftMovePosition(-player->ftReturnMoveAttackRiX(), -player->ftReturnMoveAttackY());
		DrawTextureEx(player->ftReturnGoodImage("Attack 00 Ri", Game->ct_action
				/ player->ftReturnCtAttack()), player->ftReturnPlayerPosition(), 0.0f, 2, WHITE);
		player->ftMovePosition(player->ftReturnMoveAttackRiX(), player->ftReturnMoveAttackY());
		if (Game->ct_action >= 35)
		{
			player->ftChangeAttackCt(0);
			player->ftChangeCt(0);
			Game->ct_action = 0;
		}
	}

	player->ftMovePosition(player->ftReturnCtMoveX(), 0);
	Game->ct_action += 1;
}
