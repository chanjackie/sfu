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
include web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/depend.make

# Include the progress variables for this target.
include web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/progress.make

# Include the compile flags for this target's objects.
include web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/flags.make

web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o: web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/flags.make
web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o: /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/chatwindow/src/ChatWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o -c /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/chatwindow/src/ChatWindow.cpp

web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.i"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/chatwindow/src/ChatWindow.cpp > CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.i

web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.s"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/chatwindow/src/ChatWindow.cpp -o CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.s

# Object files for target chatwindow
chatwindow_OBJECTS = \
"CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o"

# External object files for target chatwindow
chatwindow_EXTERNAL_OBJECTS =

lib/libchatwindow.a: web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/src/ChatWindow.cpp.o
lib/libchatwindow.a: web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/build.make
lib/libchatwindow.a: web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/sfu-cmpt/cmpt-373/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libchatwindow.a"
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && $(CMAKE_COMMAND) -P CMakeFiles/chatwindow.dir/cmake_clean_target.cmake
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chatwindow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/build: lib/libchatwindow.a

.PHONY : web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/build

web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/clean:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow && $(CMAKE_COMMAND) -P CMakeFiles/chatwindow.dir/cmake_clean.cmake
.PHONY : web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/clean

web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/depend:
	cd /mnt/c/sfu-cmpt/cmpt-373/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming /mnt/c/sfu-cmpt/cmpt-373/project/social-gaming/web-socket-networking-master/lib/chatwindow /mnt/c/sfu-cmpt/cmpt-373/project/build /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow /mnt/c/sfu-cmpt/cmpt-373/project/build/web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : web-socket-networking-master/lib/chatwindow/CMakeFiles/chatwindow.dir/depend

