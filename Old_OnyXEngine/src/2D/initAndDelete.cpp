#include "../../myIncludes/game.hpp"

MultipleCam2D	*ftInitCameras(Game *game, MultipleCam2D *allCameras)
{
	// Camera player
	allCameras->camera00.camera = {0};
	allCameras->camera00.camera.target = {0};
	allCameras->camera00.camera.offset = (Vector2){game->screenWidth / 2.0f - 150, game->screenHeight / 2.0f - 40};
	allCameras->camera00.camera.rotation = 0.0f;
	allCameras->camera00.camera.zoom = 1.0f;
	allCameras->camera00.textForCam = LoadRenderTexture(game->screenWidth - 300, game->screenHeight - 40);
	allCameras->camera00.rectForCam = {0.0f, 0.0f, (float)allCameras->camera00.textForCam.texture.width, (float)-allCameras->camera00.textForCam.texture.height};

	// Camera panel side up
	allCameras->camera01.camera = {0};
	allCameras->camera01.camera.target = {0, 0};
	allCameras->camera01.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera.rotation = 0.0f;
	allCameras->camera01.camera.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, game->screenHeight / 3);  // color panel
	allCameras->camera01.textForCam2 = LoadRenderTexture(300, game->screenHeight / 3); // control panel
	allCameras->camera01.rectForCam = {0.0f, 0.0f, (float)allCameras->camera01.textForCam.texture.width, (float)-allCameras->camera01.textForCam.texture.height};
	// allCameras->camera01.image = LoadImage();

	// Camera panel side down
	allCameras->camera02.camera = {0};
	allCameras->camera02.camera.target = {0, 0};
	allCameras->camera02.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera.rotation = 0.0f;
	allCameras->camera02.camera.zoom = 1.0f;
	allCameras->camera02.textForCam = LoadRenderTexture(300, game->screenHeight / 3 * 2 - 40);
	allCameras->camera02.rectForCam = {0.0f, 0.0f, (float)allCameras->camera02.textForCam.texture.width, (float)-allCameras->camera02.textForCam.texture.height};

	// Camera panel up
	allCameras->camera03.camera = {0};
	allCameras->camera03.camera.target = {0, 0};
	allCameras->camera03.camera.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera.rotation = 0.0f;
	allCameras->camera03.camera.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(game->screenWidth, 40);
	allCameras->camera03.rectForCam = {0.0f, 0.0f, (float)allCameras->camera03.textForCam.texture.width, (float)-allCameras->camera03.textForCam.texture.height};

	// Multiple camera
	// void (*cameraUpdaters[])(Camera2D *, Player *, EnvItem *, int, float, int, int) = {
	// 	ftUpdateCameraCenter};
	game->cameraUpdaters[0] = {ftUpdateCameraCenter};
	return (allCameras);
}

