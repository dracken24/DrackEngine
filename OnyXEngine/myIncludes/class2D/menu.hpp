#ifndef MENU_HPP
# define MENU_HPP

#include "../../vendor/raylib/src/raylib.h"

class Menu
{
	public:
		Menu(void);
		~Menu(void);

		void	ftChangeChooseCt(int ct);
		void	ftChangePlayer(int ct);
		void	ftChangeStart(int ct);
		
		int		ftReturnChooseCt(void);
		int		ftReturnPlayer(void);
		int		ftReturnStart(void);

	private:
		int     menuCt = 10;
		int		chooseCt = 0;
		int		player = 0;
};

#endif
