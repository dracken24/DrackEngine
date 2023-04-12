
BUILD_DIR := bin
OBJ_DIR := obj

ASSEMBLY := tests
EXTENSION := 
COMPILER_FLAGS := -g -MD -Werror=vla -fdeclspec -fPIC
INCLUDE_FLAGS := -Iengine/src -I$(VULKAN_SDK)\include
LINKER_FLAGS := -lstdc++ -L./$(BUILD_DIR)/ -lengine -Wl,-rpath,.
DEFINES := -D_DEBUG -DKIMPORT

# Make does not offer a recursive wildcard function, so here's one:
#rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_FILES := $(shell find $(ASSEMBLY) -name *.cpp)		# .cpp files
DIRECTORIES := $(shell find $(ASSEMBLY) -type d)		# directories with .h files
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)		# compiled .o objects

all: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	@echo "\033[33mScaffolding folder structure..."
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@echo Done."\n"

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@echo "\n"Linking $(ASSEMBLY)...
	@clang $(OBJ_FILES) -o $(BUILD_DIR)/$(ASSEMBLY)$(EXTENSION) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .c files
	@echo Compiling..."\n"

.PHONY: clean
clean: # clean build directory
	rm -rf $(BUILD_DIR)/$(ASSEMBLY)
	rm -rf $(OBJ_DIR)/$(ASSEMBLY)

$(OBJ_DIR)/%.cpp.o: %.cpp # compile .cpp to .o object
	@echo   $<...
	@clang $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

-include $(OBJ_FILES:.o=.d)
