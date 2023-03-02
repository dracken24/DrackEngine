#ifndef BUTTONS_HPP
# define BUTTONS_HPP

# include "../../../raylib/src/raylib.h"
// # include <stdlib.h>
# include <iostream>

class BUTTONS
{
	public:
		BUTTONS(void);
		BUTTONS(BUTTONS const &src);
		~BUTTONS(void);

		void		ftInitButton(Vector2 pos, Vector2 size,
						Color color, Texture2D texture, int nbr);

		Vector2		ftReturnPosition(void) const;
		Vector2		ftReturnSize(void) const;
		Color		ftReturnColor(void) const;
		Texture2D	ftReturnTexture(void) const;
		Rectangle	ftReturnRectangle(void) const;
		int			ftReturnNbr(void) const;

		void		ftUnloadTexture(void);

	private:
		Rectangle		_rect;
		Texture2D		_texture;
		Color			_color;

		int				_nbr;
};

#endif