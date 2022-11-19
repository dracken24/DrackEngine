#include "../../../../myIncludes/game.hpp"

void	ftSelectItemsTop(Game *game, Camera2D *camera)
{
	Vector2 mousePos = game->mouse.pos;
	Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Rectangle item = game->buttonsMenuUp.play.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != -1)
		{
			game->ctMode = -1;
		}
		item = game->buttonsMenuUp.stop.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != 1)
		{
			game->ctMode = 1;
		}
	}
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Game *game, Camera2D *camera)
{
	ftSelectItemsTop(game, camera);
	DrawTextureEx(game->buttonsMenuUp.play.ftReturnOneEnviTexture(),{(float)game->screenWidth - 300, 5}, 0, 1, WHITE);
	DrawTextureEx(game->buttonsMenuUp.stop.ftReturnOneEnviTexture(),{(float)game->screenWidth - 260, 5}, 0, 1, WHITE);
	if (game->ctMenuUpButtons == 1) // Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonColorOpen.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonColorOpen.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviPos(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 0) // Second Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonControlOpen.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonControlOpen.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviPos(), 0, 1, WHITE);
	}
	DrawText("Panel Up", 10, 10, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		Rectangle item = game->buttonsMenuUp.buttonColorOpen.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuUpButtons = 1;
		}
		item = game->buttonsMenuUp.buttonControlOpen.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item))
		{
			game->ctMenuUpButtons = 0;
		}
	}
}