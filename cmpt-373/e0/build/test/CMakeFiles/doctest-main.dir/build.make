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
include test/CMakeFiles/doctest-main.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/doctest-main.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/doctest-main.dir/flags.make

test/CMakeFiles/doctest-main.dir/doctest.cpp.o: test/CMakeFiles/doctest-main.dir/flags.make
test/CMakeFiles/doctest-main.dir/doctest.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/doctest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/doctest-main.dir/doctest.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/doctest-main.dir/doctest.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/doctest.cpp

test/CMakeFiles/doctest-main.dir/doctest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/doctest-main.dir/doctest.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/doctest.cpp > CMakeFiles/doctest-main.dir/doctest.cpp.i

test/CMakeFiles/doctest-main.dir/doctest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/doctest-main.dir/doctest.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test/doctest.cpp -o CMakeFiles/doctest-main.dir/doctest.cpp.s

doctest-main: test/CMakeFiles/doctest-main.dir/doctest.cpp.o
doctest-main: test/CMakeFiles/doctest-main.dir/build.make

.PHONY : doctest-main

# Rule to build all files generated by this target.
test/CMakeFiles/doctest-main.dir/build: doctest-main

.PHONY : test/CMakeFiles/doctest-main.dir/build

test/CMakeFiles/doctest-main.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build/test && $(CMAKE_COMMAND) -P CMakeFiles/doctest-main.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/doctest-main.dir/clean

test/CMakeFiles/doctest-main.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/e0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template /mnt/c/sfu-cmpt/cmpt-373/e0/se-background-template/test /mnt/c/sfu-cmpt/cmpt-373/e0/build /mnt/c/sfu-cmpt/cmpt-373/e0/build/test /mnt/c/sfu-cmpt/cmpt-373/e0/build/test/CMakeFiles/doctest-main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/doctest-main.dir/depend

