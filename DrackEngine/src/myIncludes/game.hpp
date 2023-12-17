/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackenLib PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		  game.hpp         	  *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef GAME_HPP
# define GAME_HPP

// # include <raylib.h>
# include "../../raylib/src/raylib.h"
# include "../../raylib/src/raymath.h"
# include "class2D/player.hpp"
# include "class2D/props.hpp"
# include "./class2D/menu.hpp"
# include "./class2D/envitems.hpp"
# include "./class2D/squareProps.hpp"
# include "./class/buttons.hpp"
# include "./color.hpp"
# include "utility/logger.hpp"

# include "./class3D/cube3D.hpp"
# include "../../raylib/src/rlgl.h"

# include <string>
# include <iostream>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <vector>
# include <cmath>

# define G 800
# define PLAYER_JUMP_SPD 600.0f
# define PLAYER_HOR_SPD 200.0f
# define MAX_INPUT_CHARS 8

# define CENTER_SCREEN {(float)game->screenWidth / 2 - 150, (float)game->screenHeight / 2 - 20}

# define DARKGRAY1   CLITERAL(Color){ 60, 60, 60, 255 }
# define DARKGRAY2   CLITERAL(Color){ 140, 140, 140, 255 }
# define DARKPURPLE2 CLITERAL(Color){ 46, 23, 126, 255 } 
# define MYDARKGREEN  CLITERAL(Color){ 0, 148, 54, 255 }

using std::string;

struct MultipleCam2D;
class BUTTONS;

typedef struct Mouse{
	Vector2	pos;
	float	camZoom;
	int		clickName = 0;
}	Mouse;

typedef struct NeedBy2DCam{
	RenderTexture 	textForCam2;
	RenderTexture 	textForCam;
	Rectangle		rectForCam;
	Camera2D 		camera;
	Image			image;
}	NeedBy2DCam;

typedef struct MultipleCam2D{
	NeedBy2DCam	camera00;
	NeedBy2DCam camera01;
	NeedBy2DCam camera02;
	NeedBy2DCam camera03;
	NeedBy2DCam camera04;
	NeedBy2DCam camera05;
	NeedBy2DCam camera06;
	NeedBy2DCam camera07;
	NeedBy2DCam camera08;
	NeedBy2DCam camera09;
}	MultipleCam2D;

typedef struct NeedBy3DCam{
	RenderTexture 	textForCam2;
	RenderTexture 	textForCam;
	Rectangle		rectForCam;
	Camera2D 		camera2D;
	Camera 			camera3D;
	Image			image;
}	NeedBy3DCam;

typedef struct MultipleCam3D{
	NeedBy3DCam	camera00;
	NeedBy3DCam camera01;
	NeedBy3DCam camera02;
	NeedBy3DCam camera03;
	NeedBy3DCam camera04;
	NeedBy3DCam camera05;
	NeedBy3DCam camera06;
	NeedBy3DCam camera07;
	NeedBy3DCam camera08;
	NeedBy3DCam camera09;
}	MultipleCam3D;

typedef struct Select
{
public:
	Select(void) { };

	Player		*lastPlayer;	// 1
	Player		*player;	// 1
	SquareProps	*lastProp;		// 2
	SquareProps	*prop;		// 2
	EnvItems	*lastItem;		// 3
	EnvItems	*item;		// 3
	int			lastSelected = 0;
	int			selected = 0;
	int			lastType = 0;
	int			type = 0;	// Select witch
	int			nbr = 0;		// Nbr of prop

	int			lastNbr = 0;
	bool		resetTxt = false; // If deselect items

	int			letterCount = 0;
	int			witchBox = 0;
}	Select;

typedef struct MenuUp
{
	BUTTONS		buttonControlClose;
	BUTTONS		buttonControlOpen;
	BUTTONS		buttonColorClose;
	BUTTONS		buttonColorOpen;
	BUTTONS		buttonListClose;
	BUTTONS		buttonListOpen;

	BUTTONS		play;
	BUTTONS		stop;
}	MenuUp;

typedef struct MenuSideDown
{
	BUTTONS		buttonMiddleClose;
	BUTTONS		buttonMiddleOpen;
	BUTTONS		buttonRightClose;
	BUTTONS		buttonRightOpen;
	BUTTONS		buttonLeftClose;
	BUTTONS		buttonLeftOpen;
}	MenuSideDown;

typedef struct TrioBox
{
	Vector2		posTextBox;

	Rectangle	writeBox;
	Rectangle	hitBox;
}	TrioBox;

typedef struct TextBoxSideUp
{
	TrioBox		RightBox0;
	TrioBox		LeftBox0;
	TrioBox		RightBox1;
	TrioBox		LeftBox1;

}	TextBoxSideUp;

typedef struct Drag
{
	EnvItems	*square;
	EnvItems	*squareSelect;
	EnvItems	*triangle;
	EnvItems	*triangleSelect;
	EnvItems	*circle;
	EnvItems	*circleSelect;
	EnvItems	*other;
	EnvItems	*otherSelect;

	EnvItems	*platform;
	EnvItems	*platformSelect;
}	Drag;

