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
CMAKE_SOURCE_DIR = /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom

# Include any dependencies generated for this target.
include CMakeFiles/BallDetection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BallDetection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BallDetection.dir/flags.make

CMakeFiles/BallDetection.dir/BallDetection.cpp.o: CMakeFiles/BallDetection.dir/flags.make
CMakeFiles/BallDetection.dir/BallDetection.cpp.o: ../BallDetection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BallDetection.dir/BallDetection.cpp.o"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BallDetection.dir/BallDetection.cpp.o -c /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/BallDetection.cpp

CMakeFiles/BallDetection.dir/BallDetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BallDetection.dir/BallDetection.cpp.i"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/BallDetection.cpp > CMakeFiles/BallDetection.dir/BallDetection.cpp.i

CMakeFiles/BallDetection.dir/BallDetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BallDetection.dir/BallDetection.cpp.s"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/BallDetection.cpp -o CMakeFiles/BallDetection.dir/BallDetection.cpp.s

CMakeFiles/BallDetection.dir/BallDetection.cpp.o.requires:

.PHONY : CMakeFiles/BallDetection.dir/BallDetection.cpp.o.requires

CMakeFiles/BallDetection.dir/BallDetection.cpp.o.provides: CMakeFiles/BallDetection.dir/BallDetection.cpp.o.requires
	$(MAKE) -f CMakeFiles/BallDetection.dir/build.make CMakeFiles/BallDetection.dir/BallDetection.cpp.o.provides.build
.PHONY : CMakeFiles/BallDetection.dir/BallDetection.cpp.o.provides

CMakeFiles/BallDetection.dir/BallDetection.cpp.o.provides.build: CMakeFiles/BallDetection.dir/BallDetection.cpp.o


CMakeFiles/BallDetection.dir/main.cpp.o: CMakeFiles/BallDetection.dir/flags.make
CMakeFiles/BallDetection.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BallDetection.dir/main.cpp.o"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BallDetection.dir/main.cpp.o -c /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/main.cpp

CMakeFiles/BallDetection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BallDetection.dir/main.cpp.i"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/main.cpp > CMakeFiles/BallDetection.dir/main.cpp.i

CMakeFiles/BallDetection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BallDetection.dir/main.cpp.s"
	/home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5//cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/main.cpp -o CMakeFiles/BallDetection.dir/main.cpp.s

CMakeFiles/BallDetection.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/BallDetection.dir/main.cpp.o.requires

CMakeFiles/BallDetection.dir/main.cpp.o.provides: CMakeFiles/BallDetection.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/BallDetection.dir/build.make CMakeFiles/BallDetection.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/BallDetection.dir/main.cpp.o.provides

CMakeFiles/BallDetection.dir/main.cpp.o.provides.build: CMakeFiles/BallDetection.dir/main.cpp.o


# Object files for target BallDetection
BallDetection_OBJECTS = \
"CMakeFiles/BallDetection.dir/BallDetection.cpp.o" \
"CMakeFiles/BallDetection.dir/main.cpp.o"

# External object files for target BallDetection
BallDetection_EXTERNAL_OBJECTS =

sdk/lib/naoqi/libBallDetection.so: CMakeFiles/BallDetection.dir/BallDetection.cpp.o
sdk/lib/naoqi/libBallDetection.so: CMakeFiles/BallDetection.dir/main.cpp.o
sdk/lib/naoqi/libBallDetection.so: CMakeFiles/BallDetection.dir/build.make
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalproxies.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalsoap.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librttools.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalthread.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_signals-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_program_options-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalvalue.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libtinyxml.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libqi.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalerror.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_filesystem-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_date_time-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_date_time-mt.so
sdk/lib/naoqi/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
sdk/lib/naoqi/libBallDetection.so: CMakeFiles/BallDetection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library sdk/lib/naoqi/libBallDetection.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BallDetection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BallDetection.dir/build: sdk/lib/naoqi/libBallDetection.so

.PHONY : CMakeFiles/BallDetection.dir/build

# Object files for target BallDetection
BallDetection_OBJECTS = \
"CMakeFiles/BallDetection.dir/BallDetection.cpp.o" \
"CMakeFiles/BallDetection.dir/main.cpp.o"

# External object files for target BallDetection
BallDetection_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/libBallDetection.so: CMakeFiles/BallDetection.dir/BallDetection.cpp.o
CMakeFiles/CMakeRelink.dir/libBallDetection.so: CMakeFiles/BallDetection.dir/main.cpp.o
CMakeFiles/CMakeRelink.dir/libBallDetection.so: CMakeFiles/BallDetection.dir/build.make
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalproxies.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalsoap.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librttools.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalthread.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_signals-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_program_options-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalvalue.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libtinyxml.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/librt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libqi.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libalerror.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_filesystem-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_date_time-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_system-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_thread-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libboost_date_time-mt.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: /home/htellezb/Aldebaran-software/linux64-nao-atom-cross-toolchain-1.14.5/sysroot/usr/lib/libdl.so
CMakeFiles/CMakeRelink.dir/libBallDetection.so: CMakeFiles/BallDetection.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libBallDetection.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BallDetection.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/BallDetection.dir/preinstall: CMakeFiles/CMakeRelink.dir/libBallDetection.so

.PHONY : CMakeFiles/BallDetection.dir/preinstall

CMakeFiles/BallDetection.dir/requires: CMakeFiles/BallDetection.dir/BallDetection.cpp.o.requires
CMakeFiles/BallDetection.dir/requires: CMakeFiles/BallDetection.dir/main.cpp.o.requires

.PHONY : CMakeFiles/BallDetection.dir/requires

CMakeFiles/BallDetection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BallDetection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BallDetection.dir/clean

CMakeFiles/BallDetection.dir/depend:
	cd /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom /home/htellezb/EK-SPL/ball-recognition/ball-recognition-module/build-cross-atom/CMakeFiles/BallDetection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BallDetection.dir/depend
