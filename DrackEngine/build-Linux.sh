# /*****************************************************************************/
# /*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
# /* |             ---------------------------------------------             | */
# /* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  DATE:		 31-03-2023  		    *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  FILE: 	      build.sh              *--*             | */
# /* |             ---------------------------------------------             | */
# /*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
# /*****************************************************************************/

#!/bin/zsh
# Build script for engine
set echo on

cd Launcher
make

# echo "HELP: 1"

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi