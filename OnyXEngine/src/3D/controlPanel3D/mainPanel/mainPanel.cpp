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
	// pos.x += 150;
	// pos.y -= 23;
	game->ray.ray = GetMouseRay(pos, allCameras->camera00.camera3D);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (!game->ray.collision.hit)
		{
			// Vector2 pos = GetMousePosition();
			pos.x += 150;
			pos.y -= 23;
			game->ray.ray = GetMouseRay(pos, allCameras->camera00.camera3D);

			Cube3D cube = cubes->ftReturnCube3D();
			game->ray.collision = GetRayCollisionBox(game->ray.ray, 
				(BoundingBox){(Vector3){cube.pos.x - cube.pos.x / 2, cube.pos.y - cube.size.y / 2, cube.pos.z - cube.size.z / 2},
				(Vector3){cube.pos.x + cube.size.x / 2, cube.pos.y + cube.size.y / 2, cube.pos.z + cube.size.z / 2}});
		}
		else
			game->ray.collision.hit = false;
	}
	else if (game->ray.collision.hit == true)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector3 ppos;
			ppos.x = game->ray.ray.position.x;
			ppos.y = game->ray.ray.position.y;
			ppos.z = game->ray.ray.position.z;
			ppos.x += game->ray.ray.position.x - ray.position.x;
			ppos.y += game->ray.ray.position.y - ray.position.y;
			ppos.z += game->ray.ray.position.z - ray.position.z;
			cubes->ftChangePosition(ppos);
		}
	}

	if (IsKeyDown('Z'))
		allCameras->camera00.camera3D.target = (Vector3){0.0f, 0.0f, 0.0f};
	ray = game->ray.ray;
	// mousePos = game->mouse.pos;
}

void    ftControlMainPanel(Game *game, CUBE3D *cubes, MultipleCam3D *allCameras)
{
	ftKeyEvents(game, cubes, allCameras);
	

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
