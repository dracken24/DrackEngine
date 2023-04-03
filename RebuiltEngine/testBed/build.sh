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
# Build script for testbed
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cFilenames
echo "\033[35mCompiling testbed..."

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC" 
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine -Wl,-rpath,."
ignoreFlags="-Wno-comment"
defines="-D_DEBUG -DKIMPORT"

# echo "Building $assembly... in testBed/build.sh"
clang++ $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags $ignoreFlags
clang++ $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags $ignoreFlags
