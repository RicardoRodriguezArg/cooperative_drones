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
include utils_generics/CMakeFiles/utils_generics.dir/depend.make

# Include the progress variables for this target.
include utils_generics/CMakeFiles/utils_generics.dir/progress.make

# Include the compile flags for this target's objects.
include utils_generics/CMakeFiles/utils_generics.dir/flags.make

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o: utils_generics/CMakeFiles/utils_generics.dir/flags.make
utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o: /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/utils_generics/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utils_generics.dir/main.cpp.o -c /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/utils_generics/main.cpp

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils_generics.dir/main.cpp.i"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/utils_generics/main.cpp > CMakeFiles/utils_generics.dir/main.cpp.i

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils_generics.dir/main.cpp.s"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/utils_generics/main.cpp -o CMakeFiles/utils_generics.dir/main.cpp.s

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.requires:
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.requires

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.provides: utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.requires
	$(MAKE) -f utils_generics/CMakeFiles/utils_generics.dir/build.make utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.provides.build
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.provides

utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.provides.build: utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o

# Object files for target utils_generics
utils_generics_OBJECTS = \
"CMakeFiles/utils_generics.dir/main.cpp.o"

# External object files for target utils_generics
utils_generics_EXTERNAL_OBJECTS =

utils_generics/utils_generics: utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o
utils_generics/utils_generics: utils_generics/CMakeFiles/utils_generics.dir/build.make
utils_generics/utils_generics: utils_generics/CMakeFiles/utils_generics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable utils_generics"
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils_generics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils_generics/CMakeFiles/utils_generics.dir/build: utils_generics/utils_generics
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/build

utils_generics/CMakeFiles/utils_generics.dir/requires: utils_generics/CMakeFiles/utils_generics.dir/main.cpp.o.requires
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/requires

utils_generics/CMakeFiles/utils_generics.dir/clean:
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics && $(CMAKE_COMMAND) -P CMakeFiles/utils_generics.dir/cmake_clean.cmake
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/clean

utils_generics/CMakeFiles/utils_generics.dir/depend:
	cd /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs /home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/utils_generics /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics /home/ricardo/Desktop/debugger/cooperative_drones/trunks/install/autonomous_generic_drone/bin/commonsLibs/utils_generics/CMakeFiles/utils_generics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils_generics/CMakeFiles/utils_generics.dir/depend

