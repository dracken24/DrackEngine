/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		  props.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef PROPS_HPP
# define PROPS_HPP

# include "../../../../raylib/src/raylib.h"
# include <iostream>
# include <string>

using std::string;

typedef struct VarChar
{
	std::string propPosX;
	std::string propPosY;
	std::string propWidth;
	std::string propHeight;
	
	int		nbr;
}	VarChar;

class Props
{
	public:
		Props(void);
		Props(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name);
		Props(Props const &src);
		~Props(void);

//************************************************************************//
	// Setters //
		void        ftSetPos(Vector2 pos);
		void		ftSetSize(Vector2 size);
		void        ftMovePos(Vector2 pos);
		void		ftChangeName(std::string name);
		void		ftChangeColor(Color color);

//************************************************************************//
	// Getters //
		std::string	ftReturnName(void) const;
		Vector2		ftReturnSize(void) const;
		Vector2		ftReturnPos(void) const;
		Rectangle   ftReturnRectangle(void) const;
		Texture2D   ftReturnTexture(void) const;
		Color       ftReturnColor(void) const;
		VarChar		*ftReturnVarChar(void);

		int			ftReturnBlocking(void) const;
		int         ftReturnNbr(void) const;

		void        ftUnloadTexture(void);

	protected:
		string		_name;
		Rectangle	_rectangle;
		Color		_color;
		Texture2D	_texture;

		int			_nbr;
		int			_blocking;

		VarChar		_varChar;
};

#endif