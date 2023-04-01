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

mkdir -p ../bin

# Get a list of all the .cpp files.
cFilenames=$(find . -type f -name "*.cpp")

echo "Files:" $cFilenames

assembly="engine"
compilerFlags="-g -shared -fdeclspec -fPIC"
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I$VULKAN_SDK/include"
linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/lib -L/usr/X11R6/lib"
ignoreFlags="-Wno-comment"
defines="-D_DEBUG -DKEXPORT"

echo "Building $assembly... in engine/build.sh"
clang++ $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags $ignoreFlags
