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
include src/CMakeFiles/libEXC.a.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/libEXC.a.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/libEXC.a.dir/flags.make

src/CMakeFiles/libEXC.a.dir/glist.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/glist.c.o: ../src/glist.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/glist.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/glist.c.o   -c /develop/dev-notes/src/glist.c

src/CMakeFiles/libEXC.a.dir/glist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/glist.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/glist.c > CMakeFiles/libEXC.a.dir/glist.c.i

src/CMakeFiles/libEXC.a.dir/glist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/glist.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/glist.c -o CMakeFiles/libEXC.a.dir/glist.c.s

src/CMakeFiles/libEXC.a.dir/glist.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/glist.c.o.requires

src/CMakeFiles/libEXC.a.dir/glist.c.o.provides: src/CMakeFiles/libEXC.a.dir/glist.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/glist.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/glist.c.o.provides

src/CMakeFiles/libEXC.a.dir/glist.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/glist.c.o

src/CMakeFiles/libEXC.a.dir/memwatch.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/memwatch.c.o: ../src/memwatch.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/memwatch.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/memwatch.c.o   -c /develop/dev-notes/src/memwatch.c

src/CMakeFiles/libEXC.a.dir/memwatch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/memwatch.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/memwatch.c > CMakeFiles/libEXC.a.dir/memwatch.c.i

src/CMakeFiles/libEXC.a.dir/memwatch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/memwatch.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/memwatch.c -o CMakeFiles/libEXC.a.dir/memwatch.c.s

src/CMakeFiles/libEXC.a.dir/memwatch.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/memwatch.c.o.requires

src/CMakeFiles/libEXC.a.dir/memwatch.c.o.provides: src/CMakeFiles/libEXC.a.dir/memwatch.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/memwatch.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/memwatch.c.o.provides

src/CMakeFiles/libEXC.a.dir/memwatch.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/memwatch.c.o

src/CMakeFiles/libEXC.a.dir/excmd5.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/excmd5.c.o: ../src/excmd5.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/excmd5.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/excmd5.c.o   -c /develop/dev-notes/src/excmd5.c

src/CMakeFiles/libEXC.a.dir/excmd5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/excmd5.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/excmd5.c > CMakeFiles/libEXC.a.dir/excmd5.c.i

src/CMakeFiles/libEXC.a.dir/excmd5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/excmd5.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/excmd5.c -o CMakeFiles/libEXC.a.dir/excmd5.c.s

src/CMakeFiles/libEXC.a.dir/excmd5.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/excmd5.c.o.requires

src/CMakeFiles/libEXC.a.dir/excmd5.c.o.provides: src/CMakeFiles/libEXC.a.dir/excmd5.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/excmd5.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/excmd5.c.o.provides

src/CMakeFiles/libEXC.a.dir/excmd5.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/excmd5.c.o

src/CMakeFiles/libEXC.a.dir/lpconfig.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/lpconfig.c.o: ../src/lpconfig.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/lpconfig.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/lpconfig.c.o   -c /develop/dev-notes/src/lpconfig.c

src/CMakeFiles/libEXC.a.dir/lpconfig.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/lpconfig.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/lpconfig.c > CMakeFiles/libEXC.a.dir/lpconfig.c.i

src/CMakeFiles/libEXC.a.dir/lpconfig.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/lpconfig.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/lpconfig.c -o CMakeFiles/libEXC.a.dir/lpconfig.c.s

src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.requires

src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.provides: src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.provides

src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/lpconfig.c.o

src/CMakeFiles/libEXC.a.dir/cJSON.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/cJSON.c.o: ../src/cJSON.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/cJSON.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/cJSON.c.o   -c /develop/dev-notes/src/cJSON.c

src/CMakeFiles/libEXC.a.dir/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/cJSON.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/cJSON.c > CMakeFiles/libEXC.a.dir/cJSON.c.i

src/CMakeFiles/libEXC.a.dir/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/cJSON.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/cJSON.c -o CMakeFiles/libEXC.a.dir/cJSON.c.s

src/CMakeFiles/libEXC.a.dir/cJSON.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/cJSON.c.o.requires

