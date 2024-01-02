/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:	 	  init.hpp         	  *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../myIncludes/game.hpp"

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
	allCameras->camera01.rectForCam = {0.0f, 0.0f, (float)allCameras->camera01.textForCam.texture.width, (float)-allCameras->camera01.textForCam.texture.height};

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