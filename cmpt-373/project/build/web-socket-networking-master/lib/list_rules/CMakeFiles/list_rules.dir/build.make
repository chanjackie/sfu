# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/sfu-cmpt/cmpt-373/project/build

# Include any dependencies generated for this target.
include web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/depend.make

# Include the progress variables for this target.
include web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/progress.make

# Include the compile flags for this target's objects.
include web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/flags.make

web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.o: web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/flags.make
web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/list_rules/GameVarList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/list_rules.dir/GameVarList.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/list_rules/GameVarList.cpp

web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/list_rules.dir/GameVarList.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/list_rules/GameVarList.cpp > CMakeFiles/list_rules.dir/GameVarList.cpp.i

web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/list_rules.dir/GameVarList.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/list_rules/GameVarList.cpp -o CMakeFiles/list_rules.dir/GameVarList.cpp.s

# Object files for target list_rules
list_rules_OBJECTS = \
"CMakeFiles/list_rules.dir/GameVarList.cpp.o"

# External object files for target list_rules
list_rules_EXTERNAL_OBJECTS =

lib/liblist_rules.a: web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/GameVarList.cpp.o
lib/liblist_rules.a: web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/build.make
lib/liblist_rules.a: web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/liblist_rules.a"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && $(CMAKE_COMMAND) -P CMakeFiles/list_rules.dir/cmake_clean_target.cmake
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list_rules.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/build: lib/liblist_rules.a

.PHONY : web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/build

web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules && $(CMAKE_COMMAND) -P CMakeFiles/list_rules.dir/cmake_clean.cmake
.PHONY : web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/clean

web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/list_rules /mnt/c/sfu-cmpt/cmpt-373/project/build /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : web-socket-networking-master/lib/list_rules/CMakeFiles/list_rules.dir/depend
