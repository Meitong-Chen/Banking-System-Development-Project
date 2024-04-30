cmake_minimum_required(VERSION 3.21)
project(2021_CPP_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(2021_CPP_Project main.cpp Bank.cpp Bank.h Customer.cpp Customer.h Manager.cpp Manager.h User.cpp User.h)
