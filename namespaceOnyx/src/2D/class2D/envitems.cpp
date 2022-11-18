#include "../../../myIncludes/class2D/envitems.hpp"

using namespace obj;

EnvItems::EnvItems(void)
{
	return;
}

EnvItems::EnvItems(EnvItems const &src)
{
	*this = src;
	return;
}

EnvItems::~EnvItems(void)
{
	return;
}

EnvItems	*EnvItems::ftInitOneEnvitem(Vector2 pos, Vector2 size, int blocking,
				Color color, Texture texture, int nbr, std::string name)
{
	EnvItems *ret = new EnvItems;

	ret->_item.rect.x = pos.x;
	ret->_item.rect.y = pos.y;
	ret->_item.rect.width = size.x;
	ret->_item.rect.height = size.y;
	ret->_item.color = color;
	ret->_item.texture = texture;
	ret->_item.blocking = blocking;
	ret->_item.nbr = nbr;
	ret->_item.name = name;

	return (ret);
}

void	EnvItems::ftInitVarChar(void)
{
	this->_varCharEnvi.enviPosX = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviPosY = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviWidth = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviHeight = (char *)calloc(sizeof(char), 9);
}

void	EnvItems::ftDeleteVarChar(void)
{
	free(this->_varCharEnvi.enviPosX);
	free(this->_varCharEnvi.enviPosY);
	free(this->_varCharEnvi.enviWidth);
	free(this->_varCharEnvi.enviHeight);
}

void		EnvItems::ftInitPosition(float x, float y)
{
	this->_item.rect.x = x;
	this->_item.rect.y = y;
}
void		EnvItems::ftChangePosition(float x, float y)
{
	this->_item.rect.x += x;
	this->_item.rect.y += y;
}

EnvItems	*EnvItems::ftReturnOneEnvitems(void)
{
	EnvItems *ret = new EnvItems;

	ret = this;
	return (ret);
}

void		EnvItems::ftChangeColor(Color color)
{
	this->_item.color = color;
}

EnvItem		*EnvItems::ftReturnOneEnvitemPtr(void)
{
	return (&this->_item);
}

Rectangle	EnvItems::ftReturnOneRectangle(void) const
{
	return (this->_item.rect);
}

Vector2		EnvItems::ftReturnOneEnviPos(void) const
{
	return ((Vector2){this->_item.rect.x, _item.rect.y});
}

Vector2		EnvItems::ftReturnOneEnviSize(void) const
{
	return ((Vector2){this->_item.rect.width, _item.rect.height});
}

Color		EnvItems::ftReturnOneEnviColor(void) const
{
	return (this->_item.color);
}

Texture2D	EnvItems::ftReturnOneEnviTexture(void) const
{
	return (this->_item.texture);
}

void		EnvItems::ftDestroyImgs(void)
{
	UnloadTexture(this->_item.texture);
}

VarCharEnvi *EnvItems::ftReturnVarsCharEnvi(void)
{
	return (&this->_varCharEnvi);
}
