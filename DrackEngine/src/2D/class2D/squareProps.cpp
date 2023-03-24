/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackenLib PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  squareProps.hpp         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../myIncludes/class2D/squareProps.hpp"
#include <iostream>

SquareProps::SquareProps(void) : Props()
{
	return ;
}

SquareProps::SquareProps(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name) : Props(pos, size, blocking, color, texture, nbr, name)
{
	_speedModifier.x = 0;
	_speedModifier.y = 0;
	_speed = 0;
	_speedX = 0;
	return ;
}

SquareProps::SquareProps(SquareProps const &src) : Props(src)
{
	*this = src;
	return ;
}

SquareProps::~SquareProps(void)
{
	return ;
}

SquareProps	&SquareProps::operator=(SquareProps const &rhs)
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
		this->_speedModifier.x = rhs._speedModifier.x;
		this->_speedModifier.y = rhs._speedModifier.y;
		this->_speed = rhs._speed;
		this->_speedX = rhs._speedX;
	}
	return (*this);
}

//**************************************************************//
// Modification //
void		SquareProps::ftSetSpeedModifier(float speed, char c)
{
	if (c == 'X')
		this->_speedModifier.x = speed;
	else if (c == 'Y')
		this->_speedModifier.y = speed;
}

void		SquareProps::ftSetSpeedX(float speed)
{
	this->_speedX = speed;
}

void		SquareProps::ftSetSpeed(float speed)
{
	this->_speed = speed;
}

void		SquareProps::ftChangeSpeedModifier(float speed, char c)
{
	if (c == 'X')
		this->_speedModifier.x += speed;
	else if (c == 'Y')
		this->_speedModifier.y += speed;
}

void		SquareProps::ftChangeSpeedX(float speed)
{
	this->_speedX += speed;
}

void		SquareProps::ftChangeSpeed(float speed)
{
	this->_speed += speed;
}

//**************************************************************//
// Return //
float		SquareProps::ftReturnSpeedModifier(char c) const
{
	if (c == 'X')
		return (this->_speedModifier.x);
	else if (c == 'Y')
		return (this->_speedModifier.y);
	return (0);
}

float		SquareProps::ftReturnSpeedX(char c) const
{
	return (this->_speedX);
}

float		SquareProps::ftReturnSpeed(void) const
{
	return (this->_speed);
}
