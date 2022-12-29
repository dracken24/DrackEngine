#include "../../../myIncludes/class2D/squareProps.hpp"
#include <iostream>

SquareProps::SquareProps(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name) : Props()
{
	_rectangle = {pos.x, pos.y, size.x, size.y};
	_color = color;
	_texture = texture;
	_blocking = blocking;
	_name = name;
	_varChar.nbr = 4;
	_varChar.propPosX = (char *)malloc(sizeof(char) * 10);
	_varChar.propPosY = (char *)malloc(sizeof(char) * 10);
	_varChar.propWidth = (char *)malloc(sizeof(char) * 10);
	_varChar.propHeight = (char *)malloc(sizeof(char) * 10);
	_varChar.propPosX[0] = '\0';
	_varChar.propPosY[0] = '\0';
	_varChar.propWidth[0] = '\0';
	_varChar.propHeight[0] = '\0';
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
		this->_speedModifier = rhs._speedModifier;
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
