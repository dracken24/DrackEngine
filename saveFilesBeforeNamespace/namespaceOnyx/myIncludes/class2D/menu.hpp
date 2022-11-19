#ifndef MENU_HPP
# define MENU_HPP

#include "../../vendor/raylib/src/raylib.h"

class Menu
{
	public:
		Menu(void);
		~Menu(void);

		void	ftChangeStart(int ct);
		int		ftReturnStart(void);
		void	ftChangeChooseCt(int ct);
		int		ftReturnChooseCt(void);
		void	ftChangePlayer(int ct);
		int		ftReturnPlayer(void);

	private:
		int     menuCt = 10;
		int		chooseCt = 0;
		int		player = 0;
};

#endif
