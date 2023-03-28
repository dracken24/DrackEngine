# /*****************************************************************************/
# /*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
# /* |             ---------------------------------------------             | */
# /* |             *--*  PROJET: DrackenLib PAR: Dracken24  *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  DATE:		 24-03-2023  		    *--*             | */
# /* |             ---------------------------------------------             | */
# /* |             *--*  FILE: 	      Makefile              *--*             | */
# /* |             ---------------------------------------------             | */
# /*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
# /*****************************************************************************/

# ------------------------- Define custom functions --------------------------- #

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
platformpth = $(subst /,$(PATHSEP),$1)

# ---------------------------- Set global macros ------------------------------ #

buildDir := bin
executable := DrackEngine
target := $(buildDir)/$(executable)
sources := $(call rwildcard,Code/,*.cpp)
objects := $(patsubst Code/%, $(buildDir)/%, $(patsubst %.cpp, %.o, $(sources)))
depends := $(patsubst %.o, %.d, $(objects))
compileFlags := -std=c++17 -I include
linkFlags = -lglfw -lvulkan -Wall -Werror -Wextra

# --------------------------------- Find IOS ---------------------------------- #

ifeq ($(OS), Windows_NT)
	# Set Windows macros
	platform := Windows
	CXX ?= clang++
	linkFlags += -Wl,--allow-multiple-definition -pthread -lopengl32 -lgdi32 -lwinmm -mwindows -static -static-libgcc -static-libstdc++
	ignorFlags = -Wno-comment
	libGenDir := Code
	THEN := &&
	PATHSEP := \$(BLANK)
	MKDIR := -mkdir -p
	RM := -del /q
	COPY = -robocopy "$(call platformpth,$1)" "$(call platformpth,$2)" $3
else
	# Check for Linux
	UNAMEOS := $(shell uname)
	ifeq ($(UNAMEOS), Linux)
		# Set Linux macros
		platform := Linux
		CXX = clang++
		linkFlags += -lGL -lm -lpthread -ldl -lrt -lX11 -lX11-xcb -lxcb -lxkbcommon
		ignorFlags = -Wno-comment 
	endif
	# Check for Mac
	ifeq ($(UNAMEOS), Darwin)
		# Set macOS macros
		platform := macOS
		CXX = clang++
		linkFlags += -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
		ignorFlags = -Wno-comment
		libGenDir := Code
	endif

	# Set UNIX macros
	THEN := ;
	PATHSEP := /
	MKDIR := mkdir -p
	RM := rm -rf
	COPY = cp $1$(PATHSEP)$3 $2
endif

# -------------------------------- Compilation --------------------------------- #

# Default target, compiles, executes and cleans
all: signat msg_in $(target) msg_out execute

# Link the program and create the executable
$(target): $(objects)
	@$(CXX) $(objects) -o $(target) $(linkFlags) $(ignorFlags)

# Add all rules from dependency files
-include $(depends)

# Compile objects to the build directory
$(buildDir)/%.o: Code/%.cpp Makefile
	@$(MKDIR) $(call platformpth, $(@D))
	@$(CXX) -MMD -MP -c $(compileFlags) $(ignorFlags) $< -o  $@ $(CXXFLAGS)
	@printf "$G■"

# ---------------------------------- Execute ----------------------------------- #

execute:
	@$(target) $(ARGS)

# ---------------------------------- Messages ---------------------------------- #

msg_in:
	@echo $L"COMPILATION DE DrackEngine EN COURS..."$W

msg_out:
	@echo $L"\nDrackEngine READY !!!\n"$W

signat:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--* $LPROJET: DrackEngine  PAR: Dracken24$G *--*             |"
	@echo " |             ---------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"
	
# ----------------------------------- Colors ----------------------------------- #

L	= $(shell tput -Txterm setaf 5)
R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

# ----------------------------------- Clean ------------------------------------ #

re: clean all

clean:
	@echo $G"\n                                 Bye Bye ...\n"$W
	@$(RM) $(call platformpth, $(buildDir)/*)

# Lists phony targets for Makefile
.PHONY: all execute clean re msg_in msg_out signat
