# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build

# Include any dependencies generated for this target.
include CMakeFiles/service_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/service_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/service_example.dir/flags.make

CMakeFiles/service_example.dir/service_example.cpp.o: CMakeFiles/service_example.dir/flags.make
CMakeFiles/service_example.dir/service_example.cpp.o: ../service_example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/service_example.dir/service_example.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/service_example.dir/service_example.cpp.o -c /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/service_example.cpp

CMakeFiles/service_example.dir/service_example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/service_example.dir/service_example.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/service_example.cpp > CMakeFiles/service_example.dir/service_example.cpp.i

CMakeFiles/service_example.dir/service_example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/service_example.dir/service_example.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/service_example.cpp -o CMakeFiles/service_example.dir/service_example.cpp.s

CMakeFiles/service_example.dir/service_example.cpp.o.requires:

.PHONY : CMakeFiles/service_example.dir/service_example.cpp.o.requires

CMakeFiles/service_example.dir/service_example.cpp.o.provides: CMakeFiles/service_example.dir/service_example.cpp.o.requires
	$(MAKE) -f CMakeFiles/service_example.dir/build.make CMakeFiles/service_example.dir/service_example.cpp.o.provides.build
.PHONY : CMakeFiles/service_example.dir/service_example.cpp.o.provides

CMakeFiles/service_example.dir/service_example.cpp.o.provides.build: CMakeFiles/service_example.dir/service_example.cpp.o


# Object files for target service_example
service_example_OBJECTS = \
"CMakeFiles/service_example.dir/service_example.cpp.o"

# External object files for target service_example
service_example_EXTERNAL_OBJECTS =

service_example: CMakeFiles/service_example.dir/service_example.cpp.o
service_example: CMakeFiles/service_example.dir/build.make
service_example: /usr/local/lib/libvsomeip3.so.3.1.20
service_example: CMakeFiles/service_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable service_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/service_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/service_example.dir/build: service_example

.PHONY : CMakeFiles/service_example.dir/build

CMakeFiles/service_example.dir/requires: CMakeFiles/service_example.dir/service_example.cpp.o.requires

.PHONY : CMakeFiles/service_example.dir/requires

CMakeFiles/service_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/service_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/service_example.dir/clean

CMakeFiles/service_example.dir/depend:
	cd /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build /home/nlh/vsomeip-3.1.20.3/examples/test_vsomeip_nlh/build/CMakeFiles/service_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/service_example.dir/depend

