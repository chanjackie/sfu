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
CMAKE_SOURCE_DIR = /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/sfu-cmpt/cmpt-373/e0/build

# Include any dependencies generated for this target.
include test/CMakeFiles/unit08.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/unit08.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/unit08.dir/flags.make

test/CMakeFiles/unit08.dir/unit08.cpp.o: test/CMakeFiles/unit08.dir/flags.make
test/CMakeFiles/unit08.dir/unit08.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/unit08.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/unit08.dir/unit08.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit08.dir/unit08.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/unit08.cpp

test/CMakeFiles/unit08.dir/unit08.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit08.dir/unit08.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/unit08.cpp > CMakeFiles/unit08.dir/unit08.cpp.i

test/CMakeFiles/unit08.dir/unit08.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit08.dir/unit08.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/unit08.cpp -o CMakeFiles/unit08.dir/unit08.cpp.s

# Object files for target unit08
unit08_OBJECTS = \
"CMakeFiles/unit08.dir/unit08.cpp.o"

# External object files for target unit08
unit08_EXTERNAL_OBJECTS = \
"/mnt/c/sfu-cmpt/cmpt-373/e0/build/test/CMakeFiles/doctest-main.dir/doctest.cpp.o"

bin/unit08: test/CMakeFiles/unit08.dir/unit08.cpp.o
bin/unit08: test/CMakeFiles/doctest-main.dir/doctest.cpp.o
bin/unit08: test/CMakeFiles/unit08.dir/build.make
bin/unit08: lib/libsolutions.a
bin/unit08: lib/libsupport.a
bin/unit08: test/CMakeFiles/unit08.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/unit08"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit08.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/unit08.dir/build: bin/unit08

.PHONY : test/CMakeFiles/unit08.dir/build

test/CMakeFiles/unit08.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && $(CMAKE_COMMAND) -P CMakeFiles/unit08.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unit08.dir/clean

test/CMakeFiles/unit08.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test /mnt/c/sfu-cmpt/cmpt-373/e0/build /mnt/c/sfu-cmpt/cmpt-373/e0/build/test /mnt/c/sfu-cmpt/cmpt-373/e0/build/test/CMakeFiles/unit08.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unit08.dir/depend

