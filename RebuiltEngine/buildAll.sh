# /*****************************************************************************/
# /*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
# /* |             ---------------------------------------------             | */
# /* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  DATE:		 31-03-2023  		    *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  FILE: 	     buildAll.sh            *--*             | */
# /* |             ---------------------------------------------             | */
# /*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
# /*****************************************************************************/

#!/bin/zsh
# Build script for rebuilding everything
set echo on

echo  "\033[32mBuilding everything...\n"

alias pushd='cd'
alias popd='cd ..'

rm -fr bin/
pushd engine
./build.sh
popd

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

pushd testBed
./build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "\033[32m\nAll assemblies built successfully.\033[0m"
