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
CMAKE_COMMAND = /home/halli/Documents/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/halli/Documents/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/halli/Documents/TurboPascal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/halli/Documents/TurboPascal/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TurboPascal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TurboPascal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TurboPascal.dir/flags.make

CMakeFiles/TurboPascal.dir/main.cpp.o: CMakeFiles/TurboPascal.dir/flags.make
CMakeFiles/TurboPascal.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TurboPascal.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurboPascal.dir/main.cpp.o -c /home/halli/Documents/TurboPascal/main.cpp

CMakeFiles/TurboPascal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurboPascal.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/halli/Documents/TurboPascal/main.cpp > CMakeFiles/TurboPascal.dir/main.cpp.i

CMakeFiles/TurboPascal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurboPascal.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/halli/Documents/TurboPascal/main.cpp -o CMakeFiles/TurboPascal.dir/main.cpp.s

CMakeFiles/TurboPascal.dir/hparser.cpp.o: CMakeFiles/TurboPascal.dir/flags.make
CMakeFiles/TurboPascal.dir/hparser.cpp.o: ../hparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TurboPascal.dir/hparser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurboPascal.dir/hparser.cpp.o -c /home/halli/Documents/TurboPascal/hparser.cpp

CMakeFiles/TurboPascal.dir/hparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurboPascal.dir/hparser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/halli/Documents/TurboPascal/hparser.cpp > CMakeFiles/TurboPascal.dir/hparser.cpp.i

CMakeFiles/TurboPascal.dir/hparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurboPascal.dir/hparser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/halli/Documents/TurboPascal/hparser.cpp -o CMakeFiles/TurboPascal.dir/hparser.cpp.s

CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o: CMakeFiles/TurboPascal.dir/flags.make
CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o: ../sa_visitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o -c /home/halli/Documents/TurboPascal/sa_visitor.cpp

CMakeFiles/TurboPascal.dir/sa_visitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurboPascal.dir/sa_visitor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/halli/Documents/TurboPascal/sa_visitor.cpp > CMakeFiles/TurboPascal.dir/sa_visitor.cpp.i

CMakeFiles/TurboPascal.dir/sa_visitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurboPascal.dir/sa_visitor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/halli/Documents/TurboPascal/sa_visitor.cpp -o CMakeFiles/TurboPascal.dir/sa_visitor.cpp.s

CMakeFiles/TurboPascal.dir/lexer.cpp.o: CMakeFiles/TurboPascal.dir/flags.make
CMakeFiles/TurboPascal.dir/lexer.cpp.o: ../lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TurboPascal.dir/lexer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurboPascal.dir/lexer.cpp.o -c /home/halli/Documents/TurboPascal/lexer.cpp

CMakeFiles/TurboPascal.dir/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurboPascal.dir/lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/halli/Documents/TurboPascal/lexer.cpp > CMakeFiles/TurboPascal.dir/lexer.cpp.i

CMakeFiles/TurboPascal.dir/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurboPascal.dir/lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/halli/Documents/TurboPascal/lexer.cpp -o CMakeFiles/TurboPascal.dir/lexer.cpp.s

CMakeFiles/TurboPascal.dir/language.cpp.o: CMakeFiles/TurboPascal.dir/flags.make
CMakeFiles/TurboPascal.dir/language.cpp.o: ../language.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TurboPascal.dir/language.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurboPascal.dir/language.cpp.o -c /home/halli/Documents/TurboPascal/language.cpp

CMakeFiles/TurboPascal.dir/language.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurboPascal.dir/language.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/halli/Documents/TurboPascal/language.cpp > CMakeFiles/TurboPascal.dir/language.cpp.i

CMakeFiles/TurboPascal.dir/language.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurboPascal.dir/language.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/halli/Documents/TurboPascal/language.cpp -o CMakeFiles/TurboPascal.dir/language.cpp.s

# Object files for target TurboPascal
TurboPascal_OBJECTS = \
"CMakeFiles/TurboPascal.dir/main.cpp.o" \
"CMakeFiles/TurboPascal.dir/hparser.cpp.o" \
"CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o" \
"CMakeFiles/TurboPascal.dir/lexer.cpp.o" \
"CMakeFiles/TurboPascal.dir/language.cpp.o"

# External object files for target TurboPascal
TurboPascal_EXTERNAL_OBJECTS =

TurboPascal: CMakeFiles/TurboPascal.dir/main.cpp.o
TurboPascal: CMakeFiles/TurboPascal.dir/hparser.cpp.o
TurboPascal: CMakeFiles/TurboPascal.dir/sa_visitor.cpp.o
TurboPascal: CMakeFiles/TurboPascal.dir/lexer.cpp.o
TurboPascal: CMakeFiles/TurboPascal.dir/language.cpp.o
TurboPascal: CMakeFiles/TurboPascal.dir/build.make
TurboPascal: CMakeFiles/TurboPascal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable TurboPascal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TurboPascal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TurboPascal.dir/build: TurboPascal

.PHONY : CMakeFiles/TurboPascal.dir/build

CMakeFiles/TurboPascal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TurboPascal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TurboPascal.dir/clean

CMakeFiles/TurboPascal.dir/depend:
	cd /home/halli/Documents/TurboPascal/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/halli/Documents/TurboPascal /home/halli/Documents/TurboPascal /home/halli/Documents/TurboPascal/cmake-build-debug /home/halli/Documents/TurboPascal/cmake-build-debug /home/halli/Documents/TurboPascal/cmake-build-debug/CMakeFiles/TurboPascal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TurboPascal.dir/depend
