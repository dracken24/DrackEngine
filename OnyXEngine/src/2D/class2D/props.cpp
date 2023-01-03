#include "../../../myIncludes/class2D/props.hpp"

Props::Props(void)
{
	return ;
}

Props::Props(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, string name) :
_rectangle({pos.x, pos.y, size.x, size.y}),
_color(color),
_texture(texture),
_blocking(blocking),
_name(name),
_nbr(nbr)
{
	return ;
}

Props::Props(Props const &src)
{
	*this = src;
	return ;
}

Props::~Props(void)
{
	return ;
}

Props	&Props::operator=(Props const &rhs)
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
		this->_varChar = rhs._varChar;
	}
	return (*this);
}

/*******************************************************************************/

// Modification //
void	Props::ftSetPos(Vector2 pos)
{
	this->_rectangle.x = pos.x;
	this->_rectangle.y = pos.y;
}

void	Props::ftSetSize(Vector2 size)
{
	this->_rectangle.width = size.x;
	this->_rectangle.height = size.y;
}

void	Props::ftMovePos(Vector2 pos)
{
	this->_rectangle.x += pos.x;
	this->_rectangle.y += pos.y;
}

void	Props::ftChangeName(string name)
{
	this->_name = name;
}

void	Props::ftDeleteVarsChar(void)
{
	free(this->_varChar.propPosX);
	free(this->_varChar.propPosY);
	free(this->_varChar.propWidth);
	free(this->_varChar.propHeight);
}

void	Props::ftChangeColor(Color color)
{
	this->_color = color;
}

/*************************************************************************************/

// Return //
std::string	Props::ftReturnName(void) const
{
	return (this->_name);
}

Vector2		Props::ftReturnSize(void) const
{
	return (Vector2{this->_rectangle.width, this->_rectangle.height});
}

Vector2		Props::ftReturnPos(void) const
{
	return (Vector2{this->_rectangle.x, this->_rectangle.y});
}

Rectangle	Props::ftReturnRectangle(void) const
{
	return (this->_rectangle);
}

Texture2D	Props::ftReturnTexture(void) const
{
	return (this->_texture);
}

Color		Props::ftReturnColor(void) const
{
	return (this->_color);
}

int			Props::ftReturnBlocking(void) const
{
	return (this->_blocking);
}

int			Props::ftReturnNbr(void) const
{
	return (this->_nbr);
}

VarChar		*Props::ftReturnVarChar(void)
{
	return (&this->_varChar);
}

//***********************************************************************************//

void        Props::ftUnloadTexture(void)
{
    UnloadTexture(this->_texture);
}
