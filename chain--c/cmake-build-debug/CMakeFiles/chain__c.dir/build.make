# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programs\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programs\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CS\learning\projects\chain--c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CS\learning\projects\chain--c\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/chain__c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chain__c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chain__c.dir/flags.make

CMakeFiles/chain__c.dir/main.cpp.obj: CMakeFiles/chain__c.dir/flags.make
CMakeFiles/chain__c.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CS\learning\projects\chain--c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chain__c.dir/main.cpp.obj"
	D:\Programs\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\chain__c.dir\main.cpp.obj -c D:\CS\learning\projects\chain--c\main.cpp

CMakeFiles/chain__c.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chain__c.dir/main.cpp.i"
	D:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CS\learning\projects\chain--c\main.cpp > CMakeFiles\chain__c.dir\main.cpp.i

CMakeFiles/chain__c.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chain__c.dir/main.cpp.s"
	D:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CS\learning\projects\chain--c\main.cpp -o CMakeFiles\chain__c.dir\main.cpp.s

# Object files for target chain__c
chain__c_OBJECTS = \
"CMakeFiles/chain__c.dir/main.cpp.obj"

# External object files for target chain__c
chain__c_EXTERNAL_OBJECTS =

chain__c.exe: CMakeFiles/chain__c.dir/main.cpp.obj
chain__c.exe: CMakeFiles/chain__c.dir/build.make
chain__c.exe: CMakeFiles/chain__c.dir/linklibs.rsp
chain__c.exe: CMakeFiles/chain__c.dir/objects1.rsp
chain__c.exe: CMakeFiles/chain__c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CS\learning\projects\chain--c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable chain__c.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\chain__c.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chain__c.dir/build: chain__c.exe

.PHONY : CMakeFiles/chain__c.dir/build

CMakeFiles/chain__c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\chain__c.dir\cmake_clean.cmake
.PHONY : CMakeFiles/chain__c.dir/clean

CMakeFiles/chain__c.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CS\learning\projects\chain--c D:\CS\learning\projects\chain--c D:\CS\learning\projects\chain--c\cmake-build-debug D:\CS\learning\projects\chain--c\cmake-build-debug D:\CS\learning\projects\chain--c\cmake-build-debug\CMakeFiles\chain__c.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chain__c.dir/depend

