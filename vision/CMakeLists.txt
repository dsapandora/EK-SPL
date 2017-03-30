cmake_minimum_required(VERSION 2.8)
project(vision)

find_package(qibuild)

set(_srcs
   # vision.cpp
   # vision.h
    #main.cpp
    BallDetection.cpp)

qi_create_lib(vision SHARED ${_srcs} SUBFOLDER naoqi)

#qi_use_lib(vision ALCOMMON BOOST)

qi_use_lib(vision OPENCV2_HIGHGUI OPENCV2_IMGPROC)