#include "../../../myIncludes/class2D/menu.hpp"

Menu::Menu(void)
{
	return ;
}

Menu::~Menu(void)
{
	return ;
}

void	Menu::ftChangeStart(int ct)
{
	this->menuCt = ct;
}

int		Menu::ftReturnStart(void)
{
	return (this->menuCt);
}

void	Menu::ftChangeChooseCt(int ct)
{
	this->chooseCt = ct;
}

int		Menu::ftReturnChooseCt(void)
{
	return (this->chooseCt);
}

void	Menu::ftChangePlayer(int ct)
{
	this->player = ct;
}

int		Menu::ftReturnPlayer(void)
{
	return (this->player);
}
