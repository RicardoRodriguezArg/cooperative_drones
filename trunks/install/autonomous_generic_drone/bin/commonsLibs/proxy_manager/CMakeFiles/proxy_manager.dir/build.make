# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs

# Include any dependencies generated for this target.
include proxy_manager/CMakeFiles/proxy_manager.dir/depend.make

# Include the progress variables for this target.
include proxy_manager/CMakeFiles/proxy_manager.dir/progress.make

# Include the compile flags for this target's objects.
include proxy_manager/CMakeFiles/proxy_manager.dir/flags.make

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o: proxy_manager/CMakeFiles/proxy_manager.dir/flags.make
proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o: /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/proxy_manager/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/proxy_manager.dir/main.cpp.o -c /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/proxy_manager/main.cpp

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proxy_manager.dir/main.cpp.i"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/proxy_manager/main.cpp > CMakeFiles/proxy_manager.dir/main.cpp.i

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proxy_manager.dir/main.cpp.s"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/proxy_manager/main.cpp -o CMakeFiles/proxy_manager.dir/main.cpp.s

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.requires:
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.requires

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.provides: proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.requires
	$(MAKE) -f proxy_manager/CMakeFiles/proxy_manager.dir/build.make proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.provides.build
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.provides

proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.provides.build: proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o

# Object files for target proxy_manager
proxy_manager_OBJECTS = \
"CMakeFiles/proxy_manager.dir/main.cpp.o"

# External object files for target proxy_manager
proxy_manager_EXTERNAL_OBJECTS =

proxy_manager/proxy_manager: proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o
proxy_manager/proxy_manager: proxy_manager/CMakeFiles/proxy_manager.dir/build.make
proxy_manager/proxy_manager: proxy_manager/CMakeFiles/proxy_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable proxy_manager"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proxy_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proxy_manager/CMakeFiles/proxy_manager.dir/build: proxy_manager/proxy_manager
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/build

proxy_manager/CMakeFiles/proxy_manager.dir/requires: proxy_manager/CMakeFiles/proxy_manager.dir/main.cpp.o.requires
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/requires

proxy_manager/CMakeFiles/proxy_manager.dir/clean:
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager && $(CMAKE_COMMAND) -P CMakeFiles/proxy_manager.dir/cmake_clean.cmake
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/clean

proxy_manager/CMakeFiles/proxy_manager.dir/depend:
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/proxy_manager /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/proxy_manager/CMakeFiles/proxy_manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proxy_manager/CMakeFiles/proxy_manager.dir/depend
