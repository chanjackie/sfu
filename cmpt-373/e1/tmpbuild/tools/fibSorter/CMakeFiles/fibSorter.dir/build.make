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
CMAKE_SOURCE_DIR = /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild

# Include any dependencies generated for this target.
include tools/fibSorter/CMakeFiles/fibSorter.dir/depend.make

# Include the progress variables for this target.
include tools/fibSorter/CMakeFiles/fibSorter.dir/progress.make

# Include the compile flags for this target's objects.
include tools/fibSorter/CMakeFiles/fibSorter.dir/flags.make

tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.o: tools/fibSorter/CMakeFiles/fibSorter.dir/flags.make
tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise/tools/fibSorter/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fibSorter.dir/main.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise/tools/fibSorter/main.cpp

tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fibSorter.dir/main.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise/tools/fibSorter/main.cpp > CMakeFiles/fibSorter.dir/main.cpp.i

tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fibSorter.dir/main.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise/tools/fibSorter/main.cpp -o CMakeFiles/fibSorter.dir/main.cpp.s

# Object files for target fibSorter
fibSorter_OBJECTS = \
"CMakeFiles/fibSorter.dir/main.cpp.o"

# External object files for target fibSorter
fibSorter_EXTERNAL_OBJECTS =

bin/fibSorter: tools/fibSorter/CMakeFiles/fibSorter.dir/main.cpp.o
bin/fibSorter: tools/fibSorter/CMakeFiles/fibSorter.dir/build.make
bin/fibSorter: lib/libsortIntegers.a
bin/fibSorter: tools/fibSorter/CMakeFiles/fibSorter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/fibSorter"
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fibSorter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/fibSorter/CMakeFiles/fibSorter.dir/build: bin/fibSorter

.PHONY : tools/fibSorter/CMakeFiles/fibSorter.dir/build

tools/fibSorter/CMakeFiles/fibSorter.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter && $(CMAKE_COMMAND) -P CMakeFiles/fibSorter.dir/cmake_clean.cmake
.PHONY : tools/fibSorter/CMakeFiles/fibSorter.dir/clean

tools/fibSorter/CMakeFiles/fibSorter.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise /mnt/c/sfu-cmpt/cmpt-373/e1/cmakeExercise/tools/fibSorter /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter /mnt/c/sfu-cmpt/cmpt-373/e1/tmpbuild/tools/fibSorter/CMakeFiles/fibSorter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/fibSorter/CMakeFiles/fibSorter.dir/depend

