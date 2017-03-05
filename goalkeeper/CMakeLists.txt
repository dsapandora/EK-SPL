cmake_minimum_required(VERSION 2.8)
project(goalkeeper)

find_package(qibuild)
# Create a list of source files
set(_srcs
    goalkeeper.cpp
    goalkeeper.h
    main.cpp)

# Create a plugin, that is a shared library, and make
# sure it is built in lib/naoqi
qi_create_lib(goalkeeper SHARED ${_srcs} SUBFOLDER naoqi)

qi_use_lib(goalkeeper ALCOMMON BOOST)

