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
CMAKE_SOURCE_DIR = /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/sfu-cmpt/cmpt-373/e3/build

# Include any dependencies generated for this target.
include test/CMakeFiles/runAllTests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/runAllTests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/runAllTests.dir/flags.make

test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o: test/CMakeFiles/runAllTests.dir/flags.make
test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/ParallelogramTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/ParallelogramTests.cpp

test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/ParallelogramTests.cpp > CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.i

test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/ParallelogramTests.cpp -o CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.s

test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o: test/CMakeFiles/runAllTests.dir/flags.make
test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/MatthewsTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/MatthewsTests.cpp

test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllTests.dir/MatthewsTests.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/MatthewsTests.cpp > CMakeFiles/runAllTests.dir/MatthewsTests.cpp.i

test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllTests.dir/MatthewsTests.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/MatthewsTests.cpp -o CMakeFiles/runAllTests.dir/MatthewsTests.cpp.s

test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.o: test/CMakeFiles/runAllTests.dir/flags.make
test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/AwardsTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllTests.dir/AwardsTests.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/AwardsTests.cpp

test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllTests.dir/AwardsTests.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/AwardsTests.cpp > CMakeFiles/runAllTests.dir/AwardsTests.cpp.i

test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllTests.dir/AwardsTests.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/AwardsTests.cpp -o CMakeFiles/runAllTests.dir/AwardsTests.cpp.s

# Object files for target runAllTests
runAllTests_OBJECTS = \
"CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o" \
"CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o" \
"CMakeFiles/runAllTests.dir/AwardsTests.cpp.o"

# External object files for target runAllTests
runAllTests_EXTERNAL_OBJECTS =

test/runAllTests: test/CMakeFiles/runAllTests.dir/ParallelogramTests.cpp.o
test/runAllTests: test/CMakeFiles/runAllTests.dir/MatthewsTests.cpp.o
test/runAllTests: test/CMakeFiles/runAllTests.dir/AwardsTests.cpp.o
test/runAllTests: test/CMakeFiles/runAllTests.dir/build.make
test/runAllTests: lib/libgmock.a
test/runAllTests: lib/libgtest.a
test/runAllTests: lib/libgtest_main.a
test/runAllTests: lib/simple/libsimple.a
test/runAllTests: lib/libgtest.a
test/runAllTests: test/CMakeFiles/runAllTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/e3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable runAllTests"
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runAllTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/runAllTests.dir/build: test/runAllTests

.PHONY : test/CMakeFiles/runAllTests.dir/build

test/CMakeFiles/runAllTests.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build/test && $(CMAKE_COMMAND) -P CMakeFiles/runAllTests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/runAllTests.dir/clean

test/CMakeFiles/runAllTests.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/e3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test /mnt/c/sfu-cmpt/cmpt-373/e3/build /mnt/c/sfu-cmpt/cmpt-373/e3/build/test /mnt/c/sfu-cmpt/cmpt-373/e3/build/test/CMakeFiles/runAllTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/runAllTests.dir/depend
