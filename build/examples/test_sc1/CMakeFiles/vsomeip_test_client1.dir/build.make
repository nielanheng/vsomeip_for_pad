# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nlh/vsomeip-3.1.20.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nlh/vsomeip-3.1.20.3/build

# Include any dependencies generated for this target.
include examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/progress.make

# Include the compile flags for this target's objects.
include examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/flags.make

examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o: examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/flags.make
examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o: ../examples/test_sc1/test_client_main.cpp
examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o: examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nlh/vsomeip-3.1.20.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o"
	cd /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o -MF CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o.d -o CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o -c /home/nlh/vsomeip-3.1.20.3/examples/test_sc1/test_client_main.cpp

examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.i"
	cd /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nlh/vsomeip-3.1.20.3/examples/test_sc1/test_client_main.cpp > CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.i

examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.s"
	cd /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nlh/vsomeip-3.1.20.3/examples/test_sc1/test_client_main.cpp -o CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.s

# Object files for target vsomeip_test_client1
vsomeip_test_client1_OBJECTS = \
"CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o"

# External object files for target vsomeip_test_client1
vsomeip_test_client1_EXTERNAL_OBJECTS =

examples/test_sc1/vsomeip_test_client1: examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/test_client_main.cpp.o
examples/test_sc1/vsomeip_test_client1: examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/build.make
examples/test_sc1/vsomeip_test_client1: libvsomeip3.so.3.1.20
examples/test_sc1/vsomeip_test_client1: examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nlh/vsomeip-3.1.20.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vsomeip_test_client1"
	cd /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vsomeip_test_client1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/build: examples/test_sc1/vsomeip_test_client1
.PHONY : examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/build

examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/clean:
	cd /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 && $(CMAKE_COMMAND) -P CMakeFiles/vsomeip_test_client1.dir/cmake_clean.cmake
.PHONY : examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/clean

examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/depend:
	cd /home/nlh/vsomeip-3.1.20.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nlh/vsomeip-3.1.20.3 /home/nlh/vsomeip-3.1.20.3/examples/test_sc1 /home/nlh/vsomeip-3.1.20.3/build /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1 /home/nlh/vsomeip-3.1.20.3/build/examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/test_sc1/CMakeFiles/vsomeip_test_client1.dir/depend

