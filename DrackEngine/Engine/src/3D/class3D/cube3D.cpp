/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		 cube3D.hpp    	     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../myIncludes/class3D/cube3D.hpp"

CUBE3D::CUBE3D(void)
{
	return ;
}

CUBE3D::CUBE3D(CUBE3D const &src)
{
	*this = src;
}

CUBE3D::~CUBE3D(void)
{
	return ;
}

//*************************************** Init ***************************************//

void	CUBE3D::ftInitCube(Vector3 pos, Vector3 size, Texture texture, string name)
{
	this->_cube.pos.x = pos.x;
	this->_cube.pos.y = pos.y;
	this->_cube.pos.z = pos.z;
	this->_cube.size.x = size.x;
	this->_cube.size.y = size.y;
	this->_cube.size.z = size.z;
	this->_cube.texture = texture;
	this->_cube.name = name;
}

//************************************** Change **************************************//

void	CUBE3D::ftChangePosition(Vector3 pos)
{
	this->_cube.pos.x = pos.x;
	this->_cube.pos.y = pos.y;
	this->_cube.pos.z = pos.z;
}

void	CUBE3D::ftChangeSize(Vector3 size)
{
	this->_cube.size.x = size.x;
	this->_cube.size.y = size.y;
	this->_cube.size.z = size.z;
}

void	CUBE3D::ftChangeName(string name)
{
	this->_cube.name = name;
}

void	CUBE3D::ftChangeTexture(Texture texture)
{
	this->_cube.texture = texture;
}

void	CUBE3D::ftMovePosition(Vector3 pos)
{
	this->_cube.pos.x += pos.x;
	this->_cube.pos.y += pos.y;
	this->_cube.pos.z += pos.z;
}

void	CUBE3D::ftExpendCube(Vector3 size)
{
	this->_cube.size.x += size.x;
	this->_cube.size.y += size.y;
	this->_cube.size.z += size.z;
}

//************************************** Return **************************************//

Cube3D		CUBE3D::ftReturnCube3D(void) const
{
	return (this->_cube);
}

Vector3		CUBE3D::ftReturnPosition(void) const
{
	return (this->_cube.pos);
}

Vector3		CUBE3D::ftReturnSize(void) const
{
	return (this->_cube.size);
}

string		CUBE3D::ftReturnName(void) const
{
	return (this->_cube.name);
}

Texture		CUBE3D::ftReturnTexture(void) const
{
	return (this->_cube.texture);
}
