#include "../../../myIncludes/class2D/envitems.hpp"
# include <iostream>

EnvItems::EnvItems(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name)
{
	_rectangle = {pos.x, pos.y, size.x, size.y};
	_color = color;
	_texture = texture;
	_blocking = blocking;
	_name = name;
	_varChar.nbr = 4;
	_varChar.propPosX = (char *)malloc(sizeof(char) * 9);
	_varChar.propPosY = (char *)malloc(sizeof(char) * 9);
	_varChar.propWidth = (char *)malloc(sizeof(char) * 9);
	_varChar.propHeight = (char *)malloc(sizeof(char) * 9);
	_varChar.propPosX[0] = '\0';
	_varChar.propPosY[0] = '\0';
	_varChar.propWidth[0] = '\0';
	_varChar.propHeight[0] = '\0';
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
	}
	return (*this);
}
