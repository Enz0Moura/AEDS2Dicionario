# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/clion/308/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/308/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pedro/Desktop/AEDS2Dicionario

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DicinarioAeds2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DicinarioAeds2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DicinarioAeds2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DicinarioAeds2.dir/flags.make

CMakeFiles/DicinarioAeds2.dir/main.c.o: CMakeFiles/DicinarioAeds2.dir/flags.make
CMakeFiles/DicinarioAeds2.dir/main.c.o: /home/pedro/Desktop/AEDS2Dicionario/main.c
CMakeFiles/DicinarioAeds2.dir/main.c.o: CMakeFiles/DicinarioAeds2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DicinarioAeds2.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DicinarioAeds2.dir/main.c.o -MF CMakeFiles/DicinarioAeds2.dir/main.c.o.d -o CMakeFiles/DicinarioAeds2.dir/main.c.o -c /home/pedro/Desktop/AEDS2Dicionario/main.c

CMakeFiles/DicinarioAeds2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DicinarioAeds2.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pedro/Desktop/AEDS2Dicionario/main.c > CMakeFiles/DicinarioAeds2.dir/main.c.i

CMakeFiles/DicinarioAeds2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DicinarioAeds2.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pedro/Desktop/AEDS2Dicionario/main.c -o CMakeFiles/DicinarioAeds2.dir/main.c.s

# Object files for target DicinarioAeds2
DicinarioAeds2_OBJECTS = \
"CMakeFiles/DicinarioAeds2.dir/main.c.o"

# External object files for target DicinarioAeds2
DicinarioAeds2_EXTERNAL_OBJECTS =

DicinarioAeds2: CMakeFiles/DicinarioAeds2.dir/main.c.o
DicinarioAeds2: CMakeFiles/DicinarioAeds2.dir/build.make
DicinarioAeds2: CMakeFiles/DicinarioAeds2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable DicinarioAeds2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DicinarioAeds2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DicinarioAeds2.dir/build: DicinarioAeds2
.PHONY : CMakeFiles/DicinarioAeds2.dir/build

CMakeFiles/DicinarioAeds2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DicinarioAeds2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DicinarioAeds2.dir/clean

CMakeFiles/DicinarioAeds2.dir/depend:
	cd /home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pedro/Desktop/AEDS2Dicionario /home/pedro/Desktop/AEDS2Dicionario /home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug /home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug /home/pedro/Desktop/AEDS2Dicionario/cmake-build-debug/CMakeFiles/DicinarioAeds2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DicinarioAeds2.dir/depend

