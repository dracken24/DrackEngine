#include "../../../myIncludes/game.hpp"

#include <iostream>

using namespace obj;

Props::Props(void)
{
	return;
}

Props::Props(Props const &src)
{
	*this = src;
	return;
}

Props::~Props(void)
{
	return;
}

// /************************************** Gestion square props *****************************************/

int Props::ftReturnNbr(std::string name) const
{
	if (name == "envi")
		return (this->_nbrEnvItems);
	else if (name == "square")
		return (this->_nbrSquareProps);
	else if (name == "butt")
		return (this->_nbrbuttons);
}

void Props::ftChangeNbr(int nbr, string name)
{
	if (name == "envi")
		this->_nbrEnvItems += nbr;
	else if (name == "square")
		this->_nbrSquareProps += nbr;
	else if (name == "butt")
		this->_nbrbuttons += nbr;
}