#include "../../../myIncludes/class2D/squareProps.hpp"

using namespace obj;

SquareProps::SquareProps(void)
{
	return;
}

SquareProps::~SquareProps(void)
{
	return;
}

void SquareProps::ftInitVars(void)
{
	this->_varCharPr.varCharPr.propPosX = (char *)calloc(sizeof(char), 9);
	this->_varCharPr.varCharPr.propPosY = (char *)calloc(sizeof(char), 9);
	this->_varCharPr.varCharPr.propWidth = (char *)calloc(sizeof(char), 9);
	this->_varCharPr.varCharPr.propHeight = (char *)calloc(sizeof(char), 9);
}

void SquareProps::ftDeleteVars(void)
{
	free(this->_varCharPr.varCharPr.propPosX);
	free(this->_varCharPr.varCharPr.propPosY);
	free(this->_varCharPr.varCharPr.propWidth);
	free(this->_varCharPr.varCharPr.propHeight);
}

SquareProps *SquareProps::ftReturnCopySquareProp(void)
{
	SquareProps *ret = new SquareProps;

	ret = this;
	return (ret);
}

SquareProps *SquareProps::ftInitSquareprops(Vector2 pos, Vector2 size,
				Color color, bool blocking, int nbr, std::string name)
{
	SquareProps *ret = new SquareProps;

	ret->_varCharPr.rect.width = size.x;
	ret->_varCharPr.rect.height = size.y;
	ret->_varCharPr.rect.x = pos.x;
	ret->_varCharPr.rect.y = pos.y;
	ret->pos.x = pos.x;
	ret->pos.y = pos.y;
	ret->color = color;
	ret->speed = 0;
	ret->_nbr = nbr;
	ret->blocking = blocking;
	ret->_varCharPr.name = name;

	return (ret);
}

// void	SquareProps::ftInitSquareprops(Vector2 pos, Vector2 size, Color color, bool blocking, int nbr)
// {
// 	this->_varCharPr.rect.width = size.x;
// 	this->_varCharPr.rect.height = size.y;
// 	this->_varCharPr.rect.x = pos.x;
// 	this->_varCharPr.rect.y = pos.y;
// 	this->pos.x = pos.x;
// 	this->pos.y = pos.y;
// 	this->color = color;
// 	this->speed = 0;
// 	this->_nbr = nbr;
// 	this->blocking = blocking;
// }

void SquareProps::ftChangeWorH(float size, char c)
{
	if (c == 'W')
		this->_varCharPr.rect.width = size;
	if (c == 'H')
		this->_varCharPr.rect.height = size;
}

VarCharPr *SquareProps::ftReturnVarsProp(void)
{
	return (&this->_varCharPr.varCharPr);
}

Rectangle SquareProps::ftReturnRectangle(void) const
{
	return (this->_varCharPr.rect);
}

Color SquareProps::ftReturnColorPix(void)
{
	return (this->_varCharPr.pixColor);
}

void SquareProps::ftInitColorPix(Color color)
{
	this->_varCharPr.pixColor = color;
}

void SquareProps::ftInitColor(Color color)
{
	this->color = color;
}

Color SquareProps::ftReturnRecColor(void) const
{
	return (this->color);
}

Vector2 *SquareProps::ftReturnPositionPtr(void)
{
	return (&this->pos);
}

float SquareProps::ftReturnSpeed(void) const
{
	return (this->speed);
}

void SquareProps::ftSetSpeed(float speed)
{
	this->speed = speed;
}

void SquareProps::ftChangeSpeed(float speed)
{
	this->speed += speed;
}

void SquareProps::ftMovePosition(float x, float y)
{
	this->pos.x += x;
	this->_varCharPr.rect.x += x;
	this->pos.y += y;
	this->_varCharPr.rect.y += y;
}

void SquareProps::ftInitPosition(Vector2 pos)
{
	this->pos.x = pos.x;
	this->_varCharPr.rect.x = pos.x;
	this->pos.y = pos.y;
	this->_varCharPr.rect.y = pos.y;
}
float SquareProps::ftReturnWideorHigh(char c) const
{
	if (c == 'W') // Width
		return (this->_varCharPr.rect.width);
	if (c == 'H') // Hight
		return (this->_varCharPr.rect.height);
	return (0);
}

float SquareProps::ftReturnSpeedX(char c) const
{
	if (c == 'X')
		return (this->speedX);
	return (0);
}

void SquareProps::ftSetSpeedX(float speed, char c)
{
	if (c == 'X')
		this->speedX = speed;
}

void SquareProps::ftChangeSpeedX(float speed, char c)
{
	if (c == 'X')
		this->speedX += speed;
}

int SquareProps::ftReturnNbr(void) const
{
	return (this->_nbr);
}

float SquareProps::ftReturnSqurtPos(char c) const
{
	if (c == 'X')
		return (this->pos.x);
	if (c == 'Y')
		return (this->pos.y);
	return (0);
}

float SquareProps::ftReturnSpeedModifier(char c) const
{
	if (c == 'X')
		return (this->speedModifier.x);
	if (c == 'Y')
		return (this->speedModifier.y);
	return (0);
}

void SquareProps::ftSetSpeedModifier(float speed, char c)
{
	if (c == 'X')
		this->speedModifier.x = speed;
	if (c == 'Y')
		this->speedModifier.y = speed;
}

void SquareProps::ftChangeSpeedModifier(float speed, char c)
{
	if (c == 'X')
		this->speedModifier.x += speed;
	if (c == 'Y')
		this->speedModifier.y += speed;
}

//*** Add squareprops by drag and drop ***//

// void	SquareProps::ftInitSquareprops(Vector2 pos, Vector2 size, Color color, bool blocking, int nbr)
// {
// 	this->_varCharPr.rect.width = size.x;
// 	this->_varCharPr.rect.height = size.y;
// 	this->_varCharPr.rect.x = pos.x;
// 	this->_varCharPr.rect.y = pos.y;
// 	this->pos.x = pos.x;
// 	this->pos.y = pos.y;
// 	this->color = color;
// 	this->speed = 0;
// 	this->_nbr = nbr;
// 	this->blocking = blocking;
// }