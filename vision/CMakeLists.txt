cmake_minimum_required(VERSION 2.8)
project(vision)

find_package(qibuild)

set(_srcs
    vision.cpp
    vision.h
    main.cpp)

qi_create_lib(vision SHARED ${_srcs} SUBFOLDER naoqi)

qi_use_lib(vision ALCOMMON BOOST)

