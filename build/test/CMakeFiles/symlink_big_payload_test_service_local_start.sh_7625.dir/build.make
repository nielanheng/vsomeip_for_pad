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

# Utility rule file for symlink_big_payload_test_service_local_start.sh_7625.

# Include any custom commands dependencies for this target.
include test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/progress.make

test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625: test/big_payload_test_service_local_start.sh

test/big_payload_test_service_local_start.sh: ../test/big_payload_tests/big_payload_test_service_local_start.sh
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nlh/vsomeip-3.1.20.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying \"/home/nlh/vsomeip-3.1.20.3/test/big_payload_tests/big_payload_test_service_local_start.sh\" into build directory"
	cd /home/nlh/vsomeip-3.1.20.3/build/test && /usr/bin/cmake -E copy /home/nlh/vsomeip-3.1.20.3/test/big_payload_tests/big_payload_test_service_local_start.sh /home/nlh/vsomeip-3.1.20.3/build/test/big_payload_test_service_local_start.sh

symlink_big_payload_test_service_local_start.sh_7625: test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625
symlink_big_payload_test_service_local_start.sh_7625: test/big_payload_test_service_local_start.sh
symlink_big_payload_test_service_local_start.sh_7625: test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/build.make
.PHONY : symlink_big_payload_test_service_local_start.sh_7625

# Rule to build all files generated by this target.
test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/build: symlink_big_payload_test_service_local_start.sh_7625
.PHONY : test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/build

test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/clean:
	cd /home/nlh/vsomeip-3.1.20.3/build/test && $(CMAKE_COMMAND) -P CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/clean

test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/depend:
	cd /home/nlh/vsomeip-3.1.20.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nlh/vsomeip-3.1.20.3 /home/nlh/vsomeip-3.1.20.3/test /home/nlh/vsomeip-3.1.20.3/build /home/nlh/vsomeip-3.1.20.3/build/test /home/nlh/vsomeip-3.1.20.3/build/test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/symlink_big_payload_test_service_local_start.sh_7625.dir/depend

