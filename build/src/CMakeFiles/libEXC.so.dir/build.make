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
include src/CMakeFiles/libEXC.so.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/libEXC.so.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/libEXC.so.dir/flags.make

src/CMakeFiles/libEXC.so.dir/memwatch.c.o: src/CMakeFiles/libEXC.so.dir/flags.make
src/CMakeFiles/libEXC.so.dir/memwatch.c.o: ../src/memwatch.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.so.dir/memwatch.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.so.dir/memwatch.c.o   -c /develop/dev-notes/src/memwatch.c

src/CMakeFiles/libEXC.so.dir/memwatch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.so.dir/memwatch.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/memwatch.c > CMakeFiles/libEXC.so.dir/memwatch.c.i

src/CMakeFiles/libEXC.so.dir/memwatch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.so.dir/memwatch.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/memwatch.c -o CMakeFiles/libEXC.so.dir/memwatch.c.s

src/CMakeFiles/libEXC.so.dir/memwatch.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.so.dir/memwatch.c.o.requires

src/CMakeFiles/libEXC.so.dir/memwatch.c.o.provides: src/CMakeFiles/libEXC.so.dir/memwatch.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.so.dir/build.make src/CMakeFiles/libEXC.so.dir/memwatch.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.so.dir/memwatch.c.o.provides

src/CMakeFiles/libEXC.so.dir/memwatch.c.o.provides.build: src/CMakeFiles/libEXC.so.dir/memwatch.c.o

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o: src/CMakeFiles/libEXC.so.dir/flags.make
src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o: ../src/xeHSC_port.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.so.dir/xeHSC_port.c.o   -c /develop/dev-notes/src/xeHSC_port.c

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.so.dir/xeHSC_port.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/xeHSC_port.c > CMakeFiles/libEXC.so.dir/xeHSC_port.c.i

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.so.dir/xeHSC_port.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/xeHSC_port.c -o CMakeFiles/libEXC.so.dir/xeHSC_port.c.s

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.requires

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.provides: src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.so.dir/build.make src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.provides

src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.provides.build: src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o

# Object files for target libEXC.so
libEXC_so_OBJECTS = \
"CMakeFiles/libEXC.so.dir/memwatch.c.o" \
"CMakeFiles/libEXC.so.dir/xeHSC_port.c.o"

# External object files for target libEXC.so
libEXC_so_EXTERNAL_OBJECTS =

libEXC.so: src/CMakeFiles/libEXC.so.dir/memwatch.c.o
libEXC.so: src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o
libEXC.so: src/CMakeFiles/libEXC.so.dir/build.make
libEXC.so: src/CMakeFiles/libEXC.so.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../libEXC.so"
	cd /develop/dev-notes/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libEXC.so.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/libEXC.so.dir/build: libEXC.so
.PHONY : src/CMakeFiles/libEXC.so.dir/build

src/CMakeFiles/libEXC.so.dir/requires: src/CMakeFiles/libEXC.so.dir/memwatch.c.o.requires
src/CMakeFiles/libEXC.so.dir/requires: src/CMakeFiles/libEXC.so.dir/xeHSC_port.c.o.requires
.PHONY : src/CMakeFiles/libEXC.so.dir/requires

src/CMakeFiles/libEXC.so.dir/clean:
	cd /develop/dev-notes/build/src && $(CMAKE_COMMAND) -P CMakeFiles/libEXC.so.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/libEXC.so.dir/clean

src/CMakeFiles/libEXC.so.dir/depend:
	cd /develop/dev-notes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /develop/dev-notes /develop/dev-notes/src /develop/dev-notes/build /develop/dev-notes/build/src /develop/dev-notes/build/src/CMakeFiles/libEXC.so.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/libEXC.so.dir/depend

