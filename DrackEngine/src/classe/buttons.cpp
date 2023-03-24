/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackenLib PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    buttons.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../myIncludes/class/buttons.hpp"

BUTTONS::BUTTONS(void)
{
    return ;
}

BUTTONS::BUTTONS(BUTTONS const &src)
{
    *this = src;

    return ;
}

BUTTONS::~BUTTONS(void)
{
    return ;
}

//******************************** Init ********************************//

void		BUTTONS::ftInitButton(Vector2 pos, Vector2 size,
				Color color, Texture2D texture, int nbr)
{
    this->_rect.x = pos.x;
    this->_rect.y = pos.y;
    this->_rect.width = size.x;
    this->_rect.height = size.y;
    this->_color = color;
    this->_texture = texture;
    this->_nbr = nbr;
}

//******************************* Return *******************************//

Vector2     BUTTONS::ftReturnPosition(void) const
{
    return ((Vector2){this->_rect.x, this->_rect.y});
}

Vector2     BUTTONS::ftReturnSize(void) const
{
    return ((Vector2){this->_rect.width, this->_rect.height});
}

Color       BUTTONS::ftReturnColor(void) const
{
    return (this->_color);
}

Texture2D   BUTTONS::ftReturnTexture(void) const
{
    return (this->_texture);
}

int         BUTTONS::ftReturnNbr(void) const
{
    return (this->_nbr);
}

Rectangle   BUTTONS::ftReturnRectangle(void) const
{
    return (this->_rect);
}

//******************************* Unload *******************************//

void        BUTTONS::ftUnloadTexture(void)
{
    UnloadTexture(this->_texture);
}
