# /*****************************************************************************/
# /*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
# /* |             ---------------------------------------------             | */
# /* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  DATE:		 24-12-2023  		    *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  FILE: 	    Launcher.cpp            *--*             | */
# /* |             ---------------------------------------------             | */
# /*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
# /*****************************************************************************/

# include "Launcher.hpp"

Launcher::Launcher(void)
{
    this->init();
}

Launcher::~Launcher(void)
{
    this->Exit();
}

void    Launcher::init(void)
{
    InitWindow(1200, 750, "DrackLanucher");
    SetTargetFPS(60);

    this->_exitCt = false;
}

void    Launcher::update(void)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        system("cd ../Engine && make");
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->_exitCt = true;
    }

    draw();
}

void    Launcher::draw(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawText("Press Enter to start", 375, 250, 40, BLACK);
    DrawText("       Engine       ", 340, 320, 60, BLACK);
    
    EndDrawing();
}

void    Launcher::Exit(void)
{
    CloseWindow();
}

bool    Launcher::GetExitCt(void)
{
    return (_exitCt);
}
