#include "../../../myIncludes/game.hpp"

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

// void	EnvItems::ftNewEnvItem(int nbr)
// {

// 	this->_envItems = new EnvItem[nbr];
// 	this->_allNbr = nbr;
// }

// EnvItems	*EnvItems::ftReturnCopyEnvItems(void)
// {

// 	EnvItems *ret = new EnvItems;

// 	ret = this;
// 	return (ret);
// }

// void 	EnvItems::ftInitEnvitem(Vector2 pos, Vector2 size,
// 			int blocking, Color color, Texture texture, int nbr)
// {
// 	this->_envItems[nbr].rect.x = pos.x;
// 	this->_envItems[nbr].rect.y = pos.y;
// 	this->_envItems[nbr].rect.width = size.x;
// 	this->_envItems[nbr].rect.height = size.y;
// 	this->_envItems[nbr].color = color;
// 	this->_envItems[nbr].texture = texture;
// 	this->_envItems[nbr].blocking = blocking;
// 	this->_envItems[nbr].nbr = nbr;
// 	this->_envItems[nbr]._varCharEnvi.enviPosX = (char *)calloc(sizeof(char), 9);
// 	this->_envItems[nbr]._varCharEnvi.enviPosY = (char *)calloc(sizeof(char), 9);
// 	this->_envItems[nbr]._varCharEnvi.enviWidth = (char *)calloc(sizeof(char), 9);
// 	this->_envItems[nbr]._varCharEnvi.enviHeight = (char *)calloc(sizeof(char), 9);
// }
EnvItems *EnvItems::ftInitOneEnvitem(Game *game, Vector2 pos, Vector2 size, int blocking,
									 Color color, Texture texture, int nbr, std::string name)
{
	this->_item.rect.x = pos.x;
	this->_item.rect.y = pos.y;
	this->_item.rect.width = size.x;
	this->_item.rect.height = size.y;
	this->_item.color = color;
	this->_item.texture = texture;
	this->_item.blocking = blocking;
	this->_item.nbr = nbr;
	this->_item.name = name;
	game->nbrEnvItems += 1;

	return (this);
}

void EnvItems::ftInitVarChar(void)
{
	this->_varCharEnvi.enviPosX = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviPosY = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviWidth = (char *)calloc(sizeof(char), 9);
	this->_varCharEnvi.enviHeight = (char *)calloc(sizeof(char), 9);
}

void EnvItems::ftDeleteVarChar(void)
{
	free(this->_varCharEnvi.enviPosX);
	free(this->_varCharEnvi.enviPosY);
	free(this->_varCharEnvi.enviWidth);
	free(this->_varCharEnvi.enviHeight);
}

EnvItems *EnvItems::ftReturnOneEnvitems(void)
{
	EnvItems *ret = new EnvItems;

	ret = this;
	return (ret);
}

// EnvItem		*EnvItems::ftReturnEnvitemPtr(int nbr)
// {
// 	return (&this->_envItems[nbr]);
// }

// Rectangle	EnvItems::ftReturnRectangle(int nbr) const
// {
// 	return (this->_envItems[nbr].rect);
// }

// Vector2		EnvItems::ftReturnEnviPos(int nbr) const
// {
// 	return ((Vector2){this->_envItems[nbr].rect.x, this->_envItems[nbr].rect.y});
// }

// Vector2		EnvItems::ftReturnEnviSize(int nbr) const
// {
// 	return ((Vector2){this->_envItems[nbr].rect.width, this->_envItems[nbr].rect.height});
// }

// Color		EnvItems::ftReturnEnviColor(int nbr) const
// {
// 	return (this->_envItems[nbr].color);
// }

// Texture2D	EnvItems::ftReturnEnviTexture(int nbr) const
// {
// 	return (this->_envItems[nbr].texture);
// }

// int			EnvItems::ftReturnEnviAllNbr(void) const
// {
// 	return (this->_allNbr);
// }

//=-= One item =-=//

EnvItem *EnvItems::ftReturnOneEnvitemPtr(void)
{
	return (&this->_item);
}

Rectangle EnvItems::ftReturnOneRectangle(void) const
{
	return (this->_item.rect);
}

Vector2 EnvItems::ftReturnOneEnviPos(void) const
{
	return ((Vector2){this->_item.rect.x, _item.rect.y});
}

Vector2 EnvItems::ftReturnOneEnviSize(void) const
{
	return ((Vector2){this->_item.rect.width, _item.rect.height});
}

Color EnvItems::ftReturnOneEnviColor(void) const
{
	return (this->_item.color);
}

Texture2D EnvItems::ftReturnOneEnviTexture(void) const
{
	return (this->_item.texture);
}

void EnvItems::ftDestroyImgs(void)
{
	UnloadTexture(this->_item.texture);
}