# /*****************************************************************************/
# /*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
# /* |             ---------------------------------------------             | */
# /* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  DATE:		 24-12-2023  		    *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  FILE: 	    Launcher.hpp            *--*             | */
# /* |             ---------------------------------------------             | */
# /*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
# /*****************************************************************************/

#ifndef LAUNCHER_HPP
# define LAUNCHER_HPP

# include "../../../raylib/src/raylib.h"

# include <iostream>

class Launcher
{
    public:
        Launcher(void);
        ~Launcher(void);

        void    update(void);
        
        bool    GetExitCt(void);

    private:
        void    init(void);
        void    draw(void);
        void    Exit(void);

    private:
        bool    _exitCt;
};

#endif