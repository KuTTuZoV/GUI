# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\anton\Documents\GUI\GUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\anton\Documents\GUI\GUI\build

# Utility rule file for _GUI_autogen.

# Include the progress variables for this target.
include CMakeFiles/_GUI_autogen.dir/progress.make

CMakeFiles/_GUI_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\anton\Documents\GUI\GUI\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic UIC for target _GUI"
	"C:\Program Files\CMake\bin\cmake.exe" -E cmake_autogen C:/Users/anton/Documents/GUI/GUI/build/CMakeFiles/_GUI_autogen.dir/AutogenInfo.json ""

_GUI_autogen: CMakeFiles/_GUI_autogen
_GUI_autogen: CMakeFiles/_GUI_autogen.dir/build.make

.PHONY : _GUI_autogen

# Rule to build all files generated by this target.
CMakeFiles/_GUI_autogen.dir/build: _GUI_autogen

.PHONY : CMakeFiles/_GUI_autogen.dir/build

CMakeFiles/_GUI_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\_GUI_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/_GUI_autogen.dir/clean

CMakeFiles/_GUI_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\anton\Documents\GUI\GUI C:\Users\anton\Documents\GUI\GUI C:\Users\anton\Documents\GUI\GUI\build C:\Users\anton\Documents\GUI\GUI\build C:\Users\anton\Documents\GUI\GUI\build\CMakeFiles\_GUI_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/_GUI_autogen.dir/depend
