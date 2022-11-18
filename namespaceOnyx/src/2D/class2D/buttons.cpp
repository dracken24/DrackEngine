#include "../../../myIncludes/class2D/buttons.hpp"

Buttons::Buttons(void)
{
	return ;
}

Buttons::~Buttons()
{
	return ;
}

Buttons	*Buttons::ftInitButton(Vector2 pos, Vector2 size,
			Color color, Texture texture, int nbr, std::string name)
{
	this->_rect.x = pos.x;
	this->_rect.y = pos.y;
	this->_rect.width = size.x;
	this->_rect.height = size.y;
	this->_color = color;
	this->_texture = texture;
	this->_nbr = nbr;
	this->_name = name;

	return (this);
}

void	Buttons::ftDeleteButtonTexture(void)
{
	UnloadTexture(this->_texture);
}

Rectangle	Buttons::ftReturnRectangle(void) const
{
	return (this->_rect);
}

Texture2D	Buttons::ftReturnTexture(void) const
{
	return (this->_texture);
}

Vector2		Buttons::ftReturnPosition(void) const
{
	return ((Vector2){this->_rect.x, this->_rect.y});
}
