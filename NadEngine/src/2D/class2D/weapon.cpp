#include "../../../myIncludes/class2D/weapon.hpp"

Weapon::Weapon(void)
{
	return ;
}

Weapon::~Weapon(void)
{
	return ;
}

void	Weapon::ftInitWeapon(std::string name, Vector2 pos, Vector2 size)
{
	this->_name = name;
	this->_collisionBox.x = pos.x;
	this->_collisionBox.y = pos.y;
	this->_collisionBox.width = size.x;
	this->_collisionBox.height = size.y;
}

/***************************************** Change ****************************************/

void	Weapon::ftChangeCollBoxPos(float pos, char c)
{
	if (c == 'X')
		this->_collisionBox.x += pos;
	else if (c == 'Y')
		this->_collisionBox.y += pos;
}

void	Weapon::ftNewCollBoxPos(float pos, char c)
{
	if (c == 'X')
		this->_collisionBox.x = pos;
	else if (c == 'Y')
		this->_collisionBox.y = pos;
}

void	Weapon::ftChangeCollBoxSize(float size, char c)
{
	if (c == 'W')
		this->_collisionBox.width = size;
	else if (c == 'H')
		this->_collisionBox.height = size;
}

void	Weapon::ftChangeWeaponDamage(float damage)
{
	this->_damage = damage;
}

void	Weapon::ftAddWeaponDamage(float damage)
{
	this->_addDamage = damage;
}

/***************************************** Return ****************************************/

Rectangle	Weapon::ftReturnWeaponCollRect(void) const
{
	return (this->_collisionBox);
}

float	Weapon::ftReturnCollBoxPos(char c) const
{
	if (c == 'X')
		return (this->_collisionBox.x);
	else if (c == 'Y')
		return (this->_collisionBox.y);
	return (0);
}

float	Weapon::ftReturnCollBoxSize(char c) const
{
	if (c == 'H')
		return (this->_collisionBox.height);
	else if (c == 'W')
		return (this->_collisionBox.width);
	return (0);
}

float	Weapon::ftReturnWeaponDamage(void) const
{
	return (this->_damage);
}

float	Weapon::ftReturnAddWeaponDamage(void) const
{
	return (this->_addDamage);
}

std::string	Weapon::ftReturnName(void) const
{
	return (this->_name);
}
