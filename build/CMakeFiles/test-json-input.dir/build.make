# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.6/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sbacha/siphon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sbacha/siphon/build

# Include any dependencies generated for this target.
include CMakeFiles/test-json-input.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test-json-input.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-json-input.dir/flags.make

CMakeFiles/test-json-input.dir/test/json-input.c.o: CMakeFiles/test-json-input.dir/flags.make
CMakeFiles/test-json-input.dir/test/json-input.c.o: ../test/json-input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sbacha/siphon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test-json-input.dir/test/json-input.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-json-input.dir/test/json-input.c.o -c /Users/sbacha/siphon/test/json-input.c

CMakeFiles/test-json-input.dir/test/json-input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-json-input.dir/test/json-input.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sbacha/siphon/test/json-input.c > CMakeFiles/test-json-input.dir/test/json-input.c.i

CMakeFiles/test-json-input.dir/test/json-input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-json-input.dir/test/json-input.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sbacha/siphon/test/json-input.c -o CMakeFiles/test-json-input.dir/test/json-input.c.s

# Object files for target test-json-input
test__json__input_OBJECTS = \
"CMakeFiles/test-json-input.dir/test/json-input.c.o"

# External object files for target test-json-input
test__json__input_EXTERNAL_OBJECTS =

test-json-input: CMakeFiles/test-json-input.dir/test/json-input.c.o
test-json-input: CMakeFiles/test-json-input.dir/build.make
test-json-input: libsiphon.a
test-json-input: CMakeFiles/test-json-input.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sbacha/siphon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test-json-input"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-json-input.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-json-input.dir/build: test-json-input

.PHONY : CMakeFiles/test-json-input.dir/build

CMakeFiles/test-json-input.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-json-input.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-json-input.dir/clean

CMakeFiles/test-json-input.dir/depend:
	cd /Users/sbacha/siphon/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sbacha/siphon /Users/sbacha/siphon /Users/sbacha/siphon/build /Users/sbacha/siphon/build /Users/sbacha/siphon/build/CMakeFiles/test-json-input.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-json-input.dir/depend

