/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackenLib PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		mainPanel.hpp         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../../myIncludes/game.hpp"

static void ftDrawGrid(int slices, float spacing)
{
	int halfSlices = slices / 2;

	rlBegin(RL_LINES);
	for (int i = -halfSlices; i <= halfSlices; i++)
	{
		if (i == 0)
		{
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
			rlColor3f(100.5f, 100.5f, 100.5f);
		}
		else
		{
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
			rlColor3f(50.75f, 50.75f, 50.75f);
		}

		rlVertex3f((float)i * spacing, 0.0f, (float)-halfSlices * spacing);
		rlVertex3f((float)i * spacing, 0.0f, (float)halfSlices * spacing);

		rlVertex3f((float)-halfSlices * spacing, 0.0f, (float)i * spacing);
		rlVertex3f((float)halfSlices * spacing, 0.0f, (float)i * spacing);
	}
	rlEnd();
}

void	ftKeyEvents(Game *game, CUBE3D *cubes, MultipleCam3D *allCameras)
{
	static Ray ray;
	Vector2 pos = GetMousePosition();
	pos.x += 150;
	pos.y -= 23;
	game->ray.ray = GetMouseRay(pos, allCameras->camera00.camera3D);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// check collision with gameObject
		if (!game->ray.collision.hit)
		{
			Vector2 pos = GetMousePosition();
			pos.x += 150;
			pos.y -= 23;
			game->ray.ray = GetMouseRay(pos, allCameras->camera00.camera3D);

			Cube3D cube = cubes->ftReturnCube3D();
			game->ray.collision = GetRayCollisionBox(game->ray.ray,
				(BoundingBox){(Vector3){cube.pos.x - cube.pos.x / 2, cube.pos.y - cube.size.y / 2,
					cube.pos.z - cube.size.z / 2}, (Vector3){cube.pos.x + cube.size.x / 2,
						cube.pos.y + cube.size.y / 2, cube.pos.z + cube.size.z / 2}});
		}
		else
			game->ray.collision.hit = false;
	}
	else if (game->ray.collision.hit == true)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			// Get the difference in mouse position since last frame
			float deltaX = GetMouseX() - game->mouse.pos.x;
			float deltaY = game->mouse.pos.y - GetMouseY();

			// Get the camera's direction and right vector
			Vector3 cameraDirection = Vector3Normalize(Vector3Subtract(allCameras->camera00.camera3D.target, allCameras->camera00.camera3D.position));
			Vector3 cameraRight = Vector3Normalize(Vector3CrossProduct(cameraDirection, allCameras->camera00.camera3D.up));

			// Calculate the movement direction based on the camera's transform
			Vector3 movementDirection = Vector3Add(Vector3Scale(cameraRight, deltaX), Vector3Scale(allCameras->camera00.camera3D.up, deltaY));
			movementDirection = Vector3Normalize(movementDirection);

			// Calculate the distance from the object to the camera
			float distance = Vector3Distance(cubes->ftReturnCube3D().pos, allCameras->camera00.camera3D.position);

			// Move the object by the transformed movement direction
			cubes->ftMovePosition(Vector3Scale(movementDirection, std::sqrt(distance) * 3 * GetFrameTime()));
		}
	}

	if (IsKeyDown(KEY_Z))
		allCameras->camera00.camera3D.target = (Vector3){0.0f, 0.0f, 0.0f};
	ray = game->ray.ray;

	game->mouse.pos = GetMousePosition();
}

void    ftControlMainPanel(Game *game, CUBE3D *cubes, MultipleCam3D *allCameras)
{
	KeyboardKey key;

	// Move camera
	// if (key == KEY_ONE)
	// {
	// 	UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FIRST_PERSON);
	// }
	// if (GetKeyPressed())
	// {
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		UpdateCamera(&allCameras->camera00.camera3D, CAMERA_THIRD_PERSON);
	}
	// }
	// if (key == KEY_THREE)
	// {
	// 	UpdateCamera(&allCameras->camera00.camera3D, CAMERA_ORBITAL);
	// }
	// if (key == KEY_FOUR)
	// {
	// 	UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FREE);
	// }
	

	ftKeyEvents(game, cubes, allCameras);
	
	// If cube is selected, draw a cube around it
	if (game->ray.collision.hit)
	{
		Cube3D cube = cubes->ftReturnCube3D();
		DrawCube(cube.pos, cube.size.x, cube.size.y, cube.size.z, RED);
		DrawCubeWires(cube.pos, cube.size.x, cube.size.y, cube.size.z, MAROON);

		DrawCubeWires(cube.pos, cube.size.x + 0.2f, cube.size.y + 0.2f, cube.size.z + 0.2f, GREEN);
	}
	else
	{
		Cube3D cube = cubes->ftReturnCube3D();
		DrawCube(cube.pos, cube.size.x, cube.size.y, cube.size.z, PURPLE);
		DrawCubeWires(cube.pos, cube.size.x, cube.size.y, cube.size.z, DARKGRAY);
	}

	ftDrawGrid(10, 1.0f);

	if (IsKeyDown(KEY_I))
	{
		DrawRectangle(10, 10, 320, 133, Fade(DARKGRAY, 0.5f));
		DrawRectangleLines(10, 10, 320, 133, DARKGRAY);
	}
}
