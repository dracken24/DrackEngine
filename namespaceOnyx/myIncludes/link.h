#ifndef LINK_H
# define LINK_H

using namespace obj;

#include "game.hpp"

	void	ftMenuChooseCharacter(Game *Game, Player * player, Menu *menu);
	void	ftChooseCharacter(Menu *menu);
	void	ftChooseMenu(Menu *menu);

	//**********************************************************************************//
	//										2D											//
	//**********************************************************************************//

	/**--------------------------->> Init <<---------------------------**/

	void	ftInitTextBoxSideUp(Game *game);

	/**----------------------->> Control Panel <<-----------------------**/

	void	ftControlItems(Game *game, Player *player, EnvItems **envItems, SquareProps **blocks);
	void	ftSideUpMenu2D(Game *game, Player *player, Menu *menu, MultipleCam2D *allCameras);
	void	ftSideUpControlMenu2D(Game *game, Player *player, Menu *menu);
	void	ftSideDownMenu2D(Game *game, Camera2D *camera);
	void	ftSelectItemsTop(Game *game, Camera2D *camera);
	void	ftUpMenu2D(Game *game, Camera2D *camera);
	void	ftDrawVarsRiDownPanel(Game *game);
	void	ftDrawBoarders(Game *Game);

	/**-------------------------> Build Game <--------------------------**/

	// void	ftRunBuildMode(Game *Game,Stop *buildGame);
	void	ftRunBuildMode(Game *game, Player *player, EnvItems **envItems,
				SquareProps **blocks, Camera2D *camera);
	void	ftMoveScreen(Game *game, Camera2D *camera);

	/**----------------------------> Game <-----------------------------**/

	void 	ftUpdatePlayer(Game *game, Player *player, Menu *menu, EnvItems **envItems, int envItemsLength, float delta);
	void 	ftUpdateCameraCenter(Game *game, Camera2D *camera, Player *player,
				int envItemsLength, float delta, int width, int height);
	void	ftImgsGestion(Game *game, Player *player);

	void	ftRoutine(Game *game, Player *player, Menu *menu, Camera2D *camera, SquareProps **blocks, EnvItems **envItems);
	void	ftGestionProps(Game *game, SquareProps **blocks, EnvItems **envItems, float deltaTime, int envItemsLength);
	void	ftKeyGestion(Game *game, Player *player, Menu *menu, float delta);

	void	ftRunGameMode(Game *game, Menu menu, Player player, EnvItems **envItems,
				SquareProps **blocks, MultipleCam2D allCameras);
	void	ftDrawAll(Game *ame, Player *player, EnvItems **envItems, SquareProps **blocks);

	/**---------------------------> Utility <----------------------------**/

	void	ftUsePlayerGravity(Player *player, EnvItems **envItems, float delta, int envItemsLength);
	void	ftUseGravity(SquareProps *prop, EnvItems **envItems, float delta, int envItemsLength);
	void	ftGravityGestion(Game *game, Player *player, SquareProps **blocks);
	char	*ft_ftoa(float f, int *status);
	void	ftKeyGestionBuildMode(Game *Game);

	//**********************************************************************************//
	//										3D											//
	//**********************************************************************************//

	/**------------------------->> Fonctions <<-------------------------**/

	void	ftMode2D(Game *game, Menu *menu);
	void 	ftMode3D(Game *game);
#endif