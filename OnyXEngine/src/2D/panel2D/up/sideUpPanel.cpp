#include "../../../../myIncludes/game.hpp"

void	ftSelectItemsTop(Game *game, Camera2D *camera)
{
	Vector2 mousePos = game->mouse.pos;
	Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Rectangle item = game->buttonsMenuUp.play.ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != -1)
		{
			game->ctMode = -1;
		}
		item = game->buttonsMenuUp.stop.ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item) && game->ctMode != 1)
		{
			game->ctMode = 1;
		}
	}
}

void	ftDrawMenuUp(Game *game)
{
	DrawTextureEx(game->buttonsMenuUp.play.ftReturnTexture(),
		game->buttonsMenuUp.play.ftReturnPosition(), 0, 1, WHITE);
	DrawTextureEx(game->buttonsMenuUp.stop.ftReturnTexture(),
		game->buttonsMenuUp.stop.ftReturnPosition(), 0, 1, WHITE);
	if (game->ctMenuUpButtons == 1) // Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonColorOpen.ftReturnTexture(),
			game->buttonsMenuUp.buttonColorOpen.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonControlClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonListClose.ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 2) // Left Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonListOpen.ftReturnTexture(),
			game->buttonsMenuUp.buttonListOpen.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonControlClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonControlClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonColorClose.ftReturnPosition(), 0, 1, WHITE);
	}
	else if (game->ctMenuUpButtons == 0) // Middle Button Top Right
	{
		DrawTextureEx(game->buttonsMenuUp.buttonControlOpen.ftReturnTexture(),
			game->buttonsMenuUp.buttonControlOpen.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonColorClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonColorClose.ftReturnPosition(), 0, 1, WHITE);
		DrawTextureEx(game->buttonsMenuUp.buttonListClose.ftReturnTexture(),
			game->buttonsMenuUp.buttonListClose.ftReturnPosition(), 0, 1, WHITE);
	}
}

//*** Control buttons side up panel ***//
void	ftUpMenu2D(Game *game, Player *player, std::vector<SquareProps> *blocks,
	std::vector<EnvItems> *envItems, Camera2D *camera)
{
	ftSelectItemsTop(game, camera);
	ftDrawMenuUp(game);

	DrawText("Panel Up", 10, 10, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = game->mouse.pos;
		Vector2 rayPos = GetScreenToWorld2D(mousePos, *camera);

		Rectangle item = game->buttonsMenuUp.buttonColorOpen.ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item))	// Color panel
		{
			game->ctMenuUpButtons = 1;
		}
		item = game->buttonsMenuUp.buttonControlOpen.ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item)) // Control panel
		{
			game->ctMenuUpButtons = 0;
		}
		item = game->buttonsMenuUp.buttonListOpen.ftReturnRectangle();
		if (CheckCollisionPointRec(rayPos, item)) // List panel
		{
			game->ctMenuUpButtons = 2;
		}
	}
}
