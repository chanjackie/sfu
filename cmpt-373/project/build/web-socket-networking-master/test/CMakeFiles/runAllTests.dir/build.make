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
include web-socket-networking-master/test/CMakeFiles/runAllTests.dir/depend.make

# Include the progress variables for this target.
include web-socket-networking-master/test/CMakeFiles/runAllTests.dir/progress.make

# Include the compile flags for this target's objects.
include web-socket-networking-master/test/CMakeFiles/runAllTests.dir/flags.make

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.o: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/flags.make
web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConfigTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllTests.dir/ConfigTests.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConfigTests.cpp

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllTests.dir/ConfigTests.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConfigTests.cpp > CMakeFiles/runAllTests.dir/ConfigTests.cpp.i

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllTests.dir/ConfigTests.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConfigTests.cpp -o CMakeFiles/runAllTests.dir/ConfigTests.cpp.s

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/flags.make
web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConstantsParserTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConstantsParserTests.cpp

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConstantsParserTests.cpp > CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.i

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test/ConstantsParserTests.cpp -o CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.s

# Object files for target runAllTests
runAllTests_OBJECTS = \
"CMakeFiles/runAllTests.dir/ConfigTests.cpp.o" \
"CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o"

# External object files for target runAllTests
runAllTests_EXTERNAL_OBJECTS =

bin/runAllTests: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConfigTests.cpp.o
bin/runAllTests: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/ConstantsParserTests.cpp.o
bin/runAllTests: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/build.make
bin/runAllTests: lib/libgmock.a
bin/runAllTests: lib/libgtest.a
bin/runAllTests: lib/libgtest_main.a
bin/runAllTests: lib/libjson_interpreter.a
bin/runAllTests: lib/libgame.a
bin/runAllTests: lib/libgtest.a
bin/runAllTests: lib/libjson_interpreter.a
bin/runAllTests: lib/libgame.a
bin/runAllTests: /usr/lib/libboost_system.so
bin/runAllTests: web-socket-networking-master/test/CMakeFiles/runAllTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/runAllTests"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runAllTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
web-socket-networking-master/test/CMakeFiles/runAllTests.dir/build: bin/runAllTests

.PHONY : web-socket-networking-master/test/CMakeFiles/runAllTests.dir/build

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test && $(CMAKE_COMMAND) -P CMakeFiles/runAllTests.dir/cmake_clean.cmake
.PHONY : web-socket-networking-master/test/CMakeFiles/runAllTests.dir/clean

web-socket-networking-master/test/CMakeFiles/runAllTests.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/test /mnt/c/sfu-cmpt/cmpt-373/project/build /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/test/CMakeFiles/runAllTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : web-socket-networking-master/test/CMakeFiles/runAllTests.dir/depend
