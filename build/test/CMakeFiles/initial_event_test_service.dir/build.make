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
include test/CMakeFiles/initial_event_test_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/initial_event_test_service.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/initial_event_test_service.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/initial_event_test_service.dir/flags.make

test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o: test/CMakeFiles/initial_event_test_service.dir/flags.make
test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o: ../test/initial_event_tests/initial_event_test_service.cpp
test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o: test/CMakeFiles/initial_event_test_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nlh/vsomeip-3.1.20.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o"
	cd /home/nlh/vsomeip-3.1.20.3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o -MF CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o.d -o CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o -c /home/nlh/vsomeip-3.1.20.3/test/initial_event_tests/initial_event_test_service.cpp

test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.i"
	cd /home/nlh/vsomeip-3.1.20.3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nlh/vsomeip-3.1.20.3/test/initial_event_tests/initial_event_test_service.cpp > CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.i

test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.s"
	cd /home/nlh/vsomeip-3.1.20.3/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nlh/vsomeip-3.1.20.3/test/initial_event_tests/initial_event_test_service.cpp -o CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.s

# Object files for target initial_event_test_service
initial_event_test_service_OBJECTS = \
"CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o"

# External object files for target initial_event_test_service
initial_event_test_service_EXTERNAL_OBJECTS =

test/initial_event_test_service: test/CMakeFiles/initial_event_test_service.dir/initial_event_tests/initial_event_test_service.cpp.o
test/initial_event_test_service: test/CMakeFiles/initial_event_test_service.dir/build.make
test/initial_event_test_service: libvsomeip3.so.3.1.20
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_system.so
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_thread.so
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
test/initial_event_test_service: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
test/initial_event_test_service: lib/libgtest.a
test/initial_event_test_service: test/CMakeFiles/initial_event_test_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nlh/vsomeip-3.1.20.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable initial_event_test_service"
	cd /home/nlh/vsomeip-3.1.20.3/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/initial_event_test_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/initial_event_test_service.dir/build: test/initial_event_test_service
.PHONY : test/CMakeFiles/initial_event_test_service.dir/build

test/CMakeFiles/initial_event_test_service.dir/clean:
	cd /home/nlh/vsomeip-3.1.20.3/build/test && $(CMAKE_COMMAND) -P CMakeFiles/initial_event_test_service.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/initial_event_test_service.dir/clean

test/CMakeFiles/initial_event_test_service.dir/depend:
	cd /home/nlh/vsomeip-3.1.20.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nlh/vsomeip-3.1.20.3 /home/nlh/vsomeip-3.1.20.3/test /home/nlh/vsomeip-3.1.20.3/build /home/nlh/vsomeip-3.1.20.3/build/test /home/nlh/vsomeip-3.1.20.3/build/test/CMakeFiles/initial_event_test_service.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/initial_event_test_service.dir/depend

