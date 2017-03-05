cmake_minimum_required(VERSION 2.8)
project(shooter)

find_package(qibuild)
# Create a list of source files
set(_srcs
    shooter.cpp
    shooter.h
    main.cpp)

# Create a plugin, that is a shared library, and make
# sure it is built in lib/naoqi
qi_create_lib(shooter SHARED ${_srcs} SUBFOLDER naoqi)

qi_use_lib(shooter ALCOMMON BOOST)

