#ifndef WEAPON_HPP
# define WEAPON_HPP

# include "../../vendor/raylib/src/raylib.h"
# include "iostream"

class Weapon
{
	public:
		Weapon(void);
		~Weapon(void);

		void	ftInitWeapon(std::string name, Vector2 pos, Vector2 size);

		Rectangle	ftReturnWeaponCollRect(void) const;
		float		ftReturnCollBoxPos(char c) const;
		float		ftReturnCollBoxSize(char c) const;
		float		ftReturnWeaponDamage(void) const;
		float		ftReturnAddWeaponDamage(void) const;
		std::string	ftReturnName(void) const;

		void		ftChangeCollBoxPos(float pos,char c);
		void		ftNewCollBoxPos(float pos,char c);
		void		ftChangeCollBoxSize(float size,char c);
		void		ftChangeWeaponDamage(float damage);
		void		ftAddWeaponDamage(float damage);

	private:
		std::string _name;
		Rectangle	_collisionBox;
		float		_damage = 0;
		float		_addDamage = 0;
};

#endif