#include "../../../myIncludes/class2D/props.hpp"

// using namespace obj;

// Props::Props(void)
// {
// 	return ;
// }

// Props::Props(Props const &src)
// {
// 	*this = src;
// 	return ;
// }

// Props::~Props(void)
// {
// 	return ;
// }

// /************************************** Gestion square props *****************************************/

// // Modify //

// void	Props::ftInitSquareProps(int nbr, std::string type)
// {
// 	if (type == "blocks")
// 	{
// 		this->_squareProps = new SquareProps[nbr];
// 	}
// 	else if (type == "plateforms")
// 	{
// 		this->_platforms = new SquareProps[nbr];
// 	}
// 	this->_nbr = nbr;
// }

// void	Props::ftKillSquareProps(void)
// {
// 	delete this->_squareProps;
// }

// void	Props::ftDeleteVarsChar(int nbr)
// {
// 	this->_squareProps[nbr].ftDeleteVars();
// }

// void	Props::ftAddProps(Vector2 pos, Vector2 size, Color color, bool blocking, int nbr, std::string type)
// {
// 	if (type == "blocks")
// 	{
// 		this->_squareProps[nbr].ftInitSquareprops(pos, size, color, blocking, nbr);
// 		this->_squareProps[nbr].ftInitVars();
// 	}
// 	else if (type == "plateforms")
// 	{
// 		this->_platforms[nbr].ftInitSquareprops(pos, size, color, blocking, nbr);
// 		this->_squareProps[nbr].ftInitVars();
// 	}
// }

// void	Props::ftChangeNbr(int nbr)
// {
// 	this->_nbr = nbr;
// }

// void	Props::ftSetPosSquareProp(Vector2 pos, int nbr)
// {
// 	this->_squareProps[nbr].ftInitPosition(pos);
// }

// void	Props::ftSetSpeed(float speed, int nbr)
// {
// 	this->_squareProps[nbr].ftSetSpeed(speed);
// }

// void	Props::ftMoveSquareProp(Vector2 pos, int nbr)
// {
// 	this->_squareProps[nbr].ftMovePosition(pos.x, pos.y);
// }

// void	Props::ftSetSpeedModifier(float speed, char c, int nbr)
// {
	
// 	if (c == 'X')
// 		this->_squareProps[nbr].ftSetSpeedModifier(speed, c);
// 	else if (c == 'Y')
// 		this->_squareProps[nbr].ftSetSpeedModifier(speed, c);
// }

// void	Props::ftChangeSpeedModifier(float speed, char c, int nbr)
// {
// 	if (c == 'X')
// 		this->_squareProps[nbr].ftChangeSpeedModifier(speed, c);
// 	else if (c == 'Y')
// 		this->_squareProps[nbr].ftChangeSpeedModifier(speed, c);
// }

// // Return //

// Props		Props::ftReturnCopyProps(void)
// {
// 	Props  ret;
// 	ret._squareProps = this->_squareProps;
// 	ret._platforms = this->_platforms;
// 	ret._nbr = this->_nbr;

// 	return (ret);
// }

// Rectangle	Props::ftReturnRectangleSqPr(int nbr)
// {
// 	return (this->_squareProps[nbr].ftReturnRectangle());
// }

// Color	Props::ftReturnRecColorSqPr(int nbr)
// {
// 	return (this->_squareProps[nbr].ftReturnRecColor());
// }

// float	Props::ftReturnSpeed(int nbr) const
// {
// 	return (this->_squareProps[nbr].ftReturnSpeed());
// }

// SquareProps	*Props::ftReturnSquareProp(int nbr) const
// {
// 	return (&this->_squareProps[nbr]);
// }

// int		Props::ftReturnNbr(void) const
// {
// 	return (this->_nbr);
// }

// int	Props::ftReturnOneNbr(int	nbr) const
// {
// 	return (this->_squareProps[nbr].ftReturnNbr());
// }

// float	Props::ftReturnSqurtPos(char c, int nbr) const
// {
// 	if (c == 'X')
// 		return (this->_squareProps[nbr].ftReturnSqurtPos('X'));
// 	else if (c == 'Y')
// 		return (this->_squareProps[nbr].ftReturnSqurtPos('Y'));
// 	return (0);
// }

// float	Props::ftReturnSqurtWorH(char c, int nbr) const
// {
// 	if (c == 'W')
// 		return (this->_squareProps[nbr].ftReturnWideorHigh('W'));
// 	else if (c == 'H')
// 		return (this->_squareProps[nbr].ftReturnWideorHigh('H'));
// 	return (0);
// }

// float	Props::ftReturnSpeedModifier(char c, int nbr) const
// {
// 	if (c == 'X')
// 		return (this->_squareProps[nbr].ftReturnSpeedModifier('X'));
// 	else if (c == 'Y')
// 		return (this->_squareProps[nbr].ftReturnSpeedModifier('Y'));
// 	return (0);
// }

/***************************************** --------- ********************************************/
