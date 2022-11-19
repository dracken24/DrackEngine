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
			Color color, Texture2D texture, int nbr, std::string name)
{
	Buttons *ret = new Buttons;

	ret->_rect.x = pos.x;
	ret->_rect.y = pos.y;
	ret->_rect.width = size.x;
	ret->_rect.height = size.y;
	ret->_color = color;
	ret->_texture = texture;
	ret->_nbr = nbr;
	ret->_name = name;

	return (ret);
}

void	Buttons::ftDeleteButtonTexture(void)
{
	UnloadTexture(this->_texture);
}

Rectangle	Buttons::ftReturnRectangle(void)
{
	return (this->_rect);
}

Texture2D	Buttons::ftReturnTexture(void)
{
	return (this->_texture);
}

Vector2		Buttons::ftReturnPosition(void)
{
	return ((Vector2){this->_rect.x, this->_rect.y});
}
