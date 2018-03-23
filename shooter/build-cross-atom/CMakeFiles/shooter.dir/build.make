# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/roboticaspl/EK-SPL/shooter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roboticaspl/EK-SPL/shooter/build-cross-atom

# Include any dependencies generated for this target.
include CMakeFiles/shooter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shooter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shooter.dir/flags.make

CMakeFiles/shooter.dir/shooter.cpp.o: CMakeFiles/shooter.dir/flags.make
CMakeFiles/shooter.dir/shooter.cpp.o: ../shooter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboticaspl/EK-SPL/shooter/build-cross-atom/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/shooter.dir/shooter.cpp.o"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shooter.dir/shooter.cpp.o -c /home/roboticaspl/EK-SPL/shooter/shooter.cpp

CMakeFiles/shooter.dir/shooter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shooter.dir/shooter.cpp.i"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboticaspl/EK-SPL/shooter/shooter.cpp > CMakeFiles/shooter.dir/shooter.cpp.i

CMakeFiles/shooter.dir/shooter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shooter.dir/shooter.cpp.s"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboticaspl/EK-SPL/shooter/shooter.cpp -o CMakeFiles/shooter.dir/shooter.cpp.s

CMakeFiles/shooter.dir/shooter.cpp.o.requires:
.PHONY : CMakeFiles/shooter.dir/shooter.cpp.o.requires

CMakeFiles/shooter.dir/shooter.cpp.o.provides: CMakeFiles/shooter.dir/shooter.cpp.o.requires
	$(MAKE) -f CMakeFiles/shooter.dir/build.make CMakeFiles/shooter.dir/shooter.cpp.o.provides.build
.PHONY : CMakeFiles/shooter.dir/shooter.cpp.o.provides

CMakeFiles/shooter.dir/shooter.cpp.o.provides.build: CMakeFiles/shooter.dir/shooter.cpp.o

CMakeFiles/shooter.dir/main.cpp.o: CMakeFiles/shooter.dir/flags.make
CMakeFiles/shooter.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboticaspl/EK-SPL/shooter/build-cross-atom/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/shooter.dir/main.cpp.o"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shooter.dir/main.cpp.o -c /home/roboticaspl/EK-SPL/shooter/main.cpp

CMakeFiles/shooter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shooter.dir/main.cpp.i"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboticaspl/EK-SPL/shooter/main.cpp > CMakeFiles/shooter.dir/main.cpp.i

CMakeFiles/shooter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shooter.dir/main.cpp.s"
	/home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboticaspl/EK-SPL/shooter/main.cpp -o CMakeFiles/shooter.dir/main.cpp.s

CMakeFiles/shooter.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/shooter.dir/main.cpp.o.requires

CMakeFiles/shooter.dir/main.cpp.o.provides: CMakeFiles/shooter.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/shooter.dir/build.make CMakeFiles/shooter.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/shooter.dir/main.cpp.o.provides

CMakeFiles/shooter.dir/main.cpp.o.provides.build: CMakeFiles/shooter.dir/main.cpp.o

# Object files for target shooter
shooter_OBJECTS = \
"CMakeFiles/shooter.dir/shooter.cpp.o" \
"CMakeFiles/shooter.dir/main.cpp.o"

# External object files for target shooter
shooter_EXTERNAL_OBJECTS =

sdk/lib/naoqi/libshooter.so: CMakeFiles/shooter.dir/shooter.cpp.o
sdk/lib/naoqi/libshooter.so: CMakeFiles/shooter.dir/main.cpp.o
sdk/lib/naoqi/libshooter.so: CMakeFiles/shooter.dir/build.make
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalproxies.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalsoap.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librttools.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalthread.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_signals-mt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_program_options-mt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalvalue.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libtinyxml.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libqi.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalerror.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_filesystem-mt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libpthread.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
sdk/lib/naoqi/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
sdk/lib/naoqi/libshooter.so: CMakeFiles/shooter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library sdk/lib/naoqi/libshooter.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shooter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shooter.dir/build: sdk/lib/naoqi/libshooter.so
.PHONY : CMakeFiles/shooter.dir/build

# Object files for target shooter
shooter_OBJECTS = \
"CMakeFiles/shooter.dir/shooter.cpp.o" \
"CMakeFiles/shooter.dir/main.cpp.o"

# External object files for target shooter
shooter_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/libshooter.so: CMakeFiles/shooter.dir/shooter.cpp.o
CMakeFiles/CMakeRelink.dir/libshooter.so: CMakeFiles/shooter.dir/main.cpp.o
CMakeFiles/CMakeRelink.dir/libshooter.so: CMakeFiles/shooter.dir/build.make
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalproxies.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalsoap.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librttools.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalthread.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_signals-mt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_program_options-mt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalvalue.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libtinyxml.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libqi.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalerror.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_filesystem-mt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libpthread.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
CMakeFiles/CMakeRelink.dir/libshooter.so: /home/roboticaspl/SPL/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
CMakeFiles/CMakeRelink.dir/libshooter.so: CMakeFiles/shooter.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libshooter.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shooter.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/shooter.dir/preinstall: CMakeFiles/CMakeRelink.dir/libshooter.so
.PHONY : CMakeFiles/shooter.dir/preinstall

CMakeFiles/shooter.dir/requires: CMakeFiles/shooter.dir/shooter.cpp.o.requires
CMakeFiles/shooter.dir/requires: CMakeFiles/shooter.dir/main.cpp.o.requires
.PHONY : CMakeFiles/shooter.dir/requires

CMakeFiles/shooter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shooter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shooter.dir/clean

CMakeFiles/shooter.dir/depend:
	cd /home/roboticaspl/EK-SPL/shooter/build-cross-atom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roboticaspl/EK-SPL/shooter /home/roboticaspl/EK-SPL/shooter /home/roboticaspl/EK-SPL/shooter/build-cross-atom /home/roboticaspl/EK-SPL/shooter/build-cross-atom /home/roboticaspl/EK-SPL/shooter/build-cross-atom/CMakeFiles/shooter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shooter.dir/depend