src/CMakeFiles/libEXC.a.dir/cJSON.c.o.provides: src/CMakeFiles/libEXC.a.dir/cJSON.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/cJSON.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/cJSON.c.o.provides

src/CMakeFiles/libEXC.a.dir/cJSON.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/cJSON.c.o

src/CMakeFiles/libEXC.a.dir/excport.c.o: src/CMakeFiles/libEXC.a.dir/flags.make
src/CMakeFiles/libEXC.a.dir/excport.c.o: ../src/excport.c
	$(CMAKE_COMMAND) -E cmake_progress_report /develop/dev-notes/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/libEXC.a.dir/excport.c.o"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libEXC.a.dir/excport.c.o   -c /develop/dev-notes/src/excport.c

src/CMakeFiles/libEXC.a.dir/excport.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libEXC.a.dir/excport.c.i"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -E /develop/dev-notes/src/excport.c > CMakeFiles/libEXC.a.dir/excport.c.i

src/CMakeFiles/libEXC.a.dir/excport.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libEXC.a.dir/excport.c.s"
	cd /develop/dev-notes/build/src && gcc  $(C_DEFINES) $(C_FLAGS) -S /develop/dev-notes/src/excport.c -o CMakeFiles/libEXC.a.dir/excport.c.s

src/CMakeFiles/libEXC.a.dir/excport.c.o.requires:
.PHONY : src/CMakeFiles/libEXC.a.dir/excport.c.o.requires

src/CMakeFiles/libEXC.a.dir/excport.c.o.provides: src/CMakeFiles/libEXC.a.dir/excport.c.o.requires
	$(MAKE) -f src/CMakeFiles/libEXC.a.dir/build.make src/CMakeFiles/libEXC.a.dir/excport.c.o.provides.build
.PHONY : src/CMakeFiles/libEXC.a.dir/excport.c.o.provides

src/CMakeFiles/libEXC.a.dir/excport.c.o.provides.build: src/CMakeFiles/libEXC.a.dir/excport.c.o

# Object files for target libEXC.a
libEXC_a_OBJECTS = \
"CMakeFiles/libEXC.a.dir/glist.c.o" \
"CMakeFiles/libEXC.a.dir/memwatch.c.o" \
"CMakeFiles/libEXC.a.dir/excmd5.c.o" \
"CMakeFiles/libEXC.a.dir/lpconfig.c.o" \
"CMakeFiles/libEXC.a.dir/cJSON.c.o" \
"CMakeFiles/libEXC.a.dir/excport.c.o"

# External object files for target libEXC.a
libEXC_a_EXTERNAL_OBJECTS =

libEXC.a: src/CMakeFiles/libEXC.a.dir/glist.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/memwatch.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/excmd5.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/lpconfig.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/cJSON.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/excport.c.o
libEXC.a: src/CMakeFiles/libEXC.a.dir/build.make
libEXC.a: src/CMakeFiles/libEXC.a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library ../libEXC.a"
	cd /develop/dev-notes/build/src && $(CMAKE_COMMAND) -P CMakeFiles/libEXC.a.dir/cmake_clean_target.cmake
	cd /develop/dev-notes/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libEXC.a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/libEXC.a.dir/build: libEXC.a
.PHONY : src/CMakeFiles/libEXC.a.dir/build

src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/glist.c.o.requires
src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/memwatch.c.o.requires
src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/excmd5.c.o.requires
src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/lpconfig.c.o.requires
src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/cJSON.c.o.requires
src/CMakeFiles/libEXC.a.dir/requires: src/CMakeFiles/libEXC.a.dir/excport.c.o.requires
.PHONY : src/CMakeFiles/libEXC.a.dir/requires

src/CMakeFiles/libEXC.a.dir/clean:
	cd /develop/dev-notes/build/src && $(CMAKE_COMMAND) -P CMakeFiles/libEXC.a.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/libEXC.a.dir/clean

src/CMakeFiles/libEXC.a.dir/depend:
	cd /develop/dev-notes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /develop/dev-notes /develop/dev-notes/src /develop/dev-notes/build /develop/dev-notes/build/src /develop/dev-notes/build/src/CMakeFiles/libEXC.a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/libEXC.a.dir/depend

