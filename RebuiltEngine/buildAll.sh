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

# ---------------------------------------------------------------------------- #
# Post Build

./postBuild.sh

# ---------------------------------------------------------------------------- #
# build engine

# rm -fr bin/
pushd engine
./build.sh
popd

make -f Makefile.engine.linux.mak all

# echo "HELP: 1"

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

# ---------------------------------------------------------------------------- #
# Build TestBed

pushd testbed
./build.sh
popd

make -f Makefile.testbed.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

# ---------------------------------------------------------------------------- #
# Build Tests

make -f Makefile.tests.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "\033[32m\nAll assemblies built successfully.\033[0m"
