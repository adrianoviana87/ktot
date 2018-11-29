cmake_minimum_required(VERSION 3.0)

project(ktot_domain)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(../include)

add_library(
  ktot_domain
  task_t.cpp
  task_service_t.cpp
        work_t.cpp)

