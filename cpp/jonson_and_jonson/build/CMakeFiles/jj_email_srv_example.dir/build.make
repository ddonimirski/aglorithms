# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /opt/cmake/cmake-3.18.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake/cmake-3.18.1-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dd/aglorithms/cpp/jonson_and_jonson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dd/aglorithms/cpp/jonson_and_jonson/build

# Include any dependencies generated for this target.
include CMakeFiles/jj_email_srv_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jj_email_srv_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jj_email_srv_example.dir/flags.make

CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o: CMakeFiles/jj_email_srv_example.dir/flags.make
CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o: ../example/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dd/aglorithms/cpp/jonson_and_jonson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;--extra-arg-before=--driver-mode=g++" --source=/home/dd/aglorithms/cpp/jonson_and_jonson/example/main.cpp -- /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o -c /home/dd/aglorithms/cpp/jonson_and_jonson/example/main.cpp

CMakeFiles/jj_email_srv_example.dir/example/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jj_email_srv_example.dir/example/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dd/aglorithms/cpp/jonson_and_jonson/example/main.cpp > CMakeFiles/jj_email_srv_example.dir/example/main.cpp.i

CMakeFiles/jj_email_srv_example.dir/example/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jj_email_srv_example.dir/example/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dd/aglorithms/cpp/jonson_and_jonson/example/main.cpp -o CMakeFiles/jj_email_srv_example.dir/example/main.cpp.s

# Object files for target jj_email_srv_example
jj_email_srv_example_OBJECTS = \
"CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o"

# External object files for target jj_email_srv_example
jj_email_srv_example_EXTERNAL_OBJECTS =

jj_email_srv_example: CMakeFiles/jj_email_srv_example.dir/example/main.cpp.o
jj_email_srv_example: CMakeFiles/jj_email_srv_example.dir/build.make
jj_email_srv_example: libjj_email_srv.a
jj_email_srv_example: CMakeFiles/jj_email_srv_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dd/aglorithms/cpp/jonson_and_jonson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jj_email_srv_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jj_email_srv_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jj_email_srv_example.dir/build: jj_email_srv_example

.PHONY : CMakeFiles/jj_email_srv_example.dir/build

CMakeFiles/jj_email_srv_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jj_email_srv_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jj_email_srv_example.dir/clean

CMakeFiles/jj_email_srv_example.dir/depend:
	cd /home/dd/aglorithms/cpp/jonson_and_jonson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dd/aglorithms/cpp/jonson_and_jonson /home/dd/aglorithms/cpp/jonson_and_jonson /home/dd/aglorithms/cpp/jonson_and_jonson/build /home/dd/aglorithms/cpp/jonson_and_jonson/build /home/dd/aglorithms/cpp/jonson_and_jonson/build/CMakeFiles/jj_email_srv_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jj_email_srv_example.dir/depend