typedef struct Ray3D
{
	Ray 			ray = {0}; // Picking line ray
	RayCollision	collision = {0};
}	Ray3D;

typedef struct RayForMove
{
	Ray 			ray = {0}; // Picking line ray
	Ray				lastRay;
	RayCollision	collision = {0};
}	RayForMove;

class Game
{

	public:
		Game(void);
		~Game(void);

	public:
		
		const int   screenWidth = 1500;
		const int   screenHeight = 800;
		float		delta;

		bool		ctCollision = false;
		int         characterSelection = 0;
		int			ctMenuSideDownButtons = 0;
		int			ctMenuUpButtons = 2;
		int			ctImgBuildGame = 1;
		int			ctStopAttack = 1;
		int			ctPlayStop = 1;
		int         ct_action = 0;
		int			ctMode = 1;
		// int			nbrSquare = 0;
		// int			nbrEnvi = 0;

		Mouse			mouse;
		Font			font1;
		Vector2			posCam = {650, 300};
		Select			selected2D;

		Image			imgCercleChrom;
		Texture2D		textCercleChrom;
		Rectangle		rectCercleChrom;
		MenuUp			buttonsMenuUp;
		TextBoxSideUp	textBoxSideUp;
		MenuSideDown	buttonsMenuSideDown;
		Drag			dragDrop;
		bool			colorCt = false;

		char rotation[MAX_INPUT_CHARS + 1] = "\0";
		

		//*********************************** 3D ***********************************//
		Ray3D			ray;
		RayForMove		rayForMove;

		void (*cameraUpdaters[])(Game *, Camera2D *, Player *, int, float, int, int);
};

/**----------------------------> Menu <-----------------------------**/
void			ftMenuChooseCharacter(Game *game, Player * player, Menu *menu);
void			ftChooseCharacter(Menu *menu);
void			ftChooseMenu(Menu *menu);

MultipleCam2D	*ftInitCameras(Game *game, MultipleCam2D *allCameras);
void			ftInitButtons(Game *game);

//**********************************************************************************//
//										2D											//
//**********************************************************************************//

/**--------------------------->> Init <<---------------------------**/

void	ftInitTextBoxSideUp(Game *game);

/**----------------------->> Control Panel <<-----------------------**/

void	ftControlItems(Game *game, Player *player, std::vector<EnvItems> *envItems, std::vector<SquareProps> *blocks);
void	ftSideUpMenu2D(Game *game, Player *player, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, Menu *menu, MultipleCam2D *allCameras);
void	ftSideUpControlMenu2D(Game *game, Player *player, Menu *menu);
void	ftSideDownMenu2D(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, MultipleCam2D *allCameras);
void	ftSelectItemsTop(Game *game, Camera2D *camera);
void	ftUpMenu2D(Game *game, Player *player, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, Camera2D *camera);
void	ftDrawVarsRiDownPanel(Game *game);
void	ftDrawBoarders(Game *game);

/**-------------------------> Build Game <--------------------------**/

void	ftRunBuildMode(Game *game, Player *player, std::vector<EnvItems> *envItems,
			std::vector<SquareProps> *blocks, Camera2D *camera);
void	ftMoveScreen(Game *game, Camera2D *camera);

/**----------------------------> Game <-----------------------------**/

void 	ftUpdatePlayer(Game *game, Player *player, Menu *menu, std::vector<EnvItems> *envItems, int envItemsLength, float delta);
void 	ftUpdateCameraCenter(Game *Game, Camera2D *camera, Player *player,
			int envItemsLength, float delta, int width, int height);
void	ftImgsGestion(Game *game, Player *player);

void	ftRoutine(Game *game, Player *player, Menu *menu, Camera2D *camera,
			std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems);
void	ftGestionProps(Game *game, std::vector<SquareProps> *blocks, std::vector<EnvItems> *envItems, float deltaTime, int envItemsLength);
void	ftKeyGestion(Game *game, Player *player, Menu *menu, float delta);

void	ftRunGameMode(Game *game, Menu menu, Player player, std::vector<EnvItems> envItems,
			std::vector<SquareProps> blocks, MultipleCam2D allCameras);
void	ftDrawAll(Game *game, Player *player, std::vector<EnvItems> *envItems, std::vector<SquareProps> *blocks);;

/**---------------------------> Utility <----------------------------**/

void	ftUsePlayerGravity(Player *player, std::vector<EnvItems> *envItems, float delta, int envItemsLength);
void	ftUseGravity(SquareProps *prop, std::vector<EnvItems> *envItems, float delta, int envItemsLength);
void	ftGravityGestion(Game *Game, Player *player, std::vector<SquareProps> *blocks);
char	*ft_ftoa(float f, int *status);
// void	ftKeyGestionBuildMode(Game *Game);

//**********************************************************************************//
//										3D											//
//**********************************************************************************//

/**------------------------->> Fonctions <<-------------------------**/

void	ftMode2D(Game *game, Menu *menu);
void 	ftMode3D(Game *Game);

MultipleCam3D   *ftInitCameras3D(Game *game, MultipleCam3D *allCameras);
void    		ftControlMainPanel(Game *game, CUBE3D *cubes, MultipleCam3D *allCameras);

#endif