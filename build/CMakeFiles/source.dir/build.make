# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /data/zhiyuany/Non-Slicing_FloorPlanning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/zhiyuany/Non-Slicing_FloorPlanning/build

# Include any dependencies generated for this target.
include CMakeFiles/source.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/source.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/source.dir/flags.make

CMakeFiles/source.dir/src/block.cpp.o: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/src/block.cpp.o: ../src/block.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/zhiyuany/Non-Slicing_FloorPlanning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/source.dir/src/block.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source.dir/src/block.cpp.o -c /data/zhiyuany/Non-Slicing_FloorPlanning/src/block.cpp

CMakeFiles/source.dir/src/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source.dir/src/block.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/zhiyuany/Non-Slicing_FloorPlanning/src/block.cpp > CMakeFiles/source.dir/src/block.cpp.i

CMakeFiles/source.dir/src/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source.dir/src/block.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/zhiyuany/Non-Slicing_FloorPlanning/src/block.cpp -o CMakeFiles/source.dir/src/block.cpp.s

CMakeFiles/source.dir/src/calculate.cpp.o: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/src/calculate.cpp.o: ../src/calculate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/zhiyuany/Non-Slicing_FloorPlanning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/source.dir/src/calculate.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source.dir/src/calculate.cpp.o -c /data/zhiyuany/Non-Slicing_FloorPlanning/src/calculate.cpp

CMakeFiles/source.dir/src/calculate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source.dir/src/calculate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/zhiyuany/Non-Slicing_FloorPlanning/src/calculate.cpp > CMakeFiles/source.dir/src/calculate.cpp.i

CMakeFiles/source.dir/src/calculate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source.dir/src/calculate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/zhiyuany/Non-Slicing_FloorPlanning/src/calculate.cpp -o CMakeFiles/source.dir/src/calculate.cpp.s

# Object files for target source
source_OBJECTS = \
"CMakeFiles/source.dir/src/block.cpp.o" \
"CMakeFiles/source.dir/src/calculate.cpp.o"

# External object files for target source
source_EXTERNAL_OBJECTS =

libsource.a: CMakeFiles/source.dir/src/block.cpp.o
libsource.a: CMakeFiles/source.dir/src/calculate.cpp.o
libsource.a: CMakeFiles/source.dir/build.make
libsource.a: CMakeFiles/source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/zhiyuany/Non-Slicing_FloorPlanning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsource.a"
	$(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/source.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/source.dir/build: libsource.a

.PHONY : CMakeFiles/source.dir/build

CMakeFiles/source.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean.cmake
.PHONY : CMakeFiles/source.dir/clean

CMakeFiles/source.dir/depend:
	cd /data/zhiyuany/Non-Slicing_FloorPlanning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/zhiyuany/Non-Slicing_FloorPlanning /data/zhiyuany/Non-Slicing_FloorPlanning /data/zhiyuany/Non-Slicing_FloorPlanning/build /data/zhiyuany/Non-Slicing_FloorPlanning/build /data/zhiyuany/Non-Slicing_FloorPlanning/build/CMakeFiles/source.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/source.dir/depend
