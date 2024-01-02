/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		init3D.hpp    	      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../myIncludes/game.hpp"

MultipleCam3D   *ftInitCameras3D(Game *game, MultipleCam3D *allCameras)
{
    	// Define the camera to look into our 3d world
	allCameras->camera00.camera3D = { 0 };
	allCameras->camera00.camera3D.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
	allCameras->camera00.camera3D.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	allCameras->camera00.camera3D.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	allCameras->camera00.camera3D.fovy = 45.0f;                                // Camera field-of-view Y
	allCameras->camera00.camera3D.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
	allCameras->camera00.textForCam = LoadRenderTexture(game->screenWidth - 300, game->screenHeight - 40);
	allCameras->camera00.rectForCam = {0.0f, 0.0f, (float)allCameras->camera00.textForCam.texture.width,
		(float)-allCameras->camera00.textForCam.texture.height};

	// Camera panel side up
	allCameras->camera01.camera2D = {0};
	allCameras->camera01.camera2D.target = {0, 0};
	allCameras->camera01.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera01.camera2D.rotation = 0.0f;
	allCameras->camera01.camera2D.zoom = 1.0f;
	allCameras->camera01.textForCam = LoadRenderTexture(300, game->screenHeight / 3);
	allCameras->camera01.rectForCam = {0.0f, 0.0f, (float)allCameras->camera01.textForCam.texture.width,
		(float)-allCameras->camera01.textForCam.texture.height};

	// Camera panel side down
	allCameras->camera02.camera2D = {0};
	allCameras->camera02.camera2D.target = {0, 0};
	allCameras->camera02.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera02.camera2D.rotation = 0.0f;
	allCameras->camera02.camera2D.zoom = 1.0f;
	allCameras->camera02.textForCam = LoadRenderTexture(300, game->screenHeight / 3 * 2 - 40);
	allCameras->camera02.rectForCam = {0.0f, 0.0f, (float)allCameras->camera02.textForCam.texture.width,
		(float)-allCameras->camera02.textForCam.texture.height};

	// Camera panel up
	allCameras->camera03.camera2D = {0};
	allCameras->camera03.camera2D.target = {0, 0};
	allCameras->camera03.camera2D.offset = (Vector2){0.0f, 0.0f};
	allCameras->camera03.camera2D.rotation = 0.0f;
	allCameras->camera03.camera2D.zoom = 1.0f;
	allCameras->camera03.textForCam = LoadRenderTexture(game->screenWidth, 40);
	allCameras->camera03.rectForCam = {0.0f, 0.0f, (float)allCameras->camera03.textForCam.texture.width,
		(float)-allCameras->camera03.textForCam.texture.height};

    return (allCameras);
}
