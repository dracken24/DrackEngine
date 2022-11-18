#ifndef BUTTONS_HPP
# define BUTTONS_HPP

#include "../../vendor/raylib/src/raylib.h"
#include <iostream>

class Buttons
{
	public:
		Buttons(/* args */);
		~Buttons();

		Buttons	*ftInitButton(Vector2 pos, Vector2 size,
					Color color, Texture texture, int nbr, std::string name);
		
		void		ftDeleteButtonTexture(void);

		Rectangle	ftReturnRectangle(void) const;
		Texture2D	ftReturnTexture(void) const;
		Vector2		ftReturnPosition(void) const;

	private:
		Texture2D	_texture;
		Color		_color;
		Rectangle	_rect;
		Color		_pixColor;

		int			_nbr;

		std::string _name;
};

#endif
