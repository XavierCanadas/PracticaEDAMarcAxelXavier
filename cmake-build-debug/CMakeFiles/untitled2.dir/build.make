# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/untitled2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled2.dir/flags.make

CMakeFiles/untitled2.dir/main.c.o: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/main.c.o: /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/main.c
CMakeFiles/untitled2.dir/main.c.o: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled2.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/main.c.o -MF CMakeFiles/untitled2.dir/main.c.o.d -o CMakeFiles/untitled2.dir/main.c.o -c /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/main.c

CMakeFiles/untitled2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled2.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/main.c > CMakeFiles/untitled2.dir/main.c.i

CMakeFiles/untitled2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled2.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/main.c -o CMakeFiles/untitled2.dir/main.c.s

CMakeFiles/untitled2.dir/menu.c.o: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/menu.c.o: /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/menu.c
CMakeFiles/untitled2.dir/menu.c.o: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/untitled2.dir/menu.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/menu.c.o -MF CMakeFiles/untitled2.dir/menu.c.o.d -o CMakeFiles/untitled2.dir/menu.c.o -c /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/menu.c

CMakeFiles/untitled2.dir/menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled2.dir/menu.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/menu.c > CMakeFiles/untitled2.dir/menu.c.i

CMakeFiles/untitled2.dir/menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled2.dir/menu.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/menu.c -o CMakeFiles/untitled2.dir/menu.c.s

# Object files for target untitled2
untitled2_OBJECTS = \
"CMakeFiles/untitled2.dir/main.c.o" \
"CMakeFiles/untitled2.dir/menu.c.o"

# External object files for target untitled2
untitled2_EXTERNAL_OBJECTS =

untitled2: CMakeFiles/untitled2.dir/main.c.o
untitled2: CMakeFiles/untitled2.dir/menu.c.o
untitled2: CMakeFiles/untitled2.dir/build.make
untitled2: CMakeFiles/untitled2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable untitled2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled2.dir/build: untitled2
.PHONY : CMakeFiles/untitled2.dir/build

CMakeFiles/untitled2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled2.dir/clean

CMakeFiles/untitled2.dir/depend:
	cd /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug /Users/xavicanadas/CLionProjects/PracticaEDAMarcAxelXavier/cmake-build-debug/CMakeFiles/untitled2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/untitled2.dir/depend