void	ftInitButtons(Game *game)
{
	game->buttonsMenuUp.play.ftInitButton({(float)game->screenWidth - 385, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/play_00.png"), 0);
	game->buttonsMenuUp.stop.ftInitButton({(float)game->screenWidth - 345, 5}, {30, 30}, WHITE,
		LoadTexture("./imgs/buttons/stop_00.png"), 1);

	game->buttonsMenuUp.buttonColorOpen.ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpSelected.png"), 0);
	game->buttonsMenuUp.buttonColorClose.ftInitButton({(float)game->screenWidth - 106, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/colorSideUpUnSelected.png"), 1);
	game->buttonsMenuUp.buttonControlClose.ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonControlOpen.ftInitButton({(float)game->screenWidth - 206, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/controlSideUpSelected.png"), 1);
	game->buttonsMenuUp.buttonListClose.ftInitButton({(float)game->screenWidth - 305, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/listSideUpUnSelected.png"), 0);
	game->buttonsMenuUp.buttonListOpen.ftInitButton({(float)game->screenWidth - 305, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/listSideUpSelected.png"), 1);

	game->buttonsMenuSideDown.buttonRightOpen.ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonMiddleOpen.ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpSelected.png"), 0);
	game->buttonsMenuSideDown.buttonLeftOpen.ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpSelected.png"), 0);

	game->buttonsMenuSideDown.buttonRightClose.ftInitButton({197, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/shapesSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonMiddleClose.ftInitButton({97, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/untitledSideUpUnSelected.png"), 1);
	game->buttonsMenuSideDown.buttonLeftClose.ftInitButton({-3, 0}, {100, 40}, WHITE,
		LoadTexture("./imgs/buttons/propertySideUpUnSelected.png"), 1);

	// Drag and Drop //
	game->dragDrop.square = new EnvItems((Vector2){20, 80}, (Vector2){54, 54}, 0, WHITE,		// Square
		LoadTexture("./imgs/shapes/square00.png"), 1, "Square0");

	game->dragDrop.squareSelect = new EnvItems((Vector2){20, 80}, (Vector2){54, 54}, 0, WHITE,	// Square
		LoadTexture("./imgs/shapes/squareSelected00.png"), 1, "Square1");

	game->dragDrop.triangle = new EnvItems((Vector2){120, 80}, (Vector2){54, 54}, 0, WHITE, 		// Triangle
		LoadTexture("./imgs/shapes/triangle00.png"), 1, "Triangle0");
	game->dragDrop.triangleSelect = new EnvItems((Vector2){120, 80}, (Vector2){54, 54}, 0, WHITE,	// Triangle
		LoadTexture("./imgs/shapes/triangleSelected00.png"), 1, "Triangle1");

	game->dragDrop.circle = new EnvItems((Vector2){220, 80}, (Vector2){54, 54}, 0, WHITE, 	// Circle
		LoadTexture("./imgs/shapes/circle00.png"), 1, "Circle0");
	game->dragDrop.circleSelect = new EnvItems((Vector2){220, 80}, (Vector2){54, 54}, 0, WHITE,	// Circle
		LoadTexture("./imgs/shapes/circleSelected00.png"), 1, "Circle1");

	game->dragDrop.other = new EnvItems((Vector2){20, 180}, (Vector2){54, 54}, 0, WHITE, 	// Others
		LoadTexture("./imgs/shapes/other00.png"), 1, "Other0");
	game->dragDrop.otherSelect = new EnvItems((Vector2){20, 180}, (Vector2){54, 54}, 0, WHITE,	// Others
		LoadTexture("./imgs/shapes/otherSelected00.png"), 1, "Other1");

	game->dragDrop.platform = new EnvItems((Vector2){120, 180},(Vector2) {154, 54}, 0, WHITE, 	// Platform
		LoadTexture("./imgs/shapes/platform00.png"), 1, "Platform0");
	game->dragDrop.platformSelect = new EnvItems((Vector2){120, 180},(Vector2) {154, 54}, 0, WHITE,	// Platform
		LoadTexture("./imgs/shapes/platformSelected00.png"), 1, "Platform1");
}

void	ftDeleteAndFree(Game *game, Player *player, std::vector<SquareProps> *blocks,
			std::vector<EnvItems> *envItems, MultipleCam2D *allCameras)
{
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);
	UnloadRenderTexture(allCameras->camera00.textForCam);

	player->ftDeleteVarChar();
	blocks->clear();
	envItems->clear();

	switch (player->ftReturnNbr())
	{
		case 1:
			player->ftDestroyImgs1();
			break;
		case 2:
			player->ftDestroyImgs2();
			break;
		case 3:
			player->ftDestroyImgs3();
			break;
	}

	UnloadImage(game->imgCercleChrom);
	UnloadTexture(game->textCercleChrom);
	game->buttonsMenuUp.play.ftUnloadTexture();
	game->buttonsMenuUp.stop.ftUnloadTexture();
	game->buttonsMenuUp.buttonColorOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonColorClose.ftUnloadTexture();
	game->buttonsMenuUp.buttonControlOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonControlClose.ftUnloadTexture();
	game->buttonsMenuUp.buttonListOpen.ftUnloadTexture();
	game->buttonsMenuUp.buttonListClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonRightOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonMiddleOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonLeftOpen.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonRightClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonMiddleClose.ftUnloadTexture();
	game->buttonsMenuSideDown.buttonLeftClose.ftUnloadTexture();
	
	game->dragDrop.square->ftDeleteVarsChar();
	game->dragDrop.square->ftUnloadTexture();
	delete game->dragDrop.square;
	game->dragDrop.squareSelect->ftDeleteVarsChar();
	game->dragDrop.squareSelect->ftUnloadTexture();
	delete game->dragDrop.squareSelect;
	game->dragDrop.triangle->ftDeleteVarsChar();
	game->dragDrop.triangle->ftUnloadTexture();
	delete game->dragDrop.triangle;
	game->dragDrop.triangleSelect->ftDeleteVarsChar();
	game->dragDrop.triangleSelect->ftUnloadTexture();
	delete game->dragDrop.triangleSelect;
	game->dragDrop.circle->ftDeleteVarsChar();
	game->dragDrop.circle->ftUnloadTexture();
	delete game->dragDrop.circle;
	game->dragDrop.circleSelect->ftDeleteVarsChar();
	game->dragDrop.circleSelect->ftUnloadTexture();
	delete game->dragDrop.circleSelect;
	game->dragDrop.other->ftDeleteVarsChar();
	game->dragDrop.other->ftUnloadTexture();
	delete game->dragDrop.other;
	game->dragDrop.otherSelect->ftDeleteVarsChar();
	game->dragDrop.otherSelect->ftUnloadTexture();
	delete game->dragDrop.otherSelect;
	game->dragDrop.platform->ftDeleteVarsChar();
	game->dragDrop.platform->ftUnloadTexture();
	delete game->dragDrop.platform;
	game->dragDrop.platformSelect->ftDeleteVarsChar();
	game->dragDrop.platformSelect->ftUnloadTexture();
	delete game->dragDrop.platformSelect;

	delete player;
	delete allCameras;
}
