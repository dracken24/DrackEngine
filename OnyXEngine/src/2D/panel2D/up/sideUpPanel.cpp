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

void	ftDrawMenuUp(Game *game)
{
	DrawTextureEx(game->buttonsMenuUp.play.ftReturnOneEnviTexture(), game->buttonsMenuUp.play.ftReturnOneEnviPos(), 0, 1, WHITE);
	DrawTextureEx(game->buttonsMenuUp.stop.ftReturnOneEnviTexture(), game->buttonsMenuUp.stop.ftReturnOneEnviPos(), 0, 1, WHITE);
	if (game->ctMenuUpButtons == 1) // Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonColorOpen.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonColorOpen.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonListClose.ftReturnOneEnviPos(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 2) // Left Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonListOpen.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonListOpen.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonControlClose.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviPos(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 0) // Middle Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonControlOpen.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonControlOpen.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonColorClose.ftReturnOneEnviPos(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnOneEnviTexture(),
			game->buttonsMenuUp.buttonListClose.ftReturnOneEnviPos(), 0, 1, WHITE);
	}
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Game *game, Player *player, Props *blocks, EnvItems *envItems, Camera2D *camera)
{
	ftSelectItemsTop(game, camera);
	ftDrawMenuUp(game);

	DrawText("Panel Up", 10, 10, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		Rectangle item = game->buttonsMenuUp.buttonColorOpen.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item))	// Color panel
		{
			game->ctMenuUpButtons = 1;
		}
		item = game->buttonsMenuUp.buttonControlOpen.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item)) // Control panel
		{
			game->ctMenuUpButtons = 0;
		}
		item = game->buttonsMenuUp.buttonListOpen.ftReturnOneRectangle();
		if (CheckCollisionPointRec(rayPos, item)) // List panel
		{
			game->ctMenuUpButtons = 2;
		}
	}
}