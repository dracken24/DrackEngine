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
					Color color, Texture2D texture, int nbr, std::string name);
		
		void		ftDeleteButtonTexture(void);

		Rectangle	ftReturnRectangle(void);
		Texture2D	ftReturnTexture(void);
		Vector2		ftReturnPosition(void);

	private:
		Texture2D	_texture;
		Color		_color;
		Rectangle	_rect;
		Color		_pixColor;

		int			_nbr;

		std::string _name;
};

#endif
