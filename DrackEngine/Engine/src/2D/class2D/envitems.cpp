/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		envitems.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../myIncludes/class2D/envitems.hpp"
# include <iostream>

EnvItems::EnvItems(void) : Props()
{
	return ;
}

EnvItems::EnvItems(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name) : Props(pos, size, blocking, color, texture, nbr, name)
{
	return ;
}

EnvItems::EnvItems(EnvItems const &src)
{
	*this = src;
	return;
}

EnvItems::~EnvItems(void)
{
    return ;
}

EnvItems	&EnvItems::operator=(EnvItems const &rhs)
{
	if (this != &rhs)
	{
		this->_rectangle.x = rhs._rectangle.x;
		this->_rectangle.y = rhs._rectangle.y;
		this->_rectangle.width = rhs._rectangle.width;
		this->_rectangle.height = rhs._rectangle.height;
		this->_color = rhs._color;
		this->_texture = rhs._texture;
		this->_blocking = rhs._blocking;
		this->_name = rhs._name;
		this->_nbr = rhs._nbr;
		this->_varChar.nbr = rhs._varChar.nbr;
		this->_varChar.propPosX = rhs._varChar.propPosX;
		this->_varChar.propPosY = rhs._varChar.propPosY;
		this->_varChar.propWidth = rhs._varChar.propWidth;
		this->_varChar.propHeight = rhs._varChar.propHeight;
	}
	return (*this);
}
