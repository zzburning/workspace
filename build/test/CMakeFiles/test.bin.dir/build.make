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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /develop/dev-notes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /develop/dev-notes/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test.bin.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test.bin.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test.bin.dir/flags.make

test/CMakeFiles/test.bin.dir/test.c.o: test/CMakeFiles/test.bin.dir/flags.make
test/CMakeFiles/test.bin.dir/test.c.o: ../test/test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/test.bin.dir/test.c.o"
	cd /develop/dev-notes/build/test && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test.bin.dir/test.c.o   -c /develop/dev-notes/test/test.c

test/CMakeFiles/test.bin.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.bin.dir/test.c.i"
	cd /develop/dev-notes/build/test && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/test/test.c > CMakeFiles/test.bin.dir/test.c.i

test/CMakeFiles/test.bin.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.bin.dir/test.c.s"
	cd /develop/dev-notes/build/test && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/test/test.c -o CMakeFiles/test.bin.dir/test.c.s

test/CMakeFiles/test.bin.dir/test.c.o.requires:
.PHONY : test/CMakeFiles/test.bin.dir/test.c.o.requires

test/CMakeFiles/test.bin.dir/test.c.o.provides: test/CMakeFiles/test.bin.dir/test.c.o.requires
	$(MAKE) -f test/CMakeFiles/test.bin.dir/build.make test/CMakeFiles/test.bin.dir/test.c.o.provides.build
.PHONY : test/CMakeFiles/test.bin.dir/test.c.o.provides

test/CMakeFiles/test.bin.dir/test.c.o.provides.build: test/CMakeFiles/test.bin.dir/test.c.o

# Object files for target test.bin
test_bin_OBJECTS = \
"CMakeFiles/test.bin.dir/test.c.o"

# External object files for target test.bin
test_bin_EXTERNAL_OBJECTS =

test.bin: test/CMakeFiles/test.bin.dir/test.c.o
test.bin: libEXC.so
test.bin: test/CMakeFiles/test.bin.dir/build.make
test.bin: test/CMakeFiles/test.bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../test.bin"
	cd /develop/dev-notes/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test.bin.dir/build: test.bin
.PHONY : test/CMakeFiles/test.bin.dir/build

test/CMakeFiles/test.bin.dir/requires: test/CMakeFiles/test.bin.dir/test.c.o.requires
.PHONY : test/CMakeFiles/test.bin.dir/requires

test/CMakeFiles/test.bin.dir/clean:
	cd /develop/dev-notes/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test.bin.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test.bin.dir/clean

test/CMakeFiles/test.bin.dir/depend:
	cd /develop/dev-notes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /develop/dev-notes /develop/dev-notes/test /develop/dev-notes/build /develop/dev-notes/build/test /develop/dev-notes/build/test/CMakeFiles/test.bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test.bin.dir/depend

