# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/cmake-build-debug

# Utility rule file for TestingGroundsEditor-Mac-DebugGame.

# Include the progress variables for this target.
include CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/progress.make

CMakeFiles/TestingGroundsEditor-Mac-DebugGame:
	cd /Applications/UE_4.24 && bash /Applications/UE_4.24/Engine/Build/BatchFiles/Mac/Build.sh TestingGroundsEditor Mac DebugGame -project=/Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/TestingGrounds.uproject -game -progress -buildscw

TestingGroundsEditor-Mac-DebugGame: CMakeFiles/TestingGroundsEditor-Mac-DebugGame
TestingGroundsEditor-Mac-DebugGame: CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/build.make

.PHONY : TestingGroundsEditor-Mac-DebugGame

# Rule to build all files generated by this target.
CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/build: TestingGroundsEditor-Mac-DebugGame

.PHONY : CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/build

CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/clean

CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/depend:
	cd /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/cmake-build-debug /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/cmake-build-debug /Users/zigkurat/Documents/Workspace/Unreal/Section_05/TestingGrounds/cmake-build-debug/CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestingGroundsEditor-Mac-DebugGame.dir/depend
