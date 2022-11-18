#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "../../vendor/raylib/src/raylib.h"
# include "../../vendor/raylib/src/raymath.h"
// # include "raylib.h"
// # include "raymath.h"
#include "weapon.hpp"
# include <iostream>
# include <string>

# define MAX_INPUT_CHARS 8

typedef struct VarChar
{
	char *plyPosX;
	char *plyPosY;
	char *plyWidth;
	char *plyHeight;
	char *collBoxPosX;
	char *collBoxPosY;
	char *collBoxWidth;
	char *collBoxHeight;
	int	nbr = 8;
}	VarChar;

typedef struct SelectionBoxPly
{
	int		selectBoxNbr = 0;
}	SelectionBoxPly;

typedef struct VarsSideDownPanel
{
	Rectangle	_playerBox;
	Rectangle	collisionBox;
	VarChar		varChar;
	Color		pixColor;
}	VarsSideDownPanel;

class Player
{
	public:
		Player(void);
		~Player(void);
	
		void		ftInitPlayerImgs(int nbr);
		void		ftInitImgsEd(void);
		void		ftInitImgsIchigo(void);
		void		ftInitImgsMeliodas(void);
		void		ftSetPosition(Vector2 pos);

		void		ftInitVarChar(void);
		void		ftDeleteVarChar(void);
		SelectionBoxPly		*ftSelectionBoxPly(void);

		Player		*ftReturnPlayer(void);
		VarChar		*ftReturnVarsChar(void);

		Vector2		ftReturnPlayerPosition(void);
		Vector2		*ftReturnPlayerPositionPtr(void);
		float		ftReturnPlayerPositionX(void);
		float		ftReturnPlayerPositionY(void);

		void		ftChangePosition(float x, float Y);
		void		ftMovePosition(float x, float y);

		void		ftSetSpeed(float speed);
		float		ftReturnSpeed(void);
		void		ftChangeSpeed(float speed);
		bool		ftReturnJump(void);
		void		ftChangeJump(bool jump);

		Texture2D	ftReturnGoodImage(std::string string, int ct);
		void		ftSetCollosionBox(Vector2 pos, Vector2 size, Vector2 ajust);
		Rectangle	ftReturnCollisionBox(void) const;
		Rectangle	FtReturnRectanglePlayer(void) const;
		Rectangle	ftReturnRectangleCollBox(void) const;
		void		ftInitRectanglePlayer(Vector2 pos, Vector2 size);

		Vector2		ftReturnAjustCollisionBox(void) const;
		Vector2		ftReturnCollisionBoxPos(void) const;
		void		ftMoveCollisionBox(Vector2 pos);
		void		ftChangeCollisionBoxSize(Vector2 pos);
		int			ftReturnCollBoxPos(char c) const;
		int			ftReturnCollBoxSize(char c) const;
		float		ftReturnAjustCollBox(char c) const;
		void		ftSetAjustCollBox(Vector2 pos);

		int			ftReturnCt(void) const;
		void		ftChangeCt(int ct);
		int			ftReturnAttackCt(void) const;
		void		ftChangeAttackCt(int ct);
		int			ftReturnFace(void) const;
		void		ftChangeFace(int face);

		void		ftInitCtMoveX(int ct);
		void		ftInitCtMoveY(int ct, std::string string);
		int			ftReturnCtMoveX(void) const;
		int			ftReturnctMoveY(std::string string) const;

		int			ftReturnMoveAttackLftX(void) const;
		void		ftChangeMoveAttackLftX(int ct);
		int			ftReturnMoveAttackRiX(void) const;
		void		ftChangeMoveAttackRiX(int ct);
		int			ftReturnMoveIdleX(void) const;
		void		ftChangeMoveIdleX(int ct);
		int			ftReturnMoveAttackY(void) const;
		void		ftChangeMoveAttackY(int ct);


		int			ftReturnCtIdle(void) const;
		void		ftChangeCtIdle(int ct);
		int			ftReturnCtMove(void) const;
		void		ftChangeCtMove(int ct);
		int			ftReturnCtJump(void) const;
		void		ftChangeCtJump(int ct);
		int			ftReturnCtFall(void) const;
		void		ftChangeCtFall(int ct);
		int			ftReturnCtAttack(void) const;
		void		ftChangeCtAttack(int ct);

		float		ftReturnLastY(void) const;
		void		ftChangeLastY(int ct);

		bool		ftReturnDoAttack(void) const;
		void		ftChangeDoAttack(bool ct);

		bool		ftReturnCollX(void) const;
		void		ftChangeCollX(bool ct);

		int			ftReturnNbr(void) const;

		void		ftDestroyImgs1(void);
		void		ftDestroyImgs2(void);
		void		ftDestroyImgs3(void);

		// Player		ftReturnPlayerCpy(void);

	/***************************** Weapon ****************************/

		void		ftInitWeapon(std::string name, Vector2 pos, Vector2 size);
		
		Rectangle	ftReturnWeaponCollRect(void) const;
		float		ftReturnWeaponCollBoxPos(char c) const;
		float		ftReturnWeaponCollBoxSize(char c) const;
		float		ftReturnWeaponDamage(void) const;
		float		ftReturnAddWeaponDamage(void) const;
		std::string	ftReturnWeaponName(void) const;

		void		ftChangeWeaponCollBoxPos(float pos,char c);
		void		ftNewWeaponCollBoxPos(float pos,char c);
		void		ftChangeWeaponCollBoxSize(float size,char c);
		void		ftChangeWeaponDamage(float damage);
		void		ftAddWeaponDamage(float damage);

	/*****************************************************************/
	private:
		Weapon		_weapon;

		Texture2D	p1_idle_ri[4];
		Texture2D	p1_idle_lft[4];
		Texture2D	p1_runLft[8];
		Texture2D	p1_runRi[8];
		Texture2D	p1_jumpl[3];
		Texture2D	p1_jumpr[3];
		Texture2D	p1_falll[2];
		Texture2D	p1_fallr[2];
		Texture2D	p1_attack00ri[7];
		Texture2D	p1_attack00lft[7];
		int			ct = 0;
		int			ctA = 0;
		int			face = 0;
		int			moveX;
		int			moveIdleY;
		int			moveMoveY;
		int			moveAttackLftX = 0;
		int			moveAttackRiX = 0;
		int			moveAttackY = 0;

		Vector2		position;
		Vector2		adjustCollBox;
		float		speed;
		bool		canJump;
		int			ctIdle;
		int			ctMove;
		int			ctJump;
		int			ctFall;
		int			ctAttack;
		int			moveIdleX;

		float		lastY = 0;
		int			nbr = 0;
		bool		doAttack = false;
		bool		collX = false;
		Player		*_player;

		VarsSideDownPanel	_varsSideDownPanel;
		SelectionBoxPly		_selectionBox;
};

#endif