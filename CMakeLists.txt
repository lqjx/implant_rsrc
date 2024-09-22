cmake_minimum_required(VERSION 3.29)
project(implant_rsrc)

set(CMAKE_CXX_STANDARD 20)

add_executable(implant_rsrc main.cpp
        resource.h resources.rc)
